/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_FIELDPUBLISHERSERIALIZED_HPP
#define COM_BINDING_PIPC_FIELDPUBLISHERSERIALIZED_HPP

#include "EventPublisherSerialized.hpp"
#include "MethodServerSerialized.hpp"
#include "binding/FieldPublisher.hpp"

namespace com
{
namespace binding_pipc
{
/**
 * @brief FieldPublisher class for a serialized pipc binding.
 *
 * This is a concrete binding implementation, which provides
 * constructors to connect a FieldPublisher to serialized pipc binding
 * classes.
 */
template<typename TField>
class FieldPublisherSerialized : public binding::FieldPublisher<TField>
{
public:
    /** \brief Declarations for readability and forwarding to derived classes. */
    template<typename T>
    using UniquePtr      = ara::com::UniquePtr<T>;
    using ISerializer    = serializer::ISerializer<TField>;
    using EventPublisher = EventPublisherSerialized<1U, TField>;
    using Getter         = MethodServerSerialized<TField>;
    using GetterAdc      = com::serializer::ArgumentDeserializerCarrier<0>;
    using Setter         = MethodServerSerialized<TField, TField>;
    using SetterAdc      = com::serializer::ArgumentDeserializerCarrier<1, TField>;
    using MethodQueue    = binding::MethodQueue;
    using PipcProviderId = pipc::session::ProviderId;

    /** \brief Default constructor. */
    FieldPublisherSerialized() = default;

    /** \brief Constructor for IPC & Some/Ip deployments. */
    template<typename TContext, typename TFieldCfg>
    FieldPublisherSerialized(const TContext& context,
                             const TFieldCfg& fieldCfg,
                             UniquePtr<ISerializer>&& eventSerializer,
                             UniquePtr<e2e::IE2EProtector>&& e2eProtector,
                             UniquePtr<ISerializer>&& getterOutputSerializer,
                             UniquePtr<ISerializer>&& setterOutputSerializer,
                             UniquePtr<SetterAdc>&& setterAdc,
                             UniquePtr<e2e::IE2EChecker>&& getterChecker,
                             UniquePtr<e2e::IE2EProtector>&& getterProtector,
                             UniquePtr<e2e::IE2EChecker>&& setterChecker,
                             UniquePtr<e2e::IE2EProtector>&& setterProtector,
                             MethodQueue& methodQueue)
    {
        if (fieldCfg.hasGetter)
        {
            UniquePtr<GetterAdc> getterAdc{new GetterAdc{}};
            this->getter = std::make_unique<Getter>(context,
                                                    fieldCfg.getter,
                                                    methodQueue,
                                                    std::move(getterAdc),
                                                    std::move(getterChecker),
                                                    std::move(getterOutputSerializer),
                                                    std::move(getterProtector));

            this->setDefaultGetter();
        }
        if (fieldCfg.hasSetter)
        {
            this->setter = std::make_unique<Setter>(context,
                                                    fieldCfg.setter,
                                                    methodQueue,
                                                    std::move(setterAdc),
                                                    std::move(setterChecker),
                                                    std::move(setterOutputSerializer),
                                                    std::move(setterProtector));
        }
        if (fieldCfg.hasNotifier)
        {
            this->notifier = std::make_unique<EventPublisher>(context,
                                                              fieldCfg.notifier,
                                                              std::move(eventSerializer),
                                                              std::move(e2eProtector));
        }
    }
};

} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_FIELDPUBLISHERSERIALIZED_HPP
