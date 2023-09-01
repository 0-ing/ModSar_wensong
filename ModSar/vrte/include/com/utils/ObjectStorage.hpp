//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      ObjectStorage.hpp
/// @brief     Class for static storage of objects
/// @copyright Robert Bosch GmbH 2021
/// @author    Jochen
//=============================================================================
#ifndef COM_UTILS_OBJECT_STORAGE_HPP
#define COM_UTILS_OBJECT_STORAGE_HPP

#include "ara/com/types.h"

#include <atomic>
#include <functional>
#include <type_traits>
#include <utility>

namespace com
{
namespace utils
{
/**
 * @brief Class to manage storage of deserialized objects (in order to avoid Heap usage).
 *
 * \remark This class does not protect against concurrent allocation. If a protection is desired, the user
 * must take care of this for calls to allocateFreeObject().
 */
template<size_t N, typename SampleType>
class ObjectStorage
{
public:
    using SampleAllocateePtr = ara::com::SampleAllocateePtr<SampleType>;
    using LoanedPtr          = pipc::loan::LoanedSamplePtr<SampleType>;
    using StorageSlot        = typename std::aligned_storage<sizeof(SampleType), alignof(SampleType)>::type;
    static_assert(sizeof(StorageSlot) >= sizeof(SampleType), "StorageSlot must be big enough to hold a SampleType.");
    static_assert(alignof(StorageSlot) >= alignof(SampleType),
                  "StorageSlot align to at least the SampleType's alignment.");

    ObjectStorage()
    {
        // Storage is empty in the beginning
        for (size_t i = 0; i < N; i++)
        {
            freearray_[i] = true;
        }
        used_ = 0; // INVARIANT: Used is always equal to the number of false entries in freearray
    }

    // Currently no need for any of these so delete them
    ObjectStorage(const ObjectStorage&) = delete;
    ObjectStorage(ObjectStorage&&)      = delete;
    ObjectStorage& operator=(const ObjectStorage&) = delete;
    ObjectStorage& operator=(ObjectStorage&&) = delete;

    uint32_t getSize() const
    {
        return N;
    }
    uint32_t getUsed() const
    {
        return used_;
    }
    bool isFull() const
    {
        return (used_ == N);
    }

    /** @brief Fetch a SampleAlocateePtr. */
    SampleAllocateePtr getSampleAllocateePtr()
    {
        // Check availability
        if (used_ == N)
        {
            return SampleAllocateePtr{};
        }

        // Storage available, get next free spot
        uint32_t nextFree = getNextFree();

        // Default-construct the slot and return it
        SampleType* sample = new (&storage_[nextFree]) SampleType;
        pipc::utils::Command_1<void*, pipc::ReturnVal, pipc::loan::SampleId> deleter{&ObjectStorage::ResetAllocateeObject,
                                                                                     this};
        return SampleAllocateePtr{sample, deleter, static_cast<pipc::loan::SampleId>(nextFree)};
    }

    /** @brief Fetch a LoanedPtr. */
    LoanedPtr getLoanedPtr()
    {
        // Check availability
        if (used_ == N)
        {
            return LoanedPtr{};
        }

        // Storage available, get next free spot
        uint32_t nextFree = getNextFree();

        // Default-construct the slot and return it
        SampleType* sample = new (&storage_[nextFree]) SampleType;
        pipc::utils::Command_1<void*, void, pipc::loan::LoanId> deleter{&ObjectStorage::ResetLoanedObject, this};
        return LoanedPtr{sample, deleter, static_cast<pipc::loan::LoanId>(nextFree)};
    }

private:
    /**
     * @brief Static function used by SampleAllocateePtr Deleter.
     *
     * Will be called when the SampleAllocateePtr is deleted.
     *
     */
    static pipc::ReturnVal ResetAllocateeObject(ObjectStorage* obj, pipc::loan::SampleId sampleId)
    {
        obj->resetAllocateeObject(sampleId);
        return pipc::ReturnVal::kOk;
    }

    /**
     * @brief Static function used by LoanedPtr Deleter.
     *
     * Will be called when the LoanedPtr is deleted.
     *
     */
    static void ResetLoanedObject(ObjectStorage* obj, pipc::loan::LoanId loanId)
    {
        obj->resetLoanedObject(loanId);
    }

    /**
     * @brief Reset an object in the store using a SampleId.
     *
     * @note We dont need to call the destructor in case of a AllocateePtr,
     * because the AllocateePtr will call the SampleType destructor on destruction.
     *
     */
    void resetAllocateeObject(pipc::loan::SampleId sampleId)
    {
        // Update management structure
        freearray_[sampleId] = true;
        used_.fetch_sub(1, std::memory_order_release);
    }

    /**
     * @brief Reset an object in the store using a LoanId.
     *
     * @note We need to call the SampleType destructor in case of a LoanedPtr,
     * because the LoanedPtr will not call it on its destruction.
     *
     */
    void resetLoanedObject(pipc::loan::LoanId loanId)
    {
        auto ptr = reinterpret_cast<SampleType*>(&storage_[static_cast<uint32_t>(loanId)]);
        ptr->~SampleType();

        // Update management structure
        freearray_[static_cast<uint32_t>(loanId)] = true;
        used_.fetch_sub(1, std::memory_order_release);
    }

    uint32_t getNextFree()
    {
        // optimization possibility: start at the last allocated object and wrap around if needed
        uint32_t nextFree = 0U;
        while (!freearray_[nextFree])
        {
            nextFree++;
        }

        // Update amount & block the slot
        used_.fetch_add(1, std::memory_order_release);
        freearray_[nextFree] = false;

        return nextFree;
    }

    StorageSlot storage_[N];     ///< The storage (an array of StorageSlot), one element should be always free
    bool freearray_[N];          ///< Markers for free slots per array position
    std::atomic<uint32_t> used_; ///< No. of currently used slots
};

} // namespace utils
} // namespace com

#endif // COM_UTILS_OBJECT_STORAGE_HPP
