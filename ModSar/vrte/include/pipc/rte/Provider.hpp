/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PIPC_RTE_PROVIDER_HPP
#define PIPC_RTE_PROVIDER_HPP

#include "IApp.hpp"
#include "IRuntime.hpp"
#include "StandaloneRuntime.hpp"
#include "pipc/protocol/DefaultLayer.hpp"
#include "pipc/protocol/Layer.hpp"
#include "pipc/protocol/Protocol.hpp"
#include "pipc/session/ProviderEndpoint.hpp"

namespace pipc
{
namespace rte
{
template<size_t NUsers, typename TAppLayer = protocol::DefaultLayer, typename TAppPtmpLayer = protocol::DefaultLayer>
class Provider : public IApp
{
    using BaseClass = IApp;

public:
    using Endpoint = session::ProviderEndpoint<NUsers, TAppLayer, TAppPtmpLayer>;
    using BaseClass::BaseClass;

protected:
    /** @brief Protected constructor without runtime registration, only called by inherited classes. */
    Provider(session::ProviderId providerId, rte::IRuntime& runtime = rte::StandaloneRuntime::GetInstance())
        : endpoint_(), runtime_(runtime)
    {
        endpoint_.template getLayer<protocol::kSession>().init(providerId);
    }

    /** @brief Protected constructor with callback pass-through, only called by inherited classes. */
    template<typename... TCallbacks>
    Provider(session::ProviderId providerId, rte::IRuntime& runtime, TCallbacks&&... callbacks)
        : endpoint_(), runtime_(runtime)
    {
        endpoint_.template getLayer<protocol::kSession>().init(providerId);
        auto& dispatcher = runtime.getDispatcher();
        auto port        = dispatcher.registerCbk(std::forward<TCallbacks>(callbacks)..., *this);
        getTransportLayer().setSrcPort(port);
        if (port != transport::INVALID_PORT)
        {
            // TODO: Can we get an invalid ReturnCode?
            runtime_.registerProvider(*this);
        }
        else
        {
            PIPC_LOG_ERROR() << "Couldn't register Provider with ProviderId " << providerId.toString() << std::endl;
        }
    }
    /**
     * @brief Protected destructor, only called by inherited classes.
     */
    ~Provider()
    {
        auto port = getPort();
        if (port != transport::INVALID_PORT)
        {
            auto& dispatcher = runtime_.getDispatcher();
            dispatcher.unregisterCbk(port);
            runtime_.unregisterProvider(*this);
        }
    }

    /** @brief Wrapper to receive a msg. */
    static void Receive(Provider& obj, pimp::Socket& socket, protocol::Placeholder* msg)
    {
        obj.endpoint_.receive(*msg, socket);
    }

public:
    /** @brief Shortcut to get the app layer. */
    constexpr TAppPtmpLayer& getAppLayer()
    {
        return endpoint_.template getLayer<protocol::kApp>();
    }

    /** @brief Shortcut to get the session layer. */
    constexpr auto& getSessionLayer()
    {
        return endpoint_.template getLayer<protocol::kSession>();
    }

    /** @brief Shortcut to get the transport layer. */
    constexpr auto& getTransportLayer()
    {
        return endpoint_.template getLayer<protocol::kTransport>();
    }

    /** @brief Get the ProviderId the Provider is offering. */
    const ProviderId& getProviderId() override
    {
        return endpoint_.template getLayer<protocol::kSession>().getProviderId();
    }

    /** @brief Check whether this App is a Provider or a User. */
    bool isProvider() override
    {
        return true;
    }

    /** @brief Inform the app that a Provider has become available. */
    void notifyProviderOnline(Socket&, Port) override
    {
    }

    /** @brief Inform the app that a Provider has become unavailable. */
    void notifyProviderOffline() override
    {
    }

    /** @brief Inform the app that a socket has become unavailable. */
    void notifySocketOffline(Socket& socket) override
    {
        endpoint_.disconnect(socket);
    }

    /**
     * @brief Function to initialize the provider.
     */
    void init(bool) override
    {
        // Start from the session layer, as network & transport are irrelevant
        protocol::ForwardNotification<protocol::kTransport>(endpoint_, protocol::LayerStateChange::kValid);
    }

    /**
     * @brief Function to get the provider's port.
     */
    transport::Port getPort() const override
    {
        return endpoint_.template getLayer<protocol::kTransport>().getSrcPort();
    }

    /** @brief Start offering the service. */
    ReturnCode startOffer()
    {
        auto ret = getSessionLayer().startOffer();
        if (ret == ReturnCode::kOk)
        {
            runtime_.startOffer(*this);
        }
        return ret;
    }

    /** @brief Stop offering the service. */
    void stopOffer()
    {
        getSessionLayer().stopOffer();
        runtime_.stopOffer(*this);
    }

    /**
     * @brief get the number of current valid points.
     */
    size_t getValidEndpoints()
    {
        return endpoint_.getValidEndpoints();
    }

protected:
    /** @brief Endpoint info. */
    Endpoint endpoint_;
    /** @brief Associated runtime. */
    rte::IRuntime& runtime_;
};

} // namespace rte
} // namespace pipc

#endif // PIPC_RTE_PROVIDER_HPP
