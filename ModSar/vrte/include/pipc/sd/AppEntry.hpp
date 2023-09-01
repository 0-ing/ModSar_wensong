#ifndef SD_APP_ENTRY_HPP
#define SD_APP_ENTRY_HPP

#include "pipc/rte/IApp.hpp"

#include <atomic>

namespace pipc
{
namespace sd
{
/**
 * @brief Struct used to store IApp information.
 */
struct AppEntry
{
    /** @brief Posible registration states. */
    enum class RegisterState : uint8_t
    {
        kRegistered,
        kRegistrationPending,
        kNotRegistered
    };

    /** @brief Get the entry key. */
    rte::IApp* getKey()
    {
        return app;
    }

    /** @brief Set the entry key. */
    void setKey(rte::IApp* key)
    {
        app = key;
    }

    /** @brief The IApp. */
    rte::IApp* app{nullptr};
    /** @brief The state of the entry. */
    RegisterState state{RegisterState::kNotRegistered};
};

} // namespace sd
} // namespace pipc

#endif
