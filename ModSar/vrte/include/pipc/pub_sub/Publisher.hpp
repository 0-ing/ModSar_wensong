/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PUB_SUB_PUBLISHER_HPP
#define PUB_SUB_PUBLISHER_HPP

#include "PublisherBase.hpp"
#include "pipc/transport/Port.hpp"

namespace pipc
{
namespace pub_sub
{
/**
 * @brief Publisher for data of type T.
 *
 * @todo
 * Error handling when sending msgs.
 */
template<typename T>
class Publisher : public internal::PublisherBase<>
{
    using BaseClass = internal::PublisherBase<>;

public:
    /** @brief Constructor with registering at the runtime. */
    Publisher(session::ProviderId providerId, rte::IRuntime& runtime = rte::StandaloneRuntime::GetInstance())
        : PublisherBase(providerId, runtime, &BaseClass::Receive)
    {
    }

    /** @brief Send data to all subscribers. */
    inline void send(const T& value)
    {
        if (EXPECT_UNLIKELY(this->getSessionLayer().getState() != protocol::LayerState::kValid))
        {
            PIPC_LOG_ERROR() << "Publisher: Cannot send while not offering." << std::endl;
            return;
        }

        this->getAppLayer().sendData(endpoint_, value);
    }
};

} // namespace pub_sub
} // namespace pipc

#endif // PUB_SUB_PUBLISHER_HPP
