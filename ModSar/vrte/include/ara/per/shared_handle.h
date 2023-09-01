// --------------------------------------------------------------------------
// |              _    _ _______     .----.      _____         _____        |
// |         /\  | |  | |__   __|  .  ____ .    / ____|  /\   |  __ \       |
// |        /  \ | |  | |  | |    .  / __ \ .  | (___   /  \  | |__) |      |
// |       / /\ \| |  | |  | |   .  / / / / v   \___ \ / /\ \ |  _  /       |
// |      / /__\ \ |__| |  | |   . / /_/ /  .   ____) / /__\ \| | \ \       |
// |     /________\____/   |_|   ^ \____/  .   |_____/________\_|  \_\      |
// |                              . _ _  .                                  |
// --------------------------------------------------------------------------
//
// All Rights Reserved.
// Any use of this source code is subject to a license agreement with the
// AUTOSAR development cooperation.
// More information is available at www.autosar.org.
//
// Disclaimer
//
// This work (specification and/or software implementation) and the material
// contained in it, as released by AUTOSAR, is for the purpose of information
// only. AUTOSAR and the companies that have contributed to it shall not be
// liable for any use of the work.
//
// The material contained in this work is protected by copyright and other
// types of intellectual property rights. The commercial exploitation of the
// material contained in this work requires a license to such intellectual
// property rights.
//
// This work may be utilized or reproduced without any modification, in any
// form or by any means, for informational purposes only. For any other
// purpose, no part of the work may be utilized or reproduced, in any form
// or by any means, without permission in writing from the publisher.
//
// The work has been developed for automotive applications only. It has
// neither been developed, nor tested for non-automotive applications.
//
// The word AUTOSAR and the AUTOSAR logo are registered trademarks.
// --------------------------------------------------------------------------

#ifndef ARA_PER_SHARED_HANDLE_H
#define ARA_PER_SHARED_HANDLE_H

// maybe this must be disabled in the future, is in AUTOSAR discussion

#ifndef SHARED_HANDLE_SUPPORT_STD
#define SHARED_HANDLE_SUPPORT_STD
#endif

#ifdef SHARED_HANDLE_SUPPORT_STD
#include <memory>
#endif

#include <atomic>
#include <mutex>
#include <iostream>

namespace ara
{
namespace per
{

/// @brief Handle to a File Storage or Key-Value Storage.
///
/// A SharedHandle is returned by the functions OpenFileStorage() and OpenKeyValueStorage() and can be passed between
/// threads as needed.
///
/// It provides the abstraction that is necessary to allow thread-safe implementation of OpenFileStorage() and
/// OpenKeyValueStorage().
///
/// @traceid{SWS_PER_00362}@tracestatus{valid}
/// @uptrace{RS_PER_00002}
/// @uptrace{RS_AP_00122}
template <typename T>
class SharedHandle final
{

private:
    ///
    /// @brief template that implements a shared pointeer.
    ///        This is a helper class for the handle. It is used
    ///        to count up and down the number of references to it.
    ///        This must be done thread safe.
    ///
    template <typename P>
    class SharedPointer final
    {
    public:
        ///
        /// @brief Constructor
        ///
        /// @param [in] p pointer to object that will be handled.
        ///            This template will take over the responsibility to
        ///            delete "p"
        ///
        explicit SharedPointer(P* p) : m_counter(1U), m_item(p) {}

        ///
        /// @brief Destructor
        ///
        ~SharedPointer()
        {
#ifdef SHARED_HANDLE_SUPPORT_STD
            if (nullptr == m_std_pointer.get())
            {
                // delete item only if this is not handles by the shared pointer
                delete m_item;
            }
#else
            delete m_item;
#endif
        }

        ///
        /// @brief increment number of references.
        /// @return number of references after the incrementation
        ///
        unsigned long long increment() noexcept
        {
            return m_counter.fetch_add(1U) + 1U;
        } // unfortunately, no "add_fetch" is defined

        ///
        /// @brief decrement number of references.
        /// @return number of references after the decrementation
        ///

        unsigned long long decrement() noexcept
        {
            return m_counter.fetch_sub(1U) - 1U;
        } // unfortunately, no "sub_fetch" is defined

        ///
        /// @brief get pointer that is handle within this class
        /// @return the pointer
        ///
        P* get_item() noexcept { return m_item; }
#ifdef SHARED_HANDLE_SUPPORT_STD
        ///
        /// @brief helper function to set the (mayby temporary) shared pointer.
        ///       If this shared pointer "m_std_pointer" is set, "m_pointer" is
        ///       only a copy for faster reference and should not be deleted !
        /// @param [in] t shared pointer to object that will be handled.
        ///
        void set_std_pointer(std::shared_ptr<P> t) noexcept { m_std_pointer = t; }
#endif
    private:
        ///
        /// @brief counter of references
        ///
        std::atomic<unsigned long long> m_counter; // take biggest available counter type

        ///
        /// @brief pointer that is handled
        ///

        P* m_item;
#ifdef SHARED_HANDLE_SUPPORT_STD
        ///
        /// @brief need this to hold at least one instance of the shared pointer
        ///
        std::shared_ptr<P> m_std_pointer;
#endif
    };

public:
    ///
    /// @brief default Constructor
    ///
    ///
    explicit SharedHandle() : m_pointer(nullptr), m_mutex() {}

