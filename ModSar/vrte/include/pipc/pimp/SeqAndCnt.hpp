#ifndef SEQ_AND_CNT_HPP
#define SEQ_AND_CNT_HPP

#include "pipc/e2e/Trusted.hpp"

#include <stdint.h>

namespace pipc
{
namespace pimp
{
/**
 * @brief Sequence and Counter, summarized in a struct for atomic access.
 *
 * The same class is used for both head_seq|free_cnt and tail_seq_read_cnt in
 * some of the queue implementations. It contains methods for both of the
 * variables.
 *
 * @remark
 * This class is hand-crafted to reduce the no. of required instructions for
 * increments and decrements, as they are done in a critical path in case of
 * high contention.
 * It makes use of the fact, that only the index can overflow
 * but not the count variable.
 * Both seq and cnt are stored in a 32-bit variable, seq being in the upper
 * 16-bit and cnt in the lower 16-bit.
 *
 */
template<e2e::E2EProtection Trust>
class SeqAndCnt;

template<>
class SeqAndCnt<e2e::E2EProtection::kNone>
{
public:
    constexpr SeqAndCnt(uint16_t index = 0, uint16_t count = 0) noexcept : storage_(count | (index << 16U))
    {
    }

    inline uint16_t seq()
    {
        return static_cast<uint16_t>(storage_ >> 16U);
    }

    inline uint16_t cnt()
    {
        return static_cast<uint16_t>(storage_ & 0xFFFF);
    }

    /** @brief Calculate & return the next head index and free count. */
    inline SeqAndCnt next_head()
    {
        auto tmp = *this;
        // Add one to head index, subtract one from free cnt
        tmp.storage_ -= 0xFFFF0001;
        return tmp;
    }

    /** @brief Calculate & return the next tail index and read count. */
    inline SeqAndCnt next_tail()
    {
        auto tmp = *this;
        // Add one to tail index, add one to read cnt
        tmp.storage_ += 0x00010001;
        return tmp;
    }

    /** @brief Calculate & return higher free count. */
    inline SeqAndCnt inc_free_cnt(uint16_t n)
    {
        auto tmp = *this;
        // Add only to free count
        tmp.storage_ += n;
        return tmp;
    }

    /** @brief Reduce read count in-place. */
    inline void dec_read_cnt(uint16_t n)
    {
        // Subtract only from read count
        storage_ -= n;
    }

    constexpr bool check()
    {
        return true;
        static_assert(sizeof(SeqAndCnt) <= 8, "Must be 8 Byte or less to support lock-free atomics.");
    }

private:
    uint32_t storage_;
};

template<>
class SeqAndCnt<e2e::E2EProtection::kInverse>
{
public:
    constexpr SeqAndCnt(uint16_t index = 0, uint16_t count = 0) noexcept
        : storage_(count | (index << 16U)), inverse_(~storage_)
    {
    }

    inline uint16_t seq()
    {
        return static_cast<uint16_t>(storage_ >> 16U);
    }

    inline uint16_t cnt()
    {
        return static_cast<uint16_t>(storage_ & 0xFFFF);
    }

    /** @brief Calculate & return the next head index and free count. */
    inline SeqAndCnt next_head()
    {
        auto tmp = *this;
        // Add one to head index, subtract one from free cnt
        tmp.storage_ -= 0xFFFF0001;
        tmp.inverse_ = ~tmp.storage_;
        return tmp;
    }

    /** @brief Calculate & return the next tail index and read count. */
    inline SeqAndCnt next_tail()
    {
        auto tmp = *this;
        // Add one to tail index, add one to read cnt
        tmp.storage_ += 0x00010001;
        tmp.inverse_ = ~tmp.storage_;
        return tmp;
    }

    /** @brief Calculate & return higher free count. */
    inline SeqAndCnt inc_free_cnt(uint16_t n)
    {
        auto tmp = *this;
        // Add only to free count
        tmp.storage_ += n;
        tmp.inverse_ = ~tmp.storage_;
        return tmp;
    }

    /** @brief Reduce read count in-place. */
    inline void dec_read_cnt(uint16_t n)
    {
        // Subtract only from read count
        storage_ -= n;
        inverse_ = ~storage_;
    }

    inline bool check()
    {
        return (storage_ == ~inverse_);
    }

private:
    uint32_t storage_;
    uint32_t inverse_;
};

} // namespace pimp
} // namespace pipc

#endif // SEQ_AND_CNT_HPP
