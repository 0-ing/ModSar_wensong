#ifndef ARA_COM_METHOD_SETTINGS_HPP
#define ARA_COM_METHOD_SETTINGS_HPP

/*
 * The macro-parameter APP_Q_MSG_SIZE_PAYLOAD defines the maximal payload of a method call _after_ serialization
 * so size changes of the payload due to serialization have to be computed in.
 *
 * Changing the parameter without recompiling the gateway and the method-library makes no sense,
 * as the method call will not be stuck at the checkpoint in the serializer_method_binding.hpp but somewhere else
 * in the lower part of the stack. Hence this value has at most an informational value to COM-users.
 *
 */
#define APP_Q_MSG_SIZE_PAYLOAD 130822

#endif // ARA_COM_METHOD_SETTINGS_HPP
