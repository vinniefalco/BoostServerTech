//
// Copyright (c) 2023 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/BoostServerTech
//

#ifndef SRC_NET_LISTENER_HPP
#define SRC_NET_LISTENER_HPP

#include <pbb/config.hpp>
#include <pbb/log.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace pbb {

class listener
{
public:
    using acceptor_type = asio::basic_socket_acceptor< asio::ip::tcp, asio::executor >;
    using socket_type = asio::basic_stream_socket< asio::ip::tcp, asio::executor >;

    listener(
        asio::ip::tcp::endpoint ep,
        asio::executor ex);

private:
    acceptor_type acc_;
};

} // pbb

#endif
