//
// Copyright (c) 2023 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/BoostServerTech
//

#include <pbb/server.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/executor.hpp>

namespace pbb {

namespace {

class server_impl : public server
{
    asio::io_context ioc_;

public:
    executor_type
    make_executor() override
    {
        return executor_type(
            ioc_.get_executor());
    }
};

} // (anon)

std::unique_ptr<server>
make_server()
{
    return std::unique_ptr<server>(
        new server_impl);
}

} // pbb
