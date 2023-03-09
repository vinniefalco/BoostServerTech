//
// Copyright (c) 2023 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/BoostServerTech
//

#include <src/net/listener.hpp>

namespace pbb {

listener::
listener(
    asio::ip::tcp::endpoint ep,
    asio::executor ex)
    : acc_(ex)
{
    system::error_code ec;

    acc_.open(ep.protocol(), ec);
    if(ec.failed())
    {
    }

    acc_.set_option(asio::socket_base::reuse_address(true), ec);
    if(ec.failed())
    {
    }

    acc_.bind(ep, ec);
    if(ec.failed())
    {
    }

    acc_.listen(asio::socket_base::max_listen_connections, ec);
    if(ec.failed())
    {
    }
}

} // pbb
