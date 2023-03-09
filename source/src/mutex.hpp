//
// Copyright (c) 2023 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/BoostServerTech
//

#ifndef SRC_MUTEX_HPP
#define SRC_MUTEX_HPP

#include <pbb/config.hpp>

#ifdef _MSC_VER
#include <boost/thread/shared_mutex.hpp>
#else
#include <mutex>
#endif

namespace pbb {

// Workaround for slow MSVC std::mutex
// constrained by ABI compatibility.
#ifdef _MSC_VER
using mutex = boost::shared_mutex;
#else
using mutex = std::mutex;
#endif

} // pbb

#endif
