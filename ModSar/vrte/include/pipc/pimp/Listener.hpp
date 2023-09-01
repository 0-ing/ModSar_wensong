/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_PIMP_LISTENER_HPP
#define PIPC_PIMP_LISTENER_HPP

#include "Socket.hpp"
#include "pipc/Logger.hpp"
#include "pipc/utils/Expect.hpp"
#include "pipc/utils/Placeholder.hpp"

#include <mutex>
#include <thread>

namespace pipc
{
namespace pimp
{
/**
 * @brief Listener for a PIMP socket.
 *
 * Listens on the given socket and forwards the received messages to TReceiver.
 *
 * @tparam TReceiver The receiving component. Needs to have a receive(Socket&, Msg&) method.
 * @tparam TSocket The PIMP socket type to be used (e.g. with/without E2E protection).
 */
template<typename TReceiver, typename TSocket = Socket>
class Listener
{
public:
    using TISocket = pimp::TISocket<TSocket>;

    /** @brief Constructor with references to the socket & receiver. */
    Listener(TSocket& socket, TReceiver& receiver) : socket_(socket), receiver_(receiver), thread_(), stop_()
    {
    }

    /** @brief Destructor, which stops the listener thread. */
    ~Listener()
    {
        stop();
    }

    /**
     * @brief Poll for an input message and call the receiver on it.
     *
     * Specialization for a socket without payload protection:
     * The message can be consumed in-place and then popped from the queue.
     *
     * @remark
     * We can use this optimization as the socket listeners are single-threaded.
     */
    template<e2e::E2EProtection P = TISocket::GetPayloadProtection()>
    inline typename std::enable_if<P == e2e::E2EProtection::kNone, ReturnVal>::type poll()
    {
        utils::Placeholder* msg;
        auto ret = socket_.try_peek(msg);
        if (EXPECT_LIKELY(ret == ReturnVal::kOk))
        {
            receiver_.receive(socket_, *msg);
            socket_.try_pop();
        }
        else
        {
            if (ret != ReturnVal::kQueueEmpty)
            {
                PIPC_LOG_ERROR() << "Listener: Queue error: " << (int)ret << std::endl;
            }
        }
        return ret;
    }

    /**
     * @brief Poll for an input message and call the dispatcher on it.
     *
     * Specialization for a socket with payload protection:
     * The message needs to be popped and checked for consistency before
     * using it.
     */
    template<e2e::E2EProtection P = TISocket::GetPayloadProtection()>
    inline typename std::enable_if<P != e2e::E2EProtection::kNone, ReturnVal>::type poll()
    {
        typename Socket::SlotStorage tmp;
        auto ret = socket_.try_receive(tmp);
        if (EXPECT_LIKELY(ret == ReturnVal::kOk))
        {
            utils::Placeholder* msg = reinterpret_cast<utils::Placeholder*>(&tmp);
            receiver_.receive(socket_, *msg);
        }
        else
        {
            if (ret != ReturnVal::kQueueEmpty)
            {
                PIPC_LOG_ERROR() << "Listener: Queue error: " << (int)ret << std::endl;
            }
        }
        return ret;
    }

    /** @brief Start listening. */
    void start()
    {
        stop_ = false;
        thread_.reset(new std::thread{&Listener::listen, this});
    }

    /** @brief Stop listening. */
    void stop()
    {
        if (thread_)
        {
            stop_ = true;
            socket_.notify_self();
            thread_->join();
            thread_.reset();
        }
    }

private:
    /** @brief Listen on the socket until a closed state is recognized. */
    void listen()
    {
        do
        {
            socket_.wait();
            if (EXPECT_UNLIKELY(stop_))
            {
                break;
            }
            auto ret = poll();
            if (ret != ReturnVal::kOk)
            {
                // TODO: This could also happen in a normal scenario due to the multi producer nature,
                // make sure we get receive one more message on the next notification.
                PIPC_LOG_FATAL() << "Listener: Expected msg, got retval: " << (int)ret << std::endl;
            }
        } while (true);
    }

    /** @brief The socket that is listened on. */
    TISocket& socket_;
    /** @brief The message receiver that we forward received messages to. */
    TReceiver& receiver_;
    /** @brief The thread for listening. */
    std::unique_ptr<std::thread> thread_;
    /** @brief Flag to stop the listener thread. */
    bool stop_;
};

} // namespace pimp
} // namespace pipc

#endif // PIPC_PIMP_LISTENER_HPP
