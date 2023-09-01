#ifndef PIPC_UTILS_WARNING_HPP
#define PIPC_UTILS_WARNING_HPP

/**
 * @brief Utility macros for ignoring warnings.
 *
 * @remark
 * Whenever possible, the code should be rewritten to a pattern,
 * which makes the intent clear and doesn't lead to any warning.
 * Where the warnings are ignored, there should be a justification available!
 */

#ifdef __GNUC__
#    define DIAGNOSTIC_ERROR(w) _Pragma("GCC diagnostic error \"" w "\"")
#    define DIAGNOSTIC_IGNORE(w) _Pragma("GCC diagnostic ignored \"" w "\"")
#    define DIAGNOSTIC_PUSH _Pragma("GCC diagnostic push")
#    define DIAGNOSTIC_POP _Pragma("GCC diagnostic pop")
#else
#    define DIAGNOSTIC_ERROR(w)
#    define DIAGNOSTIC_IGNORE(w)
#    define DIAGNOSTIC_PUSH
#    define DIAGNOSTIC_POP
#endif

#endif // PIPC_UTILS_WARNING_HPP
