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

struct single_threaded_t
{
};


class server
{
public:
    using executor_type = asio::executor;

    virtual
    executor_type
    make_executor() = 0;
};

std::unique_ptr<server>
make_server();

} // pbb

#endif
