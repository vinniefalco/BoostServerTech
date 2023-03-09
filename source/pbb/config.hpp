//
// Copyright (c) 2023 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/BoostServerTech
//

#ifndef PBB_CONFIG_HPP
#define PBB_CONFIG_HPP

namespace boost {
namespace asio {
class executor;
} // asio
namespace core {}
namespace system {}
} // boost

namespace pbb {

namespace asio = boost::asio;
namespace core = boost::core;
namespace system = boost::system;

} // pbb

#endif
