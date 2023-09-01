//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/buf/iterator.h
/// @brief        Buffer iterator.
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_lib_buf

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__ITERATOR_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__ITERATOR_H_

#include <limits>
#include <cstdint>
#include <cstddef>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include <gtest/gtest_prod.h>
#endif

/// @addtogroup bosch_vrte_ucm_lib_buf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

/// @class Iterator iterator.h ucm/lib/buf/iterator.h
/// @ingroup bosch_vrte_ucm_lib_buf
/// @brief Buffer iterator class.
///
/// The buffer iterator class contains indexes, but not pointer. In the general
/// case the index can be anything - a position in a contiguous memory region,
/// number of a memory region or anything countable that has a start number
/// and an end number. In the context of this iterator we will call these
/// countable object items.
///
/// The iterator is represented by two variables - end_block_ and cur_block_.
/// Once the cur_block_ becomes equal to the end_block we consider that the
/// iterator has reached to the end of the items set it iterates over.
/// prefix and suffix increment and decrement operators are provided.
/// It must be noted that any changes in the underlying set invalidate the
/// iterator. It is a responsibility of the programmer to ensure that the
/// underlying set remains unchanged until the iterator object is in use.
///
class Iterator final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_buf__Iterator, TEST__CTor);
    FRIEND_TEST(Test__ucm_lib_buf__Iterator, TEST__OperP);
    FRIEND_TEST(Test__ucm_lib_buf__Iterator, TEST__OperM);
    FRIEND_TEST(Test__ucm_lib_buf__Iterator, TEST__OperPP);
    FRIEND_TEST(Test__ucm_lib_buf__Iterator, TEST__OperMM);
    FRIEND_TEST(Test__ucm_lib_buf__Iterator, TEST__PPOper);
    FRIEND_TEST(Test__ucm_lib_buf__Iterator, TEST__MMOper);
#endif


    /// @brief Private constructor used in overloaded operators.
    ///
    /// @param[in] mb Maximum number of items to iterate over.
    /// @param[in] cb The item number the iterator points to.
    /// @param[in] ib The value of the ini_block_ member.
    ///
    explicit Iterator(std::size_t mb, std::size_t cb, std::size_t ib) noexcept;

