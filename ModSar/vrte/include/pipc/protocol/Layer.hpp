#ifndef PROTOCOL_LAYER_HPP
#define PROTOCOL_LAYER_HPP

#include "pipc/utils/String.hpp"

#include <stdint.h>

namespace pipc
{
namespace protocol
{
enum LayerType
{
    kNetwork = 0,
    kTransport,
    kSession,
    kApp
};

/**
 * @brief A generic state definition.
 *
 * A layer's state can be one of...
 *  - kValid    : Fully functional (e.g. a working socket)
 *  - kInvalid  : Unusable (e.g. a broken socket or a denied
 *                connection)
 *  - kIdle     : Not valid yet and can be requested to trigger a
 *                validation (e.g. inactive session)
 *  - kBusy     : Temporarily unusable due to pending action
 *                (e.g. connection pending)
 */
enum class LayerState : uint8_t
{
    kValid = 0,
    kInvalid,
    kIdle,
    kBusy
};
/**
 * @brief A generic state change definition for notifications.
 *
 * Similar to State but without kBusy, which does not require
 * a notification.
 */
enum class LayerStateChange : uint8_t
{
    kValid = 0,
    kInvalid,
    kIdle
};

/**
 * @brief Return a string representation for LayerStateChange.
 *
 * @todo
 * Should not be static inline.
 */
static inline utils::String ToString(LayerStateChange change)
{
    switch (change)
    {
    case LayerStateChange::kValid:
        return "LayerStateChange::kValid";
    case LayerStateChange::kInvalid:
        return "LayerStateChange::kInvalid";
    case LayerStateChange::kIdle:
        return "LayerStateChange::kIdle";
    }
    // HINT: This code is unreachable
    return "ERR_ADD_STRING_REPRESENTATION";
}

} // namespace protocol
} // namespace pipc

#endif // PROTOCOL_LAYER_HPP
