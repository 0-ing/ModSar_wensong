/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_FIELDSUBSCRIBERSERIALIZED_HPP
#define COM_BINDING_PIPC_FIELDSUBSCRIBERSERIALIZED_HPP

#include "EventSubscriberSerialized.hpp"
#include "MethodClientSerialized.hpp"
#include "binding/FieldSubscriber.hpp"
namespace com
{
namespace binding_pipc
{

/**
 * @brief 
 * 
 * @tparam TField 
 */
template<size_t N, typename TField>
class FieldSubscriberSerialized : public binding::FieldSubscriber<TField>
{
    template<typename T>
    using UniquePtr       = ara::com::UniquePtr<T>;
    using IDeserializer   = serializer::IDeserializer<TField>;
    using EventSubscriber = EventSubscriberSerialized<N, TField>;
    using Getter          = MethodClientSerialized<TField, void>;
    using GetterAsc       = com::serializer::ArgumentSerializerCarrier<0>;
    using Setter          = MethodClientSerialized<TField, TField>;
    using SetterAsc       = com::serializer::ArgumentSerializerCarrier<1, TField>;
    using PipcProviderId  = pipc::session::ProviderId;

public:

    /**
     * @brief Construct a new Field Subscriber Serialized object
     * 
     * @tparam TFieldCfg 
     * @param baseId 
     * @param fieldCfg 
     * @param eventDeserializer 
     * @param e2eChecker 
     * @param getterOutputDeserializer 
     * @param setterOutputDeserializer 
     * @param setterAsc 
     * @param getterProtector 
     * @param getterChecker 
     * @param setterProtector 
     * @param setterChecker 
     */
    template<typename TContext, typename TFieldCfg>
    FieldSubscriberSerialized(const TContext& context,
                              const TFieldCfg& fieldCfg,
                              UniquePtr<IDeserializer>&& eventDeserializer,
                              UniquePtr<e2e::IE2EChecker>&& e2eChecker,
                              UniquePtr<IDeserializer>&& getterOutputDeserializer,
                              UniquePtr<IDeserializer>&& setterOutputDeserializer,
                              UniquePtr<SetterAsc>&& setterAsc,
                              UniquePtr<e2e::IE2EChecker>&& getterChecker,
                              UniquePtr<e2e::IE2EProtector>&& setterProtector,
                              UniquePtr<e2e::IE2EChecker>&& setterChecker)
    {
        if (fieldCfg.hasGetter)
        {
            this->getter = std::make_unique<Getter>(context,
                                                    fieldCfg.getter,
                                                    std::move(getterOutputDeserializer),
                                                    std::move(getterChecker));
        }
        if (fieldCfg.hasSetter)
        {
            this->setter = std::make_unique<Setter>(context,
                                                    fieldCfg.setter,
                                                    std::move(setterAsc),
                                                    std::move(setterProtector),
                                                    std::move(setterOutputDeserializer),
                                                    std::move(setterChecker));
        }
        if (fieldCfg.hasNotifier)
        {
            this->notifier = std::make_unique<EventSubscriber>(context,
                                                               fieldCfg.notifier,
                                                               std::move(eventDeserializer),
                                                               std::move(e2eChecker));
        }

    }
};

} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_FIELDSUBSCRIBERSERIALIZED_HPP
