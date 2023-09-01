//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file abort.h
/// @brief Interface to ara::core::Abort
//==============================================================================

#ifndef ARA_CORE_ABORT_H_
#define ARA_CORE_ABORT_H_

namespace ara {
namespace core {

    /// @brief A function declaration with the correct prototype for SetAbortHandler().
    ///
    /// This declaration exists only for providing a function type that includes "noexcept" and that acts
    /// as base type for a type alias, which is defined in SWS_CORE_00050.
    ///
    /// This compensates for the fact that the C++ standard (up to and including C++14) prohibits that
    /// "noexcept" appears in an alias-declaration.
    ///
    /// There is no implementation of this function
    ///
    /// @traceid{SWS_CORE_00053}
    void AbortHandlerPrototype() noexcept;

    /// @brief The type of a handler for SetAbortHandler().
    ///
    /// @traceid{SWS_CORE_00050}
    using AbortHandler = decltype(&AbortHandlerPrototype);

    /// @brief Set a custom global Abort handler function and return the previously installed one.
    ///
    /// By setting nullptr, the implementation may restore the default handler instead.
    ///
    /// This function can be called from multiple threads simultaneously; these calls are performed in
    /// an implementation-defined sequence.
    ///
    /// @param handler a custom Abort handler (or nullptr) description
    ///
    /// @returns the previously installed Abort handler (or nullptr if none was installed)
    ///
    /// @traceid{SWS_CORE_00051}
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wnoexcept-type"
    AbortHandler SetAbortHandler(AbortHandler handler) noexcept;
    #pragma GCC diagnostic pop

    /// @brief Abort the current operation.
    ///
    /// This function will never return to its caller. The stack is not unwound: destructors of variables
    /// with automatic storage duration are not called.
    ///
    /// @param text a custom text to include in the log message being output description
    ///
    /// @traceid{SWS_CORE_00052}
    [[noreturn]] void Abort(char const* text) noexcept;

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_ABORT_H_
