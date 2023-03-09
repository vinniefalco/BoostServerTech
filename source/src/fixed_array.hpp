//
// Copyright (c) 2023 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/BoostServerTech
//

#ifndef SRC_FIXED_ARRAY_HPP
#define SRC_FIXED_ARRAY_HPP

#include <pbb/config.hpp>
#include <cstdlib>
#include <memory>

namespace pbb {

/** A fixed size array

    This container supports non-moveable types.
    The size is determined upon construction and
    cannot be changed.
*/
template<class T>
class fixed_array
{
//#if __cplusplus < 201703L // gcc nonconforming
    static_assert(
        alignof(T) <=
            alignof(std::max_align_t),
        "T must not be overaligned");
//#endif

    T* t_ = nullptr;
    std::size_t n_ = 0;

    void
    destroy()
    {
        if(! t_)
            return;
        auto n = n_;
        while(n--)
            t_[n].~T();
        std::allocator<T>{
            }.deallocate(t_, n_);
    }

public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using iterator = T*;
    using const_reference = T const&;
    using const_pointer = T const*;
    using const_iterator = T const*;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;

    ~fixed_array()
    {
        destroy();
    }

    fixed_array() = default;

    fixed_array(
        fixed_array&& other) noexcept
        : t_(other.t_)
        , n_(other.n_)
    {
        other.t_ = nullptr;
        other.n_ = 0;
    }

    fixed_array&
    operator=(fixed_array&& other) noexcept
    {
        destroy();
        t_ = other.t_;
        n_ = other.n_;
        other.t_ = nullptr;
        other.n_ = 0;
        return *this;
    }

    template<class... Args>
    explicit
    fixed_array(
        std::size_t N,
        Args&&... args)
        : t_(std::allocator<T>{
            }.allocate(N))
    {
        struct cleanup
        {
            T* t_;
            std::size_t& n_;
            std::size_t N_;

            ~cleanup()
            {
                if(! t_)
                    return;
                while(n_--)
                    t_[n_].~T();
                std::allocator<T>{
                    }.deallocate(t_, N_);
            }
        };

        cleanup cl{ t_, n_, N };
        while(n_ < N)
        {
            ::new(&t_[n_]) T(
                std::forward<Args>(args)...);
            ++n_;
        }
        cl.t_ = nullptr;
    }

    std::size_t
    size() const noexcept
    {
        return n_;
    }

    iterator
    begin() noexcept
    {
        return t_;
    }

    iterator
    end() noexcept
    {
        return t_ + n_;
    }

    const_iterator
    begin() const noexcept
    {
        return const_cast<
            T const*>(t_);
    }

    const_iterator
    end() const noexcept
    {
        return const_cast<
            T const*>(t_) + n_;
    }

    T&
    operator[](std::size_t i) noexcept
    {
        return t_[i];
    }

    T const&
    operator[](std::size_t i) const noexcept
    {
        return t_[i];
    }

    T&
    front() noexcept
    {
        return t_[0];
    }

    T const&
    front() const noexcept
    {
        return t_[0];
    }

    T&
    back() noexcept
    {
        return t_[n_ - 1];
    }

    T const&
    back() const noexcept
    {
        return t_[n_ - 1];
    }
};

} // pbb

#endif
