//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      RingBuffer.hpp
/// @brief     Declaration/Definition of RingBuffer
/// @author    baetz
//=============================================================================
#ifndef RINGBUFFER_HPP_
#define RINGBUFFER_HPP_

#include "utils/Expectations.hpp"
#include "utils/StdReturnType.hpp"
#include "utils/Time.hpp"

namespace exm
{

namespace utils
{

/// @brief  Ring buffer functionality.
/// @tparam T Type of the ring buffer's element.
/// @tparam MAX_ELEMENTS Max number of elements of type T in the ring buffer.
template <typename T, uint32_t depth>
class RingBuffer
{
public:
    /// @brief Delete Default Constructor
    RingBuffer() = delete;

    /// @brief Constructor
    /// @param expect_ Expectations object where to signal
    RingBuffer(Expectations& expect_)
        : expect(expect_), buffer(), startValidData(0U), amountOfData(0U)
    {
    }

    /// @brief Destructor
    ~RingBuffer()
    {
    } // Not covered: Only the deleting destructor is not covered. We don't use the heap.

    /// @brief No copy constructor needed.
    RingBuffer(const RingBuffer&) = delete;

    /// @brief No copy assignment operator needed.
    RingBuffer& operator=(const RingBuffer&) = delete;

    /// @brief Default retry time (in milliseconds).
    static constexpr uint32_t RING_MS_RETRY_DEFAULT = 5U;

    /// @brief Writes a new element into the ring buffer
    /// @param newElement New element of type T to write into the buffer.
    /// @param ms_timeout If the buffer is full, how long we should retry to write into the buffer (in milliseconds).
    /// @param ms_retry If the buffer is full, frequence of the retry (in milliseconds).
    /// @return StdReturnType
    /// @retval OK Success
    /// @retval INSUFFICIENT_RESOURCES The buffer was full and it was not possible to insert the new element, even after retrying.
    /// @retval All other values: fatal error.
    StdReturnType write( const T& newElement, const uint32_t ms_timeout, const uint32_t ms_retry)
    {

        if (StdReturnType::OK != expect.Lock())
        {
            return StdReturnType::FATAL_ERROR;
        }

        size_t cancelLoop = 0U;

        // ok to cast an unsigned type into a wider signed type --> no overflow possible
        int64_t retryTime = static_cast<int64_t>(ms_timeout);

        StdReturnType ret = StdReturnType::OK;
        do
        {
            if (full())
            {
                // ok to cast an unsigned type into a wider signed type --> no overflow possible
                retryTime -= static_cast<int64_t>(ms_retry);

                if (retryTime > 0)
                {
                    DEBUG_INFO_F("write() - ring is full, wait for %dms", ms_retry);
                    if (StdReturnType::OK != expect.Unlock()) // Not covered: At least one monomorphisation is covering all branches.
                    {
                        ret = StdReturnType::FATAL_ERROR;
                        cancelLoop++;
                        continue;
                    }

                    const utils::Time t(ms_retry);
                    if (StdReturnType::OK != t.RelativeSleep()) // Not covered: At least one monomorphisation is covering all branches.
                    {
                        ret = StdReturnType::FATAL_ERROR;
                        cancelLoop++;
                    }
                    if (StdReturnType::OK != expect.Lock()) // Not covered: At least one monomorphisation is covering all branches.
                    {
                        ret = StdReturnType::FATAL_ERROR;
                        cancelLoop++;
                    }
                }
                else
                {
                    log::Log(Severity::ERROR, "write() - ring is full, timeout!");
                    ret = StdReturnType::INSUFFICIENT_RESOURCES;
                    cancelLoop++;
                }
            }
            else
            {
                const uint32_t writePos = (startValidData + amountOfData) % depth;
                buffer[writePos] = newElement;
                amountOfData += 1U;
                cancelLoop++;
            }
        } while (cancelLoop < 1U);

        if (StdReturnType::OK != expect.Unlock()) // Not covered: At least one monomorphisation is covering all branches.
        {
            ret = StdReturnType::FATAL_ERROR;
        }

        if (StdReturnType::OK == ret)
        {
            if (StdReturnType::OK != expect.SignalOneCall())
            {
                ret = StdReturnType::FATAL_ERROR;
            }
        }

        return ret;
    }

    /// @brief Reads a new element from the ring buffer and removes it
    /// @param element Pointer where to store the result.
    /// @return StdReturnType
    /// @retval OK Success
    /// @retval INSUFFICIENT_RESOURCES The buffer was empty.
    /// @retval All other values: fatal error.
    StdReturnType read(T* element)
    {
        StdReturnType ret = StdReturnType::OK;

        if (nullptr == element) // Not covered: At least one monomorphisation is covering all branches.
        {
            ret = StdReturnType::INVALID_ARGUMENTS;
        }
        else if (StdReturnType::OK != expect.Lock()) // Not covered: At least one monomorphisation is covering all branches.
        {
            ret = StdReturnType::FATAL_ERROR;
        }
        else
        {
            if (empty())
            {
                ret = StdReturnType::INSUFFICIENT_RESOURCES;
            }
            else
            {
                *element = buffer[startValidData];
                startValidData = (startValidData + 1U) % depth;
                amountOfData--;
            }

            if (StdReturnType::OK != expect.Unlock()) // Not covered: At least one monomorphisation is covering all branches.
            {
                ret = StdReturnType::FATAL_ERROR;
            }
        }

        if (StdReturnType::OK == ret)
        {
            if (StdReturnType::OK != expect.IncrementExpectationsBy(1)) // Not covered: At least one monomorphisation is covering all branches.
            {
                ret = StdReturnType::FATAL_ERROR;
            }
        }

        return ret;
    }

    /// @brief Checks if the buffer is full
    /// @return true the buffer is full
    bool full() const
    {
        return (depth == amountOfData);
    }

    /// @brief Checks if the buffer is empty
    /// @return true the buffer is empty
    bool empty() const
    {
        return (0U == amountOfData);
    }

    /// @brief Returns current number of elements in the ring
    /// @return uint32_t Number of elements
    uint32_t size() const
    {
        return amountOfData;
    }

private:
    Expectations& expect;    ///< Expectations object where to signal
    T buffer[depth];         ///< Ring buffer
    uint32_t startValidData; ///< Start of the valid data in the ring buffer
    uint32_t amountOfData;   ///< Amount of valid data in the ring
};

} // namespace utils
} // namespace exm

#endif // RINGBUFFER_HPP_
