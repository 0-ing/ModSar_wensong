/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_READABLECOMPONENTIDENTIFIER_HPP
#define COM_BINDING_READABLECOMPONENTIDENTIFIER_HPP

#include "ara/log/logger.h"

#include <string>

namespace com
{
namespace binding
{
/**
 * @brief Wraps a readable identifier to print decent log messages.
 *
 * TODO:
 * - In this form, the class can be reduced to a std::string and a function to generate that string.
 * - Actual optimized form would be references to the parts defined by the service.
 */
class ReadableComponentIdentifier
{
    friend std::ostream& operator<<(std::ostream& out, const ReadableComponentIdentifier& c);
    friend ara::log::LogStream& operator<<(ara::log::LogStream& out, const ReadableComponentIdentifier& c);

public:
    /**
     * @brief Construct a new Readable Component Identifier object
     *
     * @tparam ContextT The deployment context type. Must have a serviceName and an instanceId.
     * @param context The context argument
     * @param componentString Pointing to the method or event name.
     */
    template<typename ContextT>
    ReadableComponentIdentifier(const ContextT& context, const char* componentString)
    {
        readableName.append(context.serviceName);
        readableName.append("(");
        readableName.append(context.instanceId.ToString().data());
        readableName.append(")::");
        readableName.append(componentString);
    }

private:
    std::string readableName; ///< The internal variable holding the id.
};

/**
 * @brief Operator overload to allow pretty printing of ReadableComponentIdentifier
 *
 * @param os The ara::log outstream
 * @param identifier The readable id to print
 * @return ara::log::LogStream&
 */
ara::log::LogStream& operator<<(ara::log::LogStream& os, ReadableComponentIdentifier const& identifier);

/**
 * @brief Operator overload to allow pretty printing of ReadableComponentIdentifier
 *
 * This variant is mainly used for testing.
 * @param os The std outstream
 * @param identifier The readable id to print
 * @return ara::log::LogStream&
 */
std::ostream& operator<<(std::ostream& os, ReadableComponentIdentifier const& identifier);

} // namespace binding
} // namespace com

#endif // COM_BINDING_READABLECOMPONENTIDENTIFIER_HPP
