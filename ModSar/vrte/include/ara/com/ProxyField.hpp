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
/// @file      ProxyField.hpp
/// @brief     Main class for proxy fields
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================

#ifndef ARA_COM_PROXY_FIELD_HPP
#define ARA_COM_PROXY_FIELD_HPP

#include "ara/com/IProxyField.hpp"

/** \brief Forward declaration of the ProxyFactory class */
namespace com
{
namespace service_deployment
{
template<ara::com::NetworkBindingEnum Binding>
class ProxyFactory;

} // namespace service_deployment
} // namespace com

namespace ara
{
namespace com
{
/**
 * \brief Main class as a 'frontend' for \see IProxyField.
 *
 * The bridge pattern is used to enable access to field methods without a pointer
 * dereference, as required per AR API specification. The class template can be instantiated
 * with Boolean selectors (e.g. HasGetter) to configure which public methods are available.
 *
 * \remark
 * @ID{[SWS_CM_00132]}
 * @ID{[SWS_CM_00133]}
 */
template<typename FieldType_T, bool HasGetter = true, bool HasSetter = true, bool HasNotifier = true>
class ProxyField
{
    // Make all Proxy Factories friend classes
    template<NetworkBindingEnum Binding>
    friend class ::com::service_deployment::ProxyFactory;

private:
    /**
     * \brief Definitions of conditional enablers for the specific method availabilities
     *
     * These helper functions provide a private API to define and check which subfunctions
     * are available under which conditions.
     *
     * \remark These functions need to come first in the class definition, because they need to be available
     * as default template arguments.
     */
    static inline constexpr bool HasGetSubscriptionState()
    {
        return HasNotifier;
    }
    static inline constexpr bool HasSubscribe()
    {
        return HasNotifier;
    }
    static inline constexpr bool HasUnsubscribe()
    {
        return HasNotifier;
    }
    static inline constexpr bool HasSetSubscriptionStateChangeHandler()
    {
        return HasNotifier;
    }
    static inline constexpr bool HasUnsetSubscriptionStateChangeHandler()
    {
        return HasNotifier;
    }
    static inline constexpr bool HasSetReceiveHandler()
    {
        return HasNotifier;
    }
    static inline constexpr bool HasUnsetReceiveHandler()
    {
        return HasNotifier;
    }
    static inline constexpr bool HasGetFreeSampleCount()
    {
        return HasNotifier;
    }
    static inline constexpr bool HasGetSMState()
    {
        return HasNotifier;
    }
    static inline constexpr bool HasGetNewSamples()
    {
        return HasNotifier;
    }
    static inline constexpr bool HasGetSample()
    {
        return HasNotifier;
    }
    static inline constexpr bool HasGet()
    {
        return HasGetter;
    }
    static inline constexpr bool HasSet()
    {
        return HasSetter;
    }

public:
    using FieldType            = FieldType_T;
    using IProxyFieldUniquePtr = UniquePtr<IProxyField<FieldType>>;
    using SamplePointer        = SamplePtr<const FieldType>;

    /** \brief Default constructor */
    ProxyField() = default;

    /** \brief Constructor for taking over concrete implementation of IProxyField */
    ProxyField(IProxyFieldUniquePtr&& f_pImpl) : pImpl(std::move(f_pImpl))
    {
    }

