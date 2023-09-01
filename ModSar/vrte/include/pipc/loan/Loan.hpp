/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef SHMEM_LOAN_HPP
#define SHMEM_LOAN_HPP

#include "LoanId.hpp"
#include "pipc/ReturnCode.hpp"
#include "pipc/queue/internal/ReturnVal.hpp"
#include "pipc/utils/Command.hpp"
#include "pipc/utils/Expect.hpp"

#include <atomic>
#include <iostream>
#include <utility>

namespace pipc
{
namespace loan
{
/**
 * @brief Loan class with book-keeping for the restitution state of one sample.
 *
 * The loan keeps track of how many debitors have returned the loan and can
 * report, whether it can be considered paid (meaning all debitors have returned
 * it).
 * Once the loan is paid, it calls the ReclaimCmd to free the sample for new
 * adventures.
 *
 * @remark
 * Thread safety: Concurrent restitutions are supported.
 * All other operations don't need to be thread-safe, as loans are first set up
 * and restitutions received at a later point in time.
 */
class Loan
{
public:
    /** @brief Deleter used to push indices back to the free list. */
    using Deleter = utils::Command_1<void*, ReturnVal, SampleId>;

public:
    /**
     * @brief Check for correct size of unsigned long data type.
     *
     * Ensure the unsigned long has a size of 8 bytes , in order for the bitwiswe operations
     * to perform as expected
     */
    static_assert(sizeof(1UL) == 8, "Size of unsigned long must be 8 bytes");

    /** @brief Default constructor. */
    inline Loan() : reclaimCmd_(), debitorStates_(0), baseId_()
    {
    }

    /** @brief Report whether the loan is considered paid. */
    inline bool isPaid()
    {
        return (debitorStates_.load(std::memory_order_relaxed) == 0UL);
    }

    /**
     * @brief Release a loan and return the reclaim cmd.
     *
     * This function is used to get a loan back without reclaiming it.
     * The reclaim command of the loan is also returned.
     *
     * @remark
     * Note that a loan can only be released, if it has no debitors left.
     * If that is not the cast, the loan will stay active and the reclaim command
     * is not given to the user.
     *
     * @param loanId The id of the loan that was received, used as key for plausibilization
     *  with this loan.
     * @param reclaimCmd The command used to reclaim the loan.
     *
     * @return ReturnCode
     * - kOk
     * - kLoanAlreadyReclaimed
     * - kLoanStillHasDebitors
     * - kSequenceCounterMismatch
     *   (could occur if we receive a restitution of a sample
     *   which has already been forcefully taken).
     */
    inline ReturnCode release(LoanId loanId, Deleter& reclaimCmd)
    {
        // Initialize newDebitorstates with != 0,
        // so we can check it for full restitution in all cases
        uint64_t newDebitorStates = 1U;
        auto ret                  = processRestitution(loanId, newDebitorStates);
        // Fast path: Single debitor & restitution was successful
        if (newDebitorStates == 0U)
        {
            reclaimCmd = reclaimCmd_;
            return ReturnCode::kOk;
        }
        // Check if restitution was fine, then we had more than one debitor
        if (ret == ReturnCode::kOk)
        {
            return ReturnCode::kLoanStillHasDebitors;
        }
        return ret;
    }

    /** @brief Reset the loan, overriding it with the given values. */
    inline void reset(const Deleter& reclaimCmd, LoanId baseId, uint64_t debitorStates)
    {
        reclaimCmd_ = reclaimCmd;
        baseId_     = baseId;
        debitorStates_.store(debitorStates, std::memory_order_relaxed);
    }

    /**
     * @brief Restitute a loan.
     *
     * Sets the bit of the associated debitor state to zero.
     * Reclaims the loan if it is fully paid.
     *
     * @return True if the restitute operation was valid, false if not.
     */
    inline ReturnCode restitute(LoanId loanId)
    {
        // Initialize newDebitorstates with != 0,
        // so we can check it for full restitution in all cases
        uint64_t newDebitorStates = 1UL;
        auto ret                  = processRestitution(loanId, newDebitorStates);
        if (newDebitorStates == 0UL)
        {
            reclaimCmd_(loanId.getSampleId());
        }
        return ret;
    }

    /** @brief Reclaim a debitor's loan forcefully. */
    inline void reclaim(DebitorId debitorId)
    {
        auto debitorStates = debitorStates_.load(std::memory_order_relaxed);
        auto bitmask       = getDebitorBitmask(debitorId);
        if ((debitorStates & bitmask) > 0UL)
        {
            uint64_t newDebitorStates;
            // HINT:
            // Due to possible concurrent restitutions we need a CAS loop
            do
            {
                newDebitorStates = (debitorStates & ~bitmask);
            } while (!debitorStates_.compare_exchange_weak(debitorStates, newDebitorStates));
            if (newDebitorStates == 0UL)
            {
                reclaimCmd_(baseId_.getSampleId());
            }
        }
    }

private:
    /**
     * @brief Convert a debitor ID to the bitmask required to operate on the
     * debitor states.
     */
    inline uint64_t getDebitorBitmask(DebitorId debitorId)
    {
        return (1UL << debitorId);
    }

    /**
     * @brief Process a restitution with a given loanId and return the new debitor bitmask.
     */
    inline ReturnCode processRestitution(LoanId loanId, uint64_t& debitorStates)
    {
        if (EXPECT_UNLIKELY(loanId.getSeqCnt() != baseId_.getSeqCnt()))
        {
            return ReturnCode::kSequenceCounterMismatch;
        }
        auto localDebitorStates = debitorStates_.load(std::memory_order_relaxed);
        auto bitmask            = getDebitorBitmask(loanId.getDebitorId());
        // Feasibility checks:
        // - The base loan ID must match this entry
        // - The debitor must not have paid the loan yet
        bool valid = ((loanId.getBaseId() == baseId_) && ((localDebitorStates & bitmask) > 0UL));
        if (EXPECT_UNLIKELY(!valid))
        {
            return ReturnCode::kLoanAlreadyReclaimed;
        }

        // HINT:
        // Due to possible concurrent restitutions we need a CAS loop
        uint64_t oldDebitorStates = localDebitorStates;
        uint64_t newDebitorStates;
        do
        {
            newDebitorStates = (oldDebitorStates & ~bitmask);
        } while (!debitorStates_.compare_exchange_weak(oldDebitorStates, newDebitorStates));

        debitorStates = newDebitorStates;
        return ReturnCode::kOk;
    }

    /** @brief The command to reclaim the loan. */
    Deleter reclaimCmd_;
    /**
     * @brief The bitfield for the debitor states.
     *
     * @remark
     * Needs to be atomic, since multiple debitors can restitute at the same time.
     */
    std::atomic<uint64_t> debitorStates_;
    /** @brief The loan's base ID. */
    LoanId baseId_;
};

} // namespace loan
} // namespace pipc

#endif // SHMEM_LOAN_HPP
