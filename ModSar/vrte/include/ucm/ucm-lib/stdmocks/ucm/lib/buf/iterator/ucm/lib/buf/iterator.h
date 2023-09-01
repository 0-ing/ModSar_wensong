//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/buf/iterator.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__ITERATOR_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__ITERATOR_H_

#include <limits>
#include <cstdint>
#include <cstddef>
#include <type_traits>

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

class Iterator : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_buf__Iterator, TEST__CTor);
#endif

    explicit Iterator(std::size_t mb, std::size_t cb, size_t ib) noexcept
        : end_block_{mb}
        , cur_block_{cb > mb ? mb : cb}
        , ini_block_{ib}
    {}

public:
    static bool& mock_flag()
    {
        static bool mflag = false;
        return mflag;
    }

    explicit Iterator(std::size_t mb, std::size_t cb) noexcept
        : end_block_{mb}
        , cur_block_{cb > mb ? mb : cb}
        , ini_block_{cur_block_}
    {}

    explicit Iterator(std::size_t mb) noexcept
        : Iterator(mb, mb)
    {}

    Iterator(Iterator     &&) = default;
    Iterator(Iterator const&) = delete;

    Iterator& operator=(Iterator     &&) = default;
    Iterator& operator=(Iterator const&) = delete;

    virtual ~Iterator() = default;

    bool operator==(const Iterator& rhs) const noexcept
    {
        if (mock_flag())
            return pop<bool>();
        else
            return this->cur_block_ == rhs.cur_block_;
    }

    bool operator!=(const Iterator& rhs) const noexcept
    {
        if (mock_flag())
            return pop<bool>();
        else
            return !(*this == rhs);
    }

    Iterator& operator++() noexcept
    {
        if (cur_block_ < end_block_)
            ++cur_block_;
        return *this;
    }

    Iterator& operator--() noexcept
    {
        if (cur_block_ < end_block_) {
            if (cur_block_ == 0)
                cur_block_ = end_block_;
            else if (cur_block_ > 0)
                --cur_block_;
        }

        return *this;
    }

    Iterator operator++(int) noexcept
    {
        Iterator temp(end_block_, cur_block_, ini_block_);
        operator++();
        return temp;
    }

    Iterator operator--(int) noexcept
    {
        Iterator temp(end_block_, cur_block_, ini_block_);
        operator--();
        return temp;
    }

    Iterator operator+(std::size_t num) noexcept
    {
        std::size_t eval = endblock();
        std::size_t cval = curblock();
        std::size_t ival = iniblock();

        if (cval == eval)
            return Iterator(eval, eval, ival);

        if (num > (eval - cval))
            return Iterator(eval, eval, ival);
        else
            return Iterator(eval, cval + num, ival);
    }

    Iterator operator-(std::size_t num) noexcept
    {
        std::size_t eval = endblock();
        std::size_t cval = curblock();
        std::size_t ival = iniblock();

        if (cval == eval)
            return Iterator(eval, eval, ival);

        if (num > cval)
            return Iterator(eval, eval, ival);
        else
            return Iterator(eval, cval - num, ival);
    }

    void reset() noexcept
    {
        if (mock_flag())
            cur_block_ = pop<std::size_t>();
        else
            cur_block_ = ini_block_;
    }

    std::size_t curblock() const noexcept
    {
        if (mock_flag())
            return pop<std::size_t>();
        else
            return cur_block_;
    }

    std::size_t endblock() const noexcept
    {
        if (mock_flag())
            return pop<std::size_t>();
        else
            return end_block_;
    }

    std::size_t iniblock() const noexcept
    {
        if (mock_flag())
            return pop<std::size_t>();
        else
            return ini_block_;
    }

    bool isenditer() const noexcept
    {
        if (mock_flag())
            return pop<bool>();
        else
            return !(cur_block_ < end_block_);
    }


private:
    std::size_t end_block_;
    std::size_t cur_block_;
    std::size_t ini_block_;
};


}    // namespace buf
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_BUF__ITERATOR_H_
