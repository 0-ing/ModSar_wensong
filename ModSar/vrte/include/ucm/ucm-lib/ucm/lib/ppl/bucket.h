//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/bucket.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_BUCKET_H_
#define UCM_AAP_LIBRARY_LIB_PPL_BUCKET_H_

#include <vector>
#include <memory>
#include <cstdint>
#include <functional>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ppl/token.h"
#include "ucm/lib/ppl/token_queue_lf.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class Bucket
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_Bucket, Constructor1);
    FRIEND_TEST(Test_Bucket, Constructor2);
    FRIEND_TEST(Test_Bucket, Constructor3);
#endif

public:
    struct Deleter
    {
        void operator()(void *p) const;
    };

    struct Config
    {
#if defined(GOOGLE_TEST)
        FRIEND_TEST(Test_BucketConfig, CheckAlign);
        FRIEND_TEST(Test_BucketConfig, CheckRsize);
        FRIEND_TEST(Test_BucketConfig, CheckNelem);
        FRIEND_TEST(Test_BucketConfig, Constructor1);
        FRIEND_TEST(Test_BucketConfig, Constructor2);
        FRIEND_TEST(Test_BucketConfig, Constructor3);
        FRIEND_TEST(Test_BucketConfig, Constructor4);
        FRIEND_TEST(Test_BucketConfig, Constructor5);
        FRIEND_TEST(Test_BucketConfig, ReleaseAcquire1);
        FRIEND_TEST(Test_BucketConfig, ReleaseAcquire2);
#endif
        std::size_t nelem_;      // Number of elements
        std::size_t rsize_;      // Requested element size
        std::size_t align_;      // Element size alignment
        std::size_t esize_{0};   // Effective element size (esize_ >= rsize_)
        std::size_t bsize_{0};   // Elements buffer size

        explicit Config(std::size_t nelem, std::size_t rsize);
        explicit Config(std::size_t nelem, std::size_t rsize, std::size_t align);

    private:
        /// @brief check if the alignment is feasible and round it up to
        /// a power of 2 if needed.
        /// @return a power of 2: alignof(std::max_align_t) <= x <= _SC_PAGESIZE
        /// @throw std::logic_error if  align > _SC_PAGESIZE
        static std::size_t check_alignment(std::size_t align);

        /// @brief Check the value of rsize
        /// @return rsize
        /// @throw std::logic_error if not valid
        static std::size_t check_rsize(std::size_t rsize);

        /// @brief Check the value of nelem
        /// @return nelem
        /// @throw std::logic_error if not valid
        static std::size_t check_nelem(std::size_t nelem);
    };

    using tokens_buffer_t = std::vector<Token>;
    using frames_buffer_t = std::unique_ptr<char[], Deleter>;

    explicit Bucket(const Bucket::Config& config);

    // copy semantics
    Bucket(const Bucket& other) = delete;
    Bucket& operator=(const Bucket&) = delete;

    // move semantic
    Bucket(Bucket&&) noexcept = delete;
    Bucket& operator=(Bucket&&) = delete;

    virtual ~Bucket() = default;

    std::size_t level() const noexcept;

    /// @brief return const reference to the Bucket configuration
    const Bucket::Config& config() const noexcept;

    /// @brief acquire a free token from the bucket
    Token* token_acquire(const Tag&) noexcept;

    /// @brief release a single token into the Bucket
    /// @note the token is discarded if token->may_discard() == true
    __attribute__((warn_unused_result))
    Token* token_release(Token* token) noexcept;

    Tag factor_increase();

    void factor_decrease();

private:
    Config config_;
    TokenQueueLF tqueue_;
    tokens_buffer_t tokens_;
    frames_buffer_t frames_;

    static frames_buffer_t frames_buff_allocate(std::size_t size);
    static tokens_buffer_t tokens_buff_allocate(std::size_t size);
};

inline const Bucket::Config& Bucket::config() const noexcept
{
    return config_;
}

inline std::size_t Bucket::level() const noexcept
{
    return tqueue_.level();
}

inline Tag Bucket::factor_increase()
{
    return tqueue_.factor_increase();
}

inline void Bucket::factor_decrease()
{
    tqueue_.factor_decrease();
}


}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_BUCKET_H_
