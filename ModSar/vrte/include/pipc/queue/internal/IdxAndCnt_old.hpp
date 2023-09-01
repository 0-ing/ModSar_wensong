#ifndef IDX_AND_CNT_HPP
#define IDX_AND_CNT_HPP

#include "pipc/e2e/IntegralWrapper.hpp"

#include <stdint.h>

/**
 * @brief Index and Counter, summarized in a struct for atomic access.
 *
 * The same class is used for both head_idx|free_cnt and tail_idx_read_cnt in
 * some of the queue implementations. It contains methods for both of the
 * variables.
 *
 * @remark
 * Old version of IdxAndCnt using IntegralWrapper.
 * On x64: Slower for trusted, but faster for untrusted
 * use cases.
 */
template<Trusted Trust>
class IdxAndCnt
{
public:
    using IntegralWrapper = typename IntegralWrapper<uint16_t, Trust>::type;
    constexpr IdxAndCnt(uint16_t index = 0, uint16_t count = 0) noexcept : idx_(index), cnt_(count)
    {
    }

    constexpr uint16_t idx()
    {
        return idx_.get();
    }

    constexpr uint16_t cnt()
    {
        return cnt_.get();
    }

    /** @brief Calculate & return the next head index and free count. */
    inline IdxAndCnt next_head()
    {
        IdxAndCnt tmp = *this;
        tmp.idx_.add(1U);
        tmp.cnt_.sub(1U);
        return tmp;
    }

    /** @brief Calculate & return the next tail index and read count. */
    inline IdxAndCnt next_tail()
    {
        IdxAndCnt tmp = *this;
        tmp.idx_.add(1U);
        tmp.cnt_.add(1U);
        return tmp;
    }

    /** @brief Calculate & return higher free count. */
    inline IdxAndCnt inc_free_cnt(uint16_t n)
    {
        IdxAndCnt tmp = *this;
        tmp.cnt_.add(n);
        return tmp;
    }

    /** @brief Reduce read count in-place. */
    inline void dec_read_cnt(uint16_t n)
    {
        // Subtract only from read count
        cnt_.sub(n);
    }

    inline bool check()
    {
        return (idx_.check() && cnt_.check());
        static_assert(sizeof(IdxAndCnt) <= 8, "Must be 8 Byte or less to support lock-free atomics.");
    }

private:
    IntegralWrapper idx_;
    IntegralWrapper cnt_;
};

#endif // IDX_AND_CNT_HPP
