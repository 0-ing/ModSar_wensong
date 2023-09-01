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

#ifndef ARA_PER_UNIQUE_HANDLE_H
#define ARA_PER_UNIQUE_HANDLE_H

// maybe this must be disabled in the future, is in AUTOSAR discussion

#ifndef UNIQUE_HANDLE_SUPPORT_STD
#define UNIQUE_HANDLE_SUPPORT_STD
#endif

#ifdef UNIQUE_HANDLE_SUPPORT_STD
#include <memory>
#endif

#include <atomic>
#include <iostream>

namespace ara
{
namespace per
{

/// @brief Handle to a ReadAccessor or ReadWriteAccessor.
///
/// A UniqueHandle is returned by the functions OpenFileReadOnly(), OpenFileWriteOnly(), and OpenFileReadWrite().
///
/// @traceid{SWS_PER_00359}@tracestatus{valid}
/// @uptrace{RS_PER_00002}
/// @uptrace{RS_AP_00122}
template <typename T>
class UniqueHandle final
{
public:
    ///
    /// @brief Default constructor
    ///
    ///
    explicit UniqueHandle() : m_item(nullptr) {};
    ///
    /// @brief Constructor
    ///
    /// @param [in] t pointer to object that will be handled.
    ///            This template will take over the responsibility to
    ///            delete "t".
    ///
    explicit UniqueHandle(T* t) : m_item(t) {};
#ifdef UNIQUE_HANDLE_SUPPORT_STD
    ///
    /// @brief Constructor for std::unique_ptr. This will maybe be disabled in the future
    ///
    /// @param [in] t unique pointer to object that will be handled.
    ///            This template will take over the responsibility to
    ///            delete "t"
    ///
    explicit UniqueHandle(std::unique_ptr<T>&& t) { m_item = t.release(); }
#endif
    ///
    /// @brief Destructor.
    ///
    ~UniqueHandle()
    {
        T* item;
        item = m_item.exchange(nullptr);
        delete item;
    }
    /// @brief Move constructor for UniqueHandle.
    ///
    /// The source handle object is invalidated and cannot be used anymore.
    ///
    /// The operator bool() shall be used to check the state of a handle object before using any other operators of the
    /// handle object.
    ///
    /// @traceid{SWS_PER_00371}@tracestatus{valid}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] uh The UniqueHandle object to be moved.
    UniqueHandle(UniqueHandle&& uh) noexcept { m_item = uh.m_item.exchange(nullptr); }

    /// @brief Move assignment operator for UniqueHandle.
    ///
    /// The source handle object is invalidated and cannot be used anymore.
    ///
    /// The operator bool() shall be used to check the state of a handle object before using any other operators of the
    /// handle object.
    ///
    /// @traceid{SWS_PER_00372}@tracestatus{valid}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] uh The UniqueHandle object to be moved.
    /// @returns The moved UniqueHandle object.
    UniqueHandle& operator=(UniqueHandle&& uh) & noexcept
    {
        m_item = uh.m_item.exchange(nullptr);
        return *this;
    }

    /// @brief The copy constructor for UniqueHandle shall not be used.
    ///
    /// @traceid{SWS_PER_00373}@tracestatus{valid}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_AP_00120}
    UniqueHandle(const UniqueHandle&) = delete;

    /// @brief The copy assignment operator for UniqueHandle shall not be used.
    ///
    /// @traceid{SWS_PER_00374}@tracestatus{valid}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_AP_00120}
    UniqueHandle& operator=(const UniqueHandle&) = delete;

    /// @brief Non-constant arrow operator.
    ///
    /// @traceid{SWS_PER_00360}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    T* operator->() noexcept { return m_item; }

    /// @brief Constant arrow operator.
    ///
    /// @traceid{SWS_PER_00361}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    const T* operator->() const noexcept { return m_item; }

    /// @brief Non-constant dereference operator.
    ///
    /// @traceid{SWS_PER_00400}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    T& operator*() noexcept
    {
        if (m_item)
        {
            return *m_item;
        }
        else
        {
            exit(-1);
            return *m_item; // never reached, added to make the compiler happy
        }
    }

    /// @brief Constant dereference operator.
    ///
    /// @traceid{SWS_PER_00401}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    const T& operator*() const noexcept
    {
        if (m_item)
        {
            return *m_item;
        }
        else
        {
            exit(-1);
            return *m_item; // never reached, added to make the compiler happy
        }
    }

    /// @brief Handle state.
    ///
    /// True if the handle represents a valid object of the templated class, False if the handle is empty (e.g. after a
    /// move operation).
    ///
    /// Using other operators than bool() of an empty handle will result in undefined behavior.
    ///
    /// @traceid{SWS_PER_00399}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    explicit operator bool() const noexcept { return m_item != nullptr; }

private:
    ///
    /// @brief pointer to object
    ///
    std::atomic<T*> m_item;
};

} // namespace per
} // namespace ara

#endif // ARA_PER_UNIQUE_HANDLE_H
