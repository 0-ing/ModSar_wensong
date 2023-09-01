#ifndef PIPC_RTE_USER_HPP
#define PIPC_RTE_USER_HPP

#include "IApp.hpp"
#include "IRuntime.hpp"
#include "StandaloneRuntime.hpp"
#include "pipc/protocol/Layer.hpp"
#include "pipc/protocol/Protocol.hpp"
#include "pipc/session/UserEndpoint.hpp"

namespace pipc
{
namespace rte
{
/**
 * @brief A Service User.
 *
 * This User class combines the User Endpoint and Runtime and connects them together.
 */
template<typename TAppLayer>
class User : public IApp
{
public:
    using Endpoint = session::UserEndpoint<TAppLayer>;

protected:
    /**
     * @brief Internal constructor for initialization of providerId & runtime.
     */
    User(session::ProviderId providerId, rte::IRuntime& runtime = rte::StandaloneRuntime::GetInstance())
        : endpoint_(), runtime_(runtime)
    {
        endpoint_.template getLayer<protocol::kSession>().init(providerId);
    }

    /** @brief Internal constructor with immediate registration for inheriting classes. */
    template<typename... TCallbacks>
    User(session::ProviderId providerId, rte::IRuntime& runtime, TCallbacks&&... callbacks) : User(providerId, runtime)
    {
        doRegistration(std::forward<TCallbacks>(callbacks)...);
    }

    /**
     * @brief Protected destructor, only called by inherited classes.
     */
    ~User()
    {
        auto port = getPort();
        if (port != transport::INVALID_PORT)
        {
            auto& dispatcher = runtime_.getDispatcher();
            dispatcher.unregisterCbk(port);
            runtime_.unregisterUser(*this);
        }
    }

    /** @brief Wrapper to receive a msg. */
    static void Receive(User& obj, pimp::Socket& socket, protocol::Placeholder* msg)
    {
        obj.endpoint_.receive(*msg, socket);
    }

public:
    /** @brief Shortcut to get the network layer. */
    constexpr typename Endpoint::NetworkLayer& getNetworkLayer()
    {
        return endpoint_.template getLayer<protocol::kNetwork>();
    }

    /** @brief Shortcut to get the transport layer. */
    constexpr typename Endpoint::TransportLayer& getTransportLayer()
    {
        return endpoint_.template getLayer<protocol::kTransport>();
    }

    /** @brief Shortcut to get the session layer. */
    constexpr typename Endpoint::SessionLayer& getSessionLayer()
    {
        return endpoint_.template getLayer<protocol::kSession>();
    }

    /** @brief Shortcut to get the app layer. */
    constexpr TAppLayer& getAppLayer()
    {
        return endpoint_.template getLayer<protocol::kApp>();
    }

    /** @brief Shortcut to get a const app layer. */
    constexpr const TAppLayer& getAppLayer() const
    {
        return endpoint_.template getLayer<protocol::kApp>();
    }

    /**
     * @brief Function to get the user's port.
     */
    transport::Port getPort() const override
    {
        return endpoint_.template getLayer<protocol::kTransport>().getSrcPort();
    }

    /** @brief Get the ProviderId the User relates to. */
    const ProviderId& getProviderId() override
    {
        return endpoint_.template getLayer<protocol::kSession>().getProviderId();
    }

    /** @brief Check whether this App is a Provider or a User. */
    bool isProvider() override
    {
        return false;
    }

    /**
     * @brief Inform the app that a Provider has become available.
     */
    void notifyProviderOnline(Socket& socket, Port port) override
    {
        endpoint_.init(socket, port);
    }

    /** @brief Inform the app that a Provider has become unavailable. */
    void notifyProviderOffline() override
    {
        if (getSessionLayer().getState() != protocol::LayerState::kInvalid)
        {
            protocol::ForwardNotification<protocol::kTransport>(endpoint_, protocol::LayerStateChange::kInvalid);
        }
    }

    /** @brief Inform the app that a socket has become unavailable. */
    void notifySocketOffline(Socket& socket) override
    {
        if ((getNetworkLayer().getSocket() == &socket)
            && (getSessionLayer().getState() != protocol::LayerState::kInvalid))
        {
            protocol::ForwardNotification<protocol::kTransport>(endpoint_, protocol::LayerStateChange::kInvalid);
        }
    }

    /**
     * @brief Function to initialize the user.
     */
    void init(bool) override
    {
        // Nothing to do for a default user..
    }

protected:
    /**
     * @brief Internal function to do the registration at the runtime.
     *
     * @tparam TCallbacks... The callbacks to be registered at the Dispatcher.
     *
     * @remark
     * This function is available as a protected member function, which can be called as
     * follow-up initialization step of their constructor where required.
     */
    template<typename... TCallbacks>
    void doRegistration(TCallbacks&&... callbacks)
    {
        auto& providerId = getSessionLayer().getProviderId();
        auto& dispatcher = runtime_.getDispatcher();
        auto port        = dispatcher.registerCbk(std::forward<TCallbacks>(callbacks)..., *this);
        getTransportLayer().setSrcPort(port);
        if (port != transport::INVALID_PORT)
        {
            // TODO: Can we get an invalid ReturnCode?
            runtime_.registerUser(*this);
        }
        else
        {
            PIPC_LOG_ERROR() << "Couldn't register User with ProviderId " << providerId.toString() << std::endl;
        }
    }

    /** @brief Endpoint info. */
    Endpoint endpoint_;
    /** @brief Associated runtime. */
    rte::IRuntime& runtime_;
};

} // namespace rte
} // namespace pipc

#endif // PIPC_RTE_USER_HPP
