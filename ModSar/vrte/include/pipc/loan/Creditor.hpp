/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_LOAN_CREDITOR_HPP
#define PIPC_LOAN_CREDITOR_HPP

#include "Loan.hpp"
#include "SamplePtr.hpp"
#include "pipc/Logger.hpp"
#include "pipc/ReturnCode.hpp"
#include "pipc/utils/ErrorHandler.hpp"
#include "pipc/utils/Expect.hpp"

#include <array>
#include <iostream>

namespace pipc
{
namespace loan
{
/**
 * @brief Creditor class for giving and restituting loans.
 *
 * The Creditor contains a list of loans and provides API functions, which
 * facilitate the management of those (giving out a loan, restitutions,
 * clean-up when all restitutes are received...).
 * Each loan has a unique loan ID, which is a mixture of a sequence counter and
 * an index. The sequence counter is used as a plausibilization mechanism for a
 * timely corelation, the index is used for O(1) mapping of the right loan
 * entry.
 *
 * @todo
 * Think of NLoans stating an upper bound and initializing the Creditor with
 * any number below that for the future (needs to be supported well by the runtime).
 */
template<size_t NLoans>
class Creditor
{
public:
    /** @brief Deleter used to push indices back to the free list. */
    using Deleter = utils::Command_1<void*, ReturnVal, SampleId>;

    constexpr Creditor() : loans_(), nextSeqCnt_(0U)
    {
    }

    /**
     * @brief Get the no. of currently active loans.
     *
     * @remark
     * Used mainly for testing.
     */
    size_t getActiveLoans()
    {
        size_t ret = 0;
        for (auto& loan : loans_)
        {
            if (!loan.isPaid())
            {
                ret++;
            }
        }
        return ret;
    }

    /**
     * @brief Loan a sample and return the associated loan ID.
     *
     * @return  ReturnCode
     * - kOk
     * - kLoanAlreadyReclaimed
     * - kSequenceCounterMismatch
     * (could occur if we receive a restitution of a sample
     *  which has already been forcefully taken).
     */
    template<typename T>
    inline LoanId loan(SamplePtr<T>& ptr, uint64_t debitorStates)
    {
        Loan& loan = loans_[ptr.getSampleId()];
        // Hint:
        // This can only happen if the restitution logic has a programming
        // error
        if (!loan.isPaid())
        {
            utils::ErrorHandler::CriticalError(utils::ErrorType::kGeneral,
                                               "Internal error, trying to reset loan which wasn't restituted yet.");
        }

        static_cast<void>(ptr.release());
        auto loanId = nextLoanId(ptr.getSampleId());
        loan.reset(ptr.deleter_, loanId, debitorStates);

        return loanId;
    }

    /**
     * @brief Release a loan and retrieve the reclaimCmd.
     *
     * @return ReturnCode
     * - kOk
     * - kLoanAlreadyReclaimed
     * - kSequenceCounterMismatch
     * (could occur if we receive a restitution of a sample
     *  which has already been forcefully taken).
     *
     * @remark
     * Thread safety: Thread-safe through loan's restitute function.
     */
    inline ReturnCode release(LoanId loanId, Loan::Deleter& reclaimCmd)
    {
        size_t idx = loanId.getSampleId();
        if (EXPECT_UNLIKELY(idx > NLoans))
        {
            return ReturnCode::kSampleIdOutOfRange;
        }
        auto& loan = loans_[idx];
        return loan.release(loanId, reclaimCmd);
    }

    /**
     * @brief Process a restitution.
     *
     * @return  ReturnCode
     * - kOk
     * - kLoanAlreadyReclaimed
     * - kSampleIdOutOfRange
     * - kSequenceCounterMismatch
     * (could occur if we receive a restitution of a sample
     *  which has already been forcefully taken).
     *
     * @remark
     * Thread safety: Thread-safe through loan's restitute function.
     */
    inline ReturnCode restitute(LoanId loanId)
    {
        auto sampleId = loanId.getSampleId();
        if (EXPECT_UNLIKELY(sampleId >= NLoans))
        {
            return ReturnCode::kSampleIdOutOfRange;
        }
        auto& loan = loans_[sampleId];
        return loan.restitute(loanId);
    }

    /**
     * @brief Reclaim all loans of a debitor.
     *
     * Invoked if a debitor has disconnected.
     */
    inline void reclaim(DebitorId debitorId)
    {
        for (auto& loan : loans_)
        {
            loan.reclaim(debitorId);
        }
    }

private:
    /** @brief Calculate the next loan ID and return it. */
    inline LoanId nextLoanId(SampleId sampleId)
    {
        auto seqCnt = nextSeqCnt_++;
        return LoanId{seqCnt, sampleId};
    }

    /**
     * @brief The loans managed by the creditor.
     *
     * The indices of the loan array correspond to the Sample Ids of the loaned samples.
     */
    std::array<Loan, NLoans> loans_;
    /** @brief The next sequence counter for constructing a loan ID. */
    SeqCnt nextSeqCnt_;
};

} // namespace loan
} // namespace pipc

#endif // PIPC_LOAN_CREDITOR_HPP
