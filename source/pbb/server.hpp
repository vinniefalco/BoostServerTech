//
// Copyright (c) 2023 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/BoostServerTech
//

#ifndef PBB_SERVER_HPP
#define PBB_SERVER_HPP

#include <pbb/config.hpp>
#include <memory>

namespace pbb {

/** The server object which holds everything.
*/
class server
{
public:
    virtual
    void
    run() = 0;

    virtual
    void
    stop() = 0;
};

/** One io_context and one thread
*/
std::unique_ptr<server>
make_single_threaded_server();

/** One io_context and many threads
*/
std::unique_ptr<server>
make_multi_threaded_server(
    std::size_t number_of_threads);

/** Many single-threaded io_contexts
*/
std::unique_ptr<server>
make_multi_context_server(
    std::size_t number_of_contexts);

} // pbb

#endif
