#ifndef COM_COM_IPROXYMETHODFIREFORGET_HPP
#define COM_COM_IPROXYMETHODFIREFORGET_HPP

namespace ara {
namespace com {
/**
 * \brief   Template interfaces for method binding on proxy side.
 *          We have to distinguish two types of method calls (fireforget w/o return value and
 *          conventional w/ return value), for which two dedicated classes need to be provided.
 *          This is necessary due to the return type, which is void for fireforget and an
 *          ara::core::Future object for conventional methods. It is technically not feasible to
 *          provide both variants within one class (c++ does not support function overloading based
 *          on return type).
 */

/**
 * \brief Template interface for fireforget method binding on proxy side:
 *          The main purpose is the provision of a clean AUTOSAR conformant interface. Furthermore, it
 *          enables the usage of different implementations on the transport path. It is supposed to be
 *          a pure interface to allow variations in the particular implementation.
 */
template<typename... TArgs>
class IProxyMethodFireForget
{
public:
    virtual ~IProxyMethodFireForget() = default;

    /**
     * \brief   The () operator is the main interface to the application for method calls. As described
     *          in the adaptive AUTOSAR specification, the method call should look like a conventional
     *          method call on application side.
     * \remark
     * @ID{[SWS_CM_90435]}
     */
    virtual void operator()(const TArgs... args) = 0;
};

} // namespace com
} // namespace ara

#endif // COM_COM_IPROXYMETHODFIREFORGET_HPP
