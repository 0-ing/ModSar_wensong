#ifndef UTILS_EXPECT_HPP
#define UTILS_EXPECT_HPP

/**
 * @brief Macros to give the compiler hints for condition probability.
 *
 * For time-critical code sections these hints provide optimization
 * possibilities to restructure the code for the 'hot path' of execution.
 *
 * Background info:
 * Code is usually structured to check for certain errors and do an early return
 * with an error code, in case there is one. In the hot execution path without
 * errors this can lead to lots of false conditions and resulting forward jumps,
 * which require a correct branch prediction to minimize the pipeline penalties.
 * However, BTB sizes are limited and non-taken branches are generally more
 * efficient than taken ones.
 *
 * This feature is encapsulated in a macro, because it is currently still
 * compiler-dependent. From C++20 on this will be part of the standard
 * (see https://en.cppreference.com/w/cpp/language/attributes/likely).
 */

#ifdef __GNUC__

#    define EXPECT_LIKELY(exp) __builtin_expect(exp, 1)
#    define EXPECT_UNLIKELY(exp) __builtin_expect(exp, 0)

#endif // __GNUC__

#endif // UTILS_EXPECT_HPP
