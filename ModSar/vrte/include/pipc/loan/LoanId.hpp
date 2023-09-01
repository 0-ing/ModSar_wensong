/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_LOAN_LOAN_ID_HPP
#define PIPC_LOAN_LOAN_ID_HPP

#include <cstddef>
#include <cstdint>

namespace pipc
{
namespace loan
{
/**
 * @brief The sample ID of a loan ID.
 *
 * It corresponds to the memory location of the associated SamplePool.
 */
using SampleId = uint8_t;

/**
 * @brief The sequence counter of a loan ID.
 *
 * It can be used at debitor side to check for lost samples.
 */
using SeqCnt = uint16_t;

/**
 * @brief The debitor ID of a loan ID.
 *
 * It can be used at creditor side to map the debitor to a bit position.
 */
using DebitorId = uint8_t;

/**
 * @brief The loan ID is used for O(1) mappings for the following activities:
 *
 * - Debitor: Map a loan ID to a sample in shared memory
 * - Debitor: Optionally check the sequence counter for lost samples
 * - Creditor: Map a restituted loan to a debitor
 *
 * It is a mixture of 3 separate IDs for debitor, sequence count and sample ID.
 */
class LoanId
{
public:
    /**
     * @brief Check for correct data types.
     *
     * Sizes are hard-coded in LoanId, we need furhter adaptions if we want to
     * change that.
     */
    static_assert(sizeof(SampleId) == 1, "SampleId must be a 8-bit type.");
    static_assert(sizeof(SeqCnt) == 2, "Seq counter must be a 16-bit type.");
    static_assert(sizeof(DebitorId) == 1, "DebitorId must be a 8-bit type.");

    /** @brief Default constructor. */
    constexpr LoanId() : id_()
    {
    }

    /** @brief Create a base loan ID (without debitor ID set). */
    inline LoanId(SeqCnt seqCnt, SampleId sampleId) noexcept
        : id_((static_cast<uint32_t>(seqCnt) << 8UL) | static_cast<uint32_t>(sampleId))
    {
    }

    /** @brief Assignment operator of a uint32_t. */
    inline LoanId& operator=(const uint32_t& other)
    {
        id_.fullId = other;
        return *this;
    }

    /** @brief Comparison operator. */
    inline bool operator==(const LoanId& other) const
    {
        return (id_.fullId == other.id_.fullId);
    }

    /** @brief Conversion to a uint32. */
    inline explicit operator uint32_t() const
    {
        return id_.fullId;
    }

    /** @brief Get a debitor-specific loan ID. */
    inline LoanId get(size_t debitorIdx) const
    {
        return LoanId{(static_cast<uint32_t>(debitorIdx) << 24U) | (id_.fullId & 0x00FFFFFFU)};
    }

    /** @brief Get the loan's base ID. */
    inline LoanId getBaseId() const
    {
        return LoanId{id_.fullId & 0x00FFFFFFU};
    }

    /** @brief Get the debitor ID. */
    inline DebitorId getDebitorId() const
    {
        return static_cast<DebitorId>(id_.fields.debitorId);
    }

    /** @brief Get the sequence count. */
    inline SeqCnt getSeqCnt() const
    {
        return static_cast<SeqCnt>(id_.fields.sequenceCount);
    }

    /** @brief Get the sample ID. */
    inline SampleId getSampleId() const
    {
        return id_.fields.sampleId;
    }

    /** @brief Internal constructor for a debitor-specific loan ID. */
    inline LoanId(uint32_t id) noexcept : id_(id)
    {
    }

private:
    /**
     * @brief The ID as a union of either...
     * - debitor ID
     * - sequence count
     * - sample ID
     * or a uint32_t id.
     */
    union Id
    {
        /** @brief Default constructor. */
        constexpr Id() : fullId()
        {
        }

        /** @brief Initialization with a uint32_t. */
        constexpr Id(const uint32_t id) : fullId(id)
        {
        }

        /**
         * @brief Representation as separate fields per Id.
         *
         * @todo
         * How portable is this? What about endianness?
         */
        struct Fields
        {
            uint32_t sampleId : 8;
            uint32_t sequenceCount : 16;
            uint32_t debitorId : 8;
        } fields;

        /** @brief Representation as a uint32_t. */
        uint32_t fullId;
    };

    /** @brief The LoanId as a union representation. */
    Id id_;
};

} // namespace loan
} // namespace pipc

#endif // PIPC_LOAN_LOAN_ID_HPP
