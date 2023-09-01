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

#include "ucm/mock/sequence.h"
#include "ucm/lib/ppl/token.h"
#include "ucm/lib/ppl/token_queue_lf.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace ppl   {

class Bucket
    : virtual protected ucm::mock::Sequence
{

public:
    struct Deleter
    {
        void operator()(void *p) const;
    };

    struct Config
    {
        std::size_t nelem_{};      // Number of elements
        std::size_t rsize_{};      // Requested element size
        std::size_t align_{};      // Element size alignment
        std::size_t esize_{};   // Effective element size (esize_ >= rsize_)
        std::size_t bsize_{};   // Elements buffer size

        explicit Config(std::size_t, std::size_t)
        {
        }
		
        explicit Config(std::size_t, std::size_t, std::size_t)
        {
        }

    private:
        /// @brief check if the alignment is feasible and round it up to
        /// a power of 2 if needed.
        /// @return a power of 2: alignof(std::max_align_t) <= x <= _SC_PAGESIZE
        /// @throw std::logic_error if  align > _SC_PAGESIZE
        static std::size_t check_alignment(std::size_t) { return pop<std::size_t>(); }

        /// @brief Check the value of rsize
        /// @return rsize
        /// @throw std::logic_error if not valid
        static std::size_t check_rsize(std::size_t) { return pop<std::size_t>(); }

        /// @brief Check the value of nelem
        /// @return nelem
        /// @throw std::logic_error if not valid
        static std::size_t check_nelem(std::size_t) { return pop<std::size_t>(); }
    };

    using tokens_buffer_t = std::vector<Token>;
    using frames_buffer_t = std::unique_ptr<char[], Deleter>;

    explicit Bucket(const Bucket::Config&)
    {
    }

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
    Token* token_acquire(const Tag&) noexcept { return pop<Token*>(); }

    /// @brief release a single token into the Bucket
    /// @note the token is discarded if token->may_discard() == true
    __attribute__((warn_unused_result))
    Token* token_release(Token*) noexcept { return nullptr; }

    Tag factor_increase();

    void factor_decrease();
};

inline const Bucket::Config& Bucket::config() const noexcept
{
    return pop<Config const&>();
}

inline std::size_t Bucket::level() const noexcept
{
    return pop<std::size_t>();
}

inline Tag Bucket::factor_increase()
{
    return pop<Tag>();
}

inline void Bucket::factor_decrease()
{
    pop<void>();
}


}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_BUCKET_H_