    ///
    /// @brief Constructor
    ///
    /// @param [in] t pointer to object that will be handled.
    ///             This template will take over the responsibility to
    ///            delete "t".
    ///
    explicit SharedHandle(T* t) : m_mutex() { m_pointer = new SharedPointer<T>(t); };
#ifdef SHARED_HANDLE_SUPPORT_STD
    ///
    /// @brief Constructor for std::shared_ptr. This will maybe be disabled in the future
    ///
    /// @param [in] t shared pointer to object that will be handled.
    ///            This template will take over the responsibility to
    ///            delete "t"
    ///

    explicit SharedHandle(std::shared_ptr<T> t) : m_mutex()
    {
        m_pointer = new SharedPointer<T>(t.get());
        m_pointer->set_std_pointer(t);
    }
#endif

    ///
    /// @brief Destructor.
    ///

    ~SharedHandle()
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        if (m_pointer && m_pointer->decrement() == 0U)
        {
            delete m_pointer;
        }
    }

    /// @brief Move constructor for SharedHandle.
    ///
    /// The source handle object is invalidated and cannot be used anymore.
    ///
    /// The operator bool() shall be used to check the state of a handle object before using any other operators of the
    /// handle object.
    ///
    /// @traceid{SWS_PER_00367}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] sh The SharedHandle object to be moved.
    SharedHandle(SharedHandle&& sh) noexcept : m_mutex()
    {
        std::lock_guard<std::mutex> guard(sh.m_mutex);
        m_pointer = sh.m_pointer;
        sh.m_pointer = nullptr;
    }

    /// @brief Move assignment operator for SharedHandle.
    ///
    /// The source handle object is invalidated and cannot be used anymore.
    ///
    /// The operator bool() shall be used to check the state of a handle object before using any other operators of the
    /// handle object.
    ///
    /// @traceid{SWS_PER_00368}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] sh The SharedHandle object to be moved.
    /// @returns The moved SharedHandle object.
    SharedHandle& operator=(SharedHandle&& sh) & noexcept
    {
        std::lock_guard<std::mutex> guard(sh.m_mutex);
        if (&sh == this)
        {
            return *this;
        }
        SharedPointer<T>* tmp = sh.m_pointer;
        sh.m_pointer = m_pointer;
        m_pointer = tmp;
        if (sh.m_pointer && sh.m_pointer->decrement() == 0U)
        {
            delete sh.m_pointer;
            sh.m_pointer = nullptr;
        }
        return *this;
    }

    /// @brief Copy constructor for SharedHandle.
    ///
    /// @traceid{SWS_PER_00369}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] sh The SharedHandle object to be copied.
    SharedHandle(const SharedHandle& sh) noexcept : m_mutex()
    {
        std::lock_guard<std::mutex> guard(sh.m_mutex);
        if (sh.m_pointer)
        {
            sh.m_pointer->increment();
        }
        m_pointer = sh.m_pointer;
    }

    /// @brief Copy assignment operator for SharedHandle.
    ///
    /// @traceid{SWS_PER_00370}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] sh The SharedHandle object to be copied.
    /// @returns The moved SharedHandle object.
    SharedHandle& operator=(const SharedHandle& sh) & noexcept
    {
        std::lock_guard<std::mutex> guard(sh.m_mutex);
        SharedPointer<T>* tmp = m_pointer;
        if (sh.m_pointer)
        {
            sh.m_pointer->increment();
        }
        m_pointer = sh.m_pointer;
        if (tmp && tmp->decrement() == 0U)
        {
            delete tmp;
        }
        return *this;
    }

    /// @brief Non-constant arrow operator.
    ///
    /// @traceid{SWS_PER_00363}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    T* operator->() noexcept
    {
        if (m_pointer)
        {
            return m_pointer->get_item();
        }
        return nullptr;
    }

    /// @brief Constant arrow operator.
    ///
    /// @traceid{SWS_PER_00364}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    const T* operator->() const noexcept
    {
        if (m_pointer)
        {
            return m_pointer->get_item();
        }
        return nullptr;
    }

    /// @brief Non-constant dereference operator.
    ///
    /// @traceid{SWS_PER_00402}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    T& operator*() noexcept
    {
        T* ret_value = operator->();
        if (ret_value)
        {
            return *ret_value;
        }
        else
        {
            exit(-1);
            return *ret_value; // never reached, added to make the compiler happy
        }
    }

    /// @brief Constant dereference operator.
    ///
    /// @traceid{SWS_PER_00403}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    const T& operator*() const noexcept
    {
        const T* ret_value = operator->();
        if (ret_value)
        {
            return *ret_value;
        }
        else
        {
            exit(-1);
            return *ret_value; // never reached, added to make the compiler happy
        }
    }

    /// @brief Handle state.
    ///
    /// True if the handle represents a valid object of the templated class, False if the handle is empty (e.g. after a
    /// move operation).
    ///
    /// Using other operators than bool() of an empty handle will result in undefined behavior.
    ///
    /// @traceid{SWS_PER_00398}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    explicit operator bool() const noexcept
    {
        if (m_pointer)
        {
            return m_pointer->get_item() != nullptr;
        }
        return false;
    }

private:
    ///
    /// @brief pointer to object with reference count.
    ///
    SharedPointer<T>* m_pointer;
    mutable std::mutex m_mutex;
};

} // namespace per
} // namespace ara

#endif // ARA_PER_SHARED_HANDLE_H
