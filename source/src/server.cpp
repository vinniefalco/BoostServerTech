//
// Copyright (c) 2023 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/BoostServerTech
//

#include <pbb/server.hpp>
#include <boost/asio/append.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/signal_set.hpp>
#include <src/fixed_array.hpp>
#include <functional>
#include <thread>

namespace pbb {

template<class M, class T>
struct mem_fn_binder
{
    M mf_;
    T* t_;

    template<class... Args>
    void
    operator()(Args&&... args)
    {
        (t_->*mf_)(std::forward<Args>(args)...);
    }
};

template<class M, class T>
auto
bind_front(M mf, T* t) ->
    mem_fn_binder<M, T>
{
    return { mf, t };
}

//------------------------------------------------

namespace {

class server_impl : public server
{
    // order of construction matters
    fixed_array<asio::io_context> ioc_;
    asio::basic_signal_set<asio::io_context::executor_type> sig_;
    fixed_array<std::thread> t_;
    std::size_t nthread_;

public:
    server_impl(
        std::size_t ncontext,
        std::size_t nthread)
        : ioc_(
            [&]
            {
                if(ncontext == 0)
                    throw std::invalid_argument(
                        "ncontext == 0");

                if(nthread == 0)
                    throw std::invalid_argument(
                        "nthread == 0");

                return fixed_array<asio::io_context>(
                    ncontext, static_cast<int>(nthread));
            }())
        , sig_(ioc_.front(), SIGINT, SIGTERM)
        , nthread_(nthread)
    {
    }

    void
    run() override
    {
        // Trap SIGINT and SIGTERM to perform a clean shutdown
        sig_.async_wait(bind_front(&server_impl::on_signal, this));

        t_ = fixed_array<std::thread>(
            nthread_,
            [this]
            {
                ioc_.front().run();
            });
        ioc_.back().run();
        for(auto& t : t_)
            t.join();
    }

    void
    stop() override
    {
    }

private:
    void
    on_signal(
        system::error_code ec,
        int signum)
    {
        // Stop all `io_context`. This causes run() to return immediately,
        // eventually destroying the contexts and all of the I/O objects.
        for(auto& ioc : ioc_)
            ioc.stop();
    }
};

} // (anon)

//------------------------------------------------

std::unique_ptr<server>
make_single_threaded_server()
{
    return std::unique_ptr<server>(
        new server_impl(1, 1));
}

std::unique_ptr<server>
make_multi_threaded_server(
    std::size_t number_of_threads)
{
    return std::unique_ptr<server>(
        new server_impl(1, number_of_threads));
}

std::unique_ptr<server>
make_multi_context_server(
    std::size_t number_of_contexts)
{
    return std::unique_ptr<server>(
        new server_impl(
            number_of_contexts,
            number_of_contexts));
}

} // pbb