    /**
     * \brief Redirection to the field implementation's \see Subscribe() method
     *
     * \remark This method only exists, if the field is configured with a notifier.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<bool Conditional = HasSubscribe(), typename std::enable_if<Conditional == true>::type* = nullptr>
    ara::core::Result<void> Subscribe(size_t maxSampleCount)
    {
        return pImpl->Subscribe(maxSampleCount);
    }

    /**
     * \brief Redirection to the field implementation's \see Unsubscribe() method
     *
     * \remark This method only exists, if the field is configured with a notifier.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<bool Conditional = HasUnsubscribe(), typename std::enable_if<Conditional == true>::type* = nullptr>
    void Unsubscribe()
    {
        pImpl->Unsubscribe();
    }

    /**
     * \brief Redirection to the field implementation's \see GetSubscriptionState() method
     *
     * \remark This method only exists, if the field is configured with a notifier.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<bool Conditional = HasGetSubscriptionState(), typename std::enable_if<Conditional == true>::type* = nullptr>
    ara::com::SubscriptionState GetSubscriptionState() const
    {
        return pImpl->GetSubscriptionState();
    }

    /**
     * \brief Redirection to the field implementation's \see SetReceiveHandler() method
     *
     * \remark This method only exists, if the field is configured with a notifier.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<bool Conditional = HasSetReceiveHandler(), typename std::enable_if<Conditional == true>::type* = nullptr>
    ara::core::Result<void> SetReceiveHandler(ara::com::EventReceiveHandler handler)
    {
        return pImpl->SetReceiveHandler(handler);
    }

    /**
     * \brief Redirection to the field implementation's \see UnsetReceiveHandler() method
     *
     * \remark This method only exists, if the field is configured with a notifier.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<bool Conditional = HasUnsetReceiveHandler(), typename std::enable_if<Conditional == true>::type* = nullptr>
    ara::core::Result<void> UnsetReceiveHandler()
    {
        return pImpl->UnsetReceiveHandler();
    }

    /**
     * \brief Redirection to the field implementation's \see GetNewSamples() method
     *
     * \remark This method only exists, if the field is configured with a notifier.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<typename F,
             bool Conditional                                    = HasGetNewSamples(),
             typename std::enable_if<Conditional == true>::type* = nullptr>
    ara::core::Result<size_t> GetNewSamples(F&& f, size_t maxNumberOfSamples = std::numeric_limits<size_t>::max())
    {
        return pImpl->GetNewSamples(std::forward<F&&>(f), maxNumberOfSamples);
    }

    /**
     * \brief Redirection to the field implementation's \see SetSubscriptionStateChangeHandler() method
     *
     * \remark This method only exists, if the field is configured with a notifier.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<bool Conditional                                    = HasSetSubscriptionStateChangeHandler(),
             typename std::enable_if<Conditional == true>::type* = nullptr>
    ara::core::Result<void> SetSubscriptionStateChangeHandler(ara::com::SubscriptionStateChangeHandler handler)
    {
        return pImpl->SetSubscriptionStateChangeHandler(handler);
    }

    /**
     * \brief Redirection to the field implementation's \see UnsetSubscriptionStateChangeHandler() method
     *
     * \remark This method only exists, if the field is configured with a notifier.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<bool Conditional                                    = HasUnsetSubscriptionStateChangeHandler(),
             typename std::enable_if<Conditional == true>::type* = nullptr>
    void UnsetSubscriptionStateChangeHandler()
    {
        pImpl->UnsetSubscriptionStateChangeHandler();
    }

    /**
     * \brief Redirection to the field implementation's \see GetFreeSampleCount() method
     *
     * \remark This method only exists, if the field is configured with a notifier.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<bool Conditional = HasGetFreeSampleCount(), typename std::enable_if<Conditional == true>::type* = nullptr>
    size_t GetFreeSampleCount() const noexcept
    {
        return pImpl->GetFreeSampleCount();
    }

    /**
     * \brief Redirection to the field implementation's \see GetSMState() method
     *
     * \remark This method only exists, if the field is configured with a notifier.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<bool Conditional = HasGetSMState(), typename std::enable_if<Conditional == true>::type* = nullptr>
    ara::com::e2e::SMState GetSMState() const noexcept
    {
        return pImpl->GetSMState();
    }

    /**
     * \brief Redirection to the field implementation's \see Get() method
     *
     * \remark This method only exists, if the field is configured with a getter.
     *
     * \remark
     * @ID{[SWS_CM_00132]}
     */
    template<bool Conditional = HasGet(), typename std::enable_if<Conditional == true>::type* = nullptr>
    ara::core::Future<FieldType> Get()
    {
        return pImpl->Get();
    }

    /**
     * \brief Redirection to the field implementation's \see Set() method
     *
     * \remark This method only exists, if the field is configured with a setter.
     *
     * \remark
     * @ID{[SWS_CM_00133]}
     */
    template<bool Conditional = HasSet(), typename std::enable_if<Conditional == true>::type* = nullptr>
    ara::core::Future<FieldType> Set(const FieldType& value)
    {
        return pImpl->Set(value);
    }

protected:
    /**
     * \brief Redirection to the field implementation's \see GetSample() method
     *
     * \remark This method only exists, if the field is configured with a notifier.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<bool Conditional = HasGetSample(), typename std::enable_if<Conditional == true>::type* = nullptr>
    ara::core::Result<SamplePointer, ComErrc> GetSample()
    {
        return pImpl->GetSample();
    }

    IProxyFieldUniquePtr pImpl;
};

} // namespace com
} // namespace ara

#endif // ARA_COM_PROXY_FIELD_HPP
