#ifndef SESSION_SESSION_ID_HPP
#define SESSION_SESSION_ID_HPP

#include <stdint.h>

namespace pipc
{
namespace session
{
/**
 * @brief Definition of a Session Id.
 *
 * The Session Id is a unique identifier in the scope of a provider for an established session to a user.
 * It gets assigned upon a successful connection request and becomes invalid after disconnecting the associated user.
 */
using SessionId                               = uint8_t;
static constexpr SessionId INVALID_SESSION_ID = 255;

} // namespace session
} // namespace pipc

#endif // SESSION_SESSION_ID_HPP