public:
    /// @brief Construct an iterator.
    ///
    /// @param[in] mb Maximum number of items to iterate over.
    /// @param[in] cb The item number the iterator points to.
    ///
    /// @note If the cur_block_ > end_block_ the cur_block_ is
    /// made equal to end_block_ and an end iterator is constructed.
    ///
    explicit Iterator(std::size_t mb, std::size_t cb) noexcept;

    /// @brief Construct an end iterator: cur_block_ == end_block_.
    ///
    /// @param[in] mb Maximum number of items to iterate over.
    ///
    explicit Iterator(std::size_t mb) noexcept;

    Iterator(Iterator     &&) = default;
    Iterator(Iterator const&) = delete;

    Iterator& operator=(Iterator     &&) = default;
    Iterator& operator=(Iterator const&) = delete;

    ~Iterator() = default;

    /// @brief Compare two iterators for equality
    ///
    /// The iterators are considered equal if and only if their cur_block_
    /// member variables are equal. It is the responsibility of the programmer
    /// to ensure that only iterators that are obtained from the same underlying
    /// unmodified set are compared.
    ///
    bool operator==(const Iterator& rhs) const noexcept;

    /// @brief Compare two iterators for non-equality
    ///
    /// The comparison is performed by negating the result from operator==()
    /// and the same restrictions apply.
    ///
    bool operator!=(const Iterator& rhs) const noexcept;

    /// @brief Post-increment the cur_block_ value.
    ///
    /// Saturation arithmetic operation is implemented and cur_block_ cannot
    /// exceed the value of end_block_.
    /// Once the value of cur_block_ become equal to the value of end_block_
    /// it will stay there, regardless of any subsequent arithmetic operations.
    ///
    /// @note It is an error to pass Iterator with cur_block_ == end_block_
    /// (i.e. end iterator) to any underlying method which should return a
    /// pointed by the iterator item.
    ///
    Iterator& operator++() noexcept;

    /// @brief Post-decrement the cur_block_ value.
    ///
    /// Saturation arithmetic operation is implemented and cur_block_ cannot
    /// roll over zero. Once the value of cur_block_ become equal to zero the
    /// next subtract arithmetic operation will make it an end iterator.
    ///
    /// @note It is an error to pass Iterator with cur_block_ == end_block_
    /// (i.e. end iterator) to any underlying method which should return a
    /// pointed by the iterator item.
    ///
    Iterator& operator--() noexcept;

    /// @brief Pre-increment the cur_block_ value.
    ///
    /// Saturation arithmetic operation is implemented and cur_block_ cannot
    /// exceed the value of end_block_.
    /// Once the value of cur_block_ become equal to the value of end_block_
    /// it will stay there, regardless of any subsequent arithmetic operations.
    ///
    /// @note It is an error to pass Iterator with cur_block_ == end_block_
    /// (i.e. end iterator) to any underlying method which should return a
    /// pointed by the iterator item.
    ///
    Iterator operator++(int) noexcept;

    /// @brief Pre-decrement the cur_block_ value.
    ///
    /// Saturation arithmetic operation is implemented and cur_block_ cannot
    /// roll over zero. Once the value of cur_block_ become equal to zero the
    /// next subtract arithmetic operation will make it an end iterator.
    ///
    /// @note It is an error to pass Iterator with cur_block_ == end_block_
    /// (i.e. end iterator) to any underlying method which should return a
    /// pointed by the iterator item.
    ///
    Iterator operator--(int) noexcept;

    /// @brief Increment the iterator with num.
    ///
    /// Saturation arithmetic operation is implemented and cur_block_ cannot
    /// exceed the value of end_block_.
    /// Once the value of cur_block_ become equal to the value of end_block_
    /// it will stay there, regardless of any subsequent arithmetic operations.
    ///
    /// @note It is an error to pass Iterator with cur_block_ == end_block_
    /// (i.e. end iterator) to any underlying method which should return a
    /// pointed by the iterator item.
    ///
   Iterator operator+(std::size_t num) noexcept;

   /// @brief Decrement the iterator with num.
   ///
   /// Saturation arithmetic operation is implemented and cur_block_ cannot
   /// roll over zero. Once the value of cur_block_ become equal to zero the
   /// next subtract arithmetic operation will make it an end iterator.
   ///
   /// @note It is an error to pass Iterator with cur_block_ == end_block_
   /// (i.e. end iterator) to any underlying method which should return a
   /// pointed by the iterator item.
   ///
  Iterator operator-(std::size_t num) noexcept;

    /// @brief Reset iterator i.e. make cur_block_ == ini_block_
    ///
    void reset() noexcept;

    /// @bried Return the value of the cur_block_ member variable.
    ///
    std::size_t curblock() const noexcept;

    /// @bried Return the value of the end_block_ member variable.
    ///
    std::size_t endblock() const noexcept;

    /// @bried Return the value of the ini_block_ member variable.
    ///
    std::size_t iniblock() const noexcept;

    /// @brief Return true if it is an end iterator.
    ///
    bool isenditer() const noexcept;

private:
    std::size_t end_block_;
    std::size_t cur_block_;
    std::size_t ini_block_;
};

inline bool Iterator::operator==(const Iterator& rhs) const noexcept
{
    return this->cur_block_ == rhs.cur_block_;
}

inline bool Iterator::operator!=(const Iterator& rhs) const noexcept
{
    return !(*this == rhs);
}

inline void Iterator::reset() noexcept
{
    cur_block_ = ini_block_;
}

inline std::size_t Iterator::curblock() const noexcept
{
    return cur_block_;
}

inline std::size_t Iterator::endblock() const noexcept
{
    return end_block_;
}

inline std::size_t Iterator::iniblock() const noexcept
{
    return ini_block_;
}

inline bool Iterator::isenditer() const noexcept
{
    return !(cur_block_ < end_block_);
}

}    // namespace buf
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_BUF__ITERATOR_H_
