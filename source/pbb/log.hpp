//
// Copyright (c) 2023 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/BoostServerTech
//

#ifndef SRC_LOG_HPP
#define SRC_LOG_HPP

#include <pbb/config.hpp>

namespace pbb {

enum class log_level
{
    trace = 0,
    debug = 1,
    info  = 2,
    warn  = 3,
    err   = 4,
    fatal = 5,
    //
    disabled = 6
};

struct journal
{
};

// Log at the specified level
#define LOG_AT_LEVEL(out, level, ...) \
    do { \
        if(level >= out.threshold()) \
            out.write(level, __VA_ARGS__); \
    } while(false)

/// Log at trace level
#define LOG_TRC(sect, ...) LOG_AT_LEVEL(sect, 0, __VA_ARGS__)

/// Log at debug level
#define LOG_DBG(sect, ...) LOG_AT_LEVEL(sect, 1, __VA_ARGS__)

/// Log at info level (normal)
#define LOG_INF(sect, ...) LOG_AT_LEVEL(sect, 2, __VA_ARGS__)

/// Log at warning level
#define LOG_WRN(sect, ...) LOG_AT_LEVEL(sect, 3, __VA_ARGS__)

/// Log at error level
#define LOG_ERR(sect, ...) LOG_AT_LEVEL(sect, 4, __VA_ARGS__)

/// Log at fatal level
#define LOG_FTL(sect, ...) LOG_AT_LEVEL(sect, 0, __VA_ARGS__)
} // pbb

#endif
