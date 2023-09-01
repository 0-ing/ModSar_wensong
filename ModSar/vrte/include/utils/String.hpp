//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
///
/// @file      String.hpp
/// @author    Christopher Serr
/// @copyright Robert Bosch GmbH  2019
/// @brief     Definition of class String
///
/// A String is a mutable text buffer that stores all the characters inline. It
/// can store up to MAX_LEN characters. Various methods for safe modification
/// and inspection are provided. The String class does not dictate a specific
/// encoding, but UTF-8 is prefered. Keep in mind that a char is not necessarily
/// a full Unicode codepoint, so you need to be careful not to mess up the
/// encoding you have in mind.
///
/// Invariants that always needs to be upheld by the implementation:
///
///  1. The length of the string is smaller than or equal to the MAX_LEN
///     specified.
///  2. The capacity of the buffer is one char larger than the MAX_LEN to ensure
///     the string can always be nul-terminated.
///  3. The string starts at index 0 of the buf.
///  4. The string always has length Len().
///  5. The string is always nul-terminated.
///  6. Len always points to the nul-terminator.
///  7. There is no nul-terminator within the string.
///  8. Buf is an array, so it doesn't need to be nullptr checked.
///  9. Everything beyond the nul-terminator is considered uninitialized memory
///     and can not be read.
/// 10. For safety no actual uninitialized memory is used and the final byte in
///     the buf is always a nul-terminator.
/// 11. To uphold these invariants, the user can never get access to the raw
///     mutable buffer.
///
//=============================================================================

#ifndef UTILS_STRING_HPP
#define UTILS_STRING_HPP

#include "StdReturnType.hpp"
#include "utils/Try.hpp"
#include "utils/Types.hpp"
#include "utils/c/errno.hpp"  //wrapper to prevent direct inclusion of libc headers
#include "utils/c/limits.hpp" //wrapper to prevent direct inclusion of libc headers
#include "utils/c/stdarg.hpp" //wrapper to prevent direct inclusion of libc headers
#include "utils/c/stdio.hpp"  //wrapper to prevent direct inclusion of libc headers
#include "utils/c/stdlib.hpp" //wrapper to prevent direct inclusion of libc headers
#include "utils/c/string.hpp" //wrapper to prevent direct inclusion of libc headers
#include "utils/Array.hpp"
#include <unistd.h>

namespace exm
{
namespace utils
{

/// @brief A String is a mutable text buffer that stores all the characters
/// inline. It can store up to MAX_LEN characters. Various methods for safe
/// modification and inspection are provided. The String class does not dictate
/// a specific encoding, but UTF-8 is prefered. Keep in mind that a char is not
/// necessarily a full Unicode codepoint, so you need to be careful not to mess
/// up the encoding you have in mind.
template <size_t MAX_LEN>
class String
{
public:
    /// @brief The full capacity of the string's buffer. This is guaranteed to
    /// always be one char larger than the maximum length of the string, such
    /// that it can always be nul-terminated.
    static constexpr size_t const CAPACITY = MAX_LEN + 1U;

    /// @brief Returns the full capacity of the string's buffer. This is
    /// guaranteed to always be one char larger than the maximum length of the
    /// string, such that it can always be nul-terminated.
    /// @return The capacity of the string's buffer.
    static constexpr size_t Capacity() { return CAPACITY; }

    /// @brief Returns the maximum length of the string. This is equal to the
    /// MAX_LEN type argument provided to the String. The length of the string
    /// is always less than or equal to the maximum length of the string.
    /// @return The maximum length of the string.
    static constexpr size_t MaxLen() { return MAX_LEN; }

    /// @brief Checks whether the string has reached its maximum length. That is
    /// the case when the length of the string is equal to the maximum length
    /// specified as the MAX_LEN type argument. The string can't grow any larger
    /// beyond that.
    /// @warning No one may modify the String during the duration of this call.
    /// @return Returns whether the string has reached its maximum length.
    constexpr bool IsFull() const { return MAX_LEN <= len; }

    /// @brief Tries to convert a string of digits into a long.
    /// It is not possible to convert a string containing other characters as digits.
    /// @param out_value The long output value that shall be set.
    /// @return Returns whether the string got successfully converted or not.
    StdReturnType ToLong(Long& out_value)
    {
        // First we clear errno, as it is the only way we have to
        // get the error reporting of strtol().
        errno = 0; //PRQA S 3224 # errno is set in case of an error, see also POSIX specification of strtol().

        char* pEnd = nullptr;
        const char* const pStart = buf;
        const Long rv = strtol(pStart, &pEnd, 10);

        if (0 != errno) //PRQA S 3224 # errno is set in case of an error, see also POSIX specification of strtol().
        {
            return StdReturnType::NOT_APPLICABLE;
        }

        // Check that the string *really* contained only digits.
        // According to POSIX, pEnd points to the character just after
        // the digits:
        // That means that if the length of the string is equal to the
        // number of parsed characters, no other character are behind.
        const size_t len_ = utils::GetPtrDiffUnsigned(pEnd, pStart);
        if (len_ != len)
        {
            return StdReturnType::NOT_APPLICABLE;
        }

        out_value = rv;

        return StdReturnType::OK;
    }

    /// @brief Tries to convert a string of digits into a integer.
    /// It is not possible to convert a string containing other characters as digits.
    /// @param out_value The int output value that shall be set.
    /// @return Returns whether the string got successfully converted or not.
    StdReturnType ToInt(Integer& out_value)
    {
        Long rv_long = 0;
        TRY(ToLong(rv_long));

        // Note: a 'long' is always at least as wide
        // as an 'int', so we have to check if the long values
        // fits into the integer.

        if (rv_long > INT_MAX)
        {
            return StdReturnType::INVALID_STATE;
        }

        if (rv_long < INT_MIN)
        {
            return StdReturnType::INVALID_STATE;
        }

        out_value = static_cast<Integer>(rv_long);

        return StdReturnType::OK;
    }

    /// @brief Given a start and end index, this function tries to copy the resulting
    /// substring into a given output variable. The end index must be less than the length
    /// of the string. If the indexes denote a valid range, the function appends all characters
    /// between start and end to the string provided as output argument.
    /// @param start The start index of the substring
    /// @param end The end index of the substring
    /// @param[out] out The string in which the substring will be stored.
    /// @return Returns whether the substring was successfully copied into the output parameter.
    /// @retval INVALID_ARGUMENTS The start index is smaller than 0 or the end index is greater than
    /// the string length.
    /// @retval GENERAL_ERROR An error occured when trying to append characters to the output
    /// parameter. @see String#TryAppendChar for more information.
    StdReturnType TryGetSubString(size_t const start, size_t const end, String& out)
    {
        if(start < 0 || end > len || start > end)
        {
            return StdReturnType::INVALID_ARGUMENTS;
        }

        // Wiping the previous content of the output string
        out.Clear();

        for(size_t index = start; index < end; index++)
        {
            if(StdReturnType::OK != out.TryAppendChar(buf[index]))
            {
                return StdReturnType::GENERAL_ERROR;
            }
        }

        return StdReturnType::OK;
    }

    /// @brief Tries to retrieve the index of the first occurance of a character
    /// in the string. If the character given as argument is present in the string
    /// it returns the index of its first occurance.
    /// @param c The character to be looked in the string
    /// @param[out] out The variable which will store the index of the character
    /// @return Returns whether the char given as argument is present in the string or not.
    /// @retval INVALID_ARGUMENTS The character given as argument is not present in the string.
    StdReturnType TryGetCharIndex(char c, size_t& out)
    {
        for(size_t i = 0; i < len; i++)
        {
            if(buf[i] == c)
            {
                out = i;
                return StdReturnType::OK;
            }
        }

        return StdReturnType::INVALID_ARGUMENTS;
    }

    /// @brief Tries to append a new character to the end of the string. This
    /// only succeeds when the string has not reached its maximum length. The
    /// character to be pushed may not be a nul-terminator.
    /// @warning You need exclusive access to the string.
    /// @param c The character to append.
    /// @return Returns whether the character successfully got appended to the
    /// end of the string.
    /// @retval INSUFFICIENT_RESOURCES The character does not fit into the
    /// string.
    /// @retval INVALID_ARGUMENTS The character is a nul-terminator and can not
    /// be appended to the string.
    StdReturnType TryAppendChar(char const c)
    {
        if (IsFull())
        {
            return StdReturnType::INSUFFICIENT_RESOURCES;
        }
        if ('\0' == c)
        {
            return StdReturnType::INVALID_ARGUMENTS;
        }
        buf[len] = c;
        SetLenAndNulTerminate(len + 1u);
        return StdReturnType::OK;
    }

    /// @brief Tries to set the string to a copy of the string instance
    /// provided. If the string provided is too large, the operation fails and
    /// the old value is preserved. Despite this not being useful, a string can
    /// be set to itself.
    /// @warning You need exclusive access to the string.
    /// @param text The text to set the current string to.
    /// @return Returns whether the string got successfully set to a copy of the
    /// string provided.
    /// @retval INSUFFICIENT_RESOURCES The string provided does not fit into our
    /// string.
    template <size_t OTHER_MAX_LEN>
    StdReturnType TrySetStr(String<OTHER_MAX_LEN> const& text)
    {
        return TrySetStr(text.AsStr());
    }

    /// @brief Tries to set the string to a copy of the string provided. If the
    /// string provided is too large or is a nullptr, the operation fails and
    /// the old value is preserved. A string can be set to itself or a subset of
    /// itself.
    /// @warning The string provided needs to be properly nul-terminated. You
    /// probably only want to use this with literals or values derived from a
    /// String.
    /// @warning You need exclusive access to the string.
    /// @param text The text to set the current string to.
    /// @return Returns whether the string got successfully set to a copy of the
    /// string provided.
    /// @retval INSUFFICIENT_RESOURCES The string provided does not fit into our
    /// string.
    /// @retval INVALID_ARGUMENTS The string provided is a nullptr.
    StdReturnType TrySetStr(char const* const text)
    {
        TRY(EnsureNotNullptr(text)); // Not covered: At least one monomorphisation is covering all branches.
        size_t const newLen = strnlen(text, CAPACITY);
        TRY(JustBoundsCheckNewLen(newLen)); // Not covered: At least one monomorphisation is covering all branches.
        char* const strBuff = buf;
        (void)memmove(strBuff, text, newLen + 1u); //PRQA S 4127 #No further check required as only move operation performed
        JustSetLenAndDontNulTerminate(newLen);
        return StdReturnType::OK;
    }

    /// @brief Tries to set the string to a copy of the string provided. If the
    /// string provided is too large or is empty, the operation fails and the
    /// old value is preserved. Despite this not being useful, a string can
    /// be set to itself, but it still fails if it's empty.
    /// @warning You need exclusive access to the string.
    /// @param text The text to set the current string to.
    /// @return Returns whether the string got successfully set to a copy of the
    /// string provided.
    /// @retval INSUFFICIENT_RESOURCES The string provided does not fit into our
    /// string.
    /// @retval INVALID_ARGUMENTS The string provided is empty.
    template <size_t OTHER_MAX_LEN>
    StdReturnType TrySetNonEmptyStr(String<OTHER_MAX_LEN> const& text)
    {
        return TrySetNonEmptyStr(text.AsStr());
    }

    /// @brief Tries to set the string to a copy of the string provided. If the
    /// string provided it too large, is empty, or is a nullptr, the operation
    /// fails and the old value is preserved. A string can be set to itself or a
    /// subset of itself, but it still fails if it's empty.
    /// @warning The string provided needs to be properly nul-terminated. You
    /// probably only want to use this with literals or values derived from a
    /// String.
    /// @warning You need exclusive access to the string.
    /// @param text The text to set the current string to.
    /// @return Returns whether the string got successfully set to a copy of the
    /// string provided.
    /// @retval INSUFFICIENT_RESOURCES The string provided does not fit into our
    /// string.
    /// @retval INVALID_ARGUMENTS The string provided is a nullptr or is empty.
    StdReturnType TrySetNonEmptyStr(char const* const text)
    {
        TRY(EnsureNotNullptr(text));
        size_t const newLen = strnlen(text, CAPACITY);
        if (0U == newLen)
        {
            return StdReturnType::INVALID_ARGUMENTS;
        }
        TRY(JustBoundsCheckNewLen(newLen));
        char* const strBuff = buf;
        (void)memmove(strBuff, text, newLen + 1U); //PRQA S 4127 #No further check required as only move operation performed
        JustSetLenAndDontNulTerminate(newLen);
        return StdReturnType::OK;
    }

    /// @brief Tries to append the provided string to the end of our string. If
    /// the string provided is too large, the operation fails and the old value
    /// is preserved. A string can be appended to itself.
    /// @warning You need exclusive access to the string.
    /// @param text The text to append to the end of our string.
    /// @return Returns whether the provided string's text got successfully
    /// appended to our string.
    /// @retval INSUFFICIENT_RESOURCES The string provided was not able to be
    /// appended to the end of our string because it would've resulted in a
    /// string that is larger than the maximum length.
    template <size_t OTHER_MAX_LEN>
    StdReturnType TryAppendStr(String<OTHER_MAX_LEN> const& text)
    {
        return TryAppendStr(text.AsStr());
    }

    /// @brief Tries to append the provided string to the end of our string. If
    /// the string provided is too large or is a nullptr, the operation fails
    /// and the old value is preserved. A string or a subset of it can be
    /// appended to itself.
    /// @warning The string provided needs to be properly nul-terminated. You
    /// probably only want to use this with literals or values derived from a
    /// String.
    /// @warning You need exclusive access to the string.
    /// @param text The text to append to the end of our string.
    /// @return Returns whether the provided string's text got successfully
    /// appended to our string.
    /// @retval INSUFFICIENT_RESOURCES The string provided was not able to be
    /// appended to the end of our string because it would've resulted in a
    /// string that is larger than the maximum length.
    /// @retval INVALID_ARGUMENTS The string provided is a nullptr.
    StdReturnType TryAppendStr(char const* const text)
    {
        TRY(EnsureNotNullptr(text));
        size_t const additionalLen = strnlen(text, CAPACITY);
        size_t const newLen = len + additionalLen;
        TRY(JustBoundsCheckNewLen(newLen));
        // Manually nul-terminate here because appending itself to itself would
        // be an overlapping range as the newly appended string would overlap
        // with the nul-terminator of the original string. memcpy only works out
        // because we don't have an overlapping range anymore, as no
        // nul-terminators are copied.
        (void)memcpy(&buf[len], text, additionalLen); //PRQA S 4127 #No further check required as only copy operation performed
        SetLenAndNulTerminate(newLen);
        return StdReturnType::OK;
    }

    /// @brief Tries to remove a character from the end of the string. For this
    /// to work, the string needs to not be empty, i.e. it needs to contain at
    /// least one character, excluding the final nul-terminator. The character
    /// is then removed from the end of the string and assigned to cOut. The
    /// string is the one character shorter. If the string was empty, cOut gets
    /// set to '\0' instead.
    /// @warning cOut MUST NOT be a reference to a char from the string. This is
    /// Undefined Behavior.
    /// @warning You need exclusive access to the string.
    /// @param[out] cOut The character that got removed.
    /// @return Returns whether a character was successfully removed from the
    /// end of the string and assigned to cOut.
    /// @retval INSUFFICIENT_RESOURCES The string is empty, no character got
    /// removed.
    StdReturnType TryPopChar(char& cOut)
    {
        if (0U == len)
        {
            cOut = '\0';
            return StdReturnType::INSUFFICIENT_RESOURCES;
        }

        size_t const newLen = len - 1u;
        cOut = buf[newLen];
        SetLenAndNulTerminate(newLen);
        return StdReturnType::OK;
    }

    /// @brief Tries to truncate the length of the string to the length
    /// provided. That means that all characters at the end of the string get
    /// removed such that the length of the string ends up with the length
    /// provided. For this to work the length provided needs to be equal or less
    /// than the length of the string.
    /// @warning You need exclusive access to the string.
    /// @param newLen The new length of the string to truncate it to.
    /// @return Returns whether the string got truncated. This may also be the
    /// case when the length provided is actually equal to the length of the
    /// string, so no characters actually got removed.
    /// @retval INVALID_ARGUMENTS The length provided was larger than the length
    /// of the string.
    StdReturnType TryTruncate(size_t const newLen)
    {
        if (newLen > len)
        {
            return StdReturnType::INVALID_ARGUMENTS;
        }

        SetLenAndNulTerminate(newLen);
        return StdReturnType::OK;
    }

    /// @brief Tries to remove a character at the index provided and returns it
    /// via cOut. The index needs to be less than the length of the string. If
    /// an out of bounds index is provided, the string is not modified and '\0'
    /// gets assigned to cOut. If the index is inbounds, the character gets
    /// removed from the string and the length of the string shrinks by one.
    /// @warning cOut MUST NOT be a reference to a char from the string. This is
    /// Undefined Behavior.
    /// @warning You need exclusive access to the string.
    /// @param[out] cOut The character that got removed.
    /// @param idx Index value of the character to be removed
    /// @return Returns whether the character successfully got removed from the
    /// string and assigned to cOut.
    /// @retval INVALID_ARGUMENTS An out of bounds index was provided. The
    /// string did not get modified and '\0' got assigned to cOut.
    StdReturnType TryRemove(char& cOut, size_t const idx)
    {
        if (idx >= len)
        {
            cOut = '\0';
            return StdReturnType::INVALID_ARGUMENTS;
        }

        cOut = buf[idx];

        (void)memmove(&buf[idx], &buf[idx + 1u], len - idx);
        JustSetLenAndDontNulTerminate(len - 1u);
        return StdReturnType::OK;
    }

    /// @brief Clears the string such that it becomes an empty string with a
    /// length of 0.
    /// @warning You need exclusive access to the string.
    void Clear() { SetLenAndNulTerminate(0U); }

    /// @brief Tries to print into the string via the printf formatting
    /// mechanism. The format specified may not be nullptr. The formatted text
    /// gets appended to the end of the string. If it does not fit at the end of
    /// string, the operation fails and the old value is preserved. The
    /// formatted text may also not contain a nul-terminator. The operation
    /// fails and the old value is preserved in that case as well.
    /// @warning The format specifier and the args MUST NOT be referencing the
    /// string to print into in any way. This is Undefined Behavior.
    /// @warning You need exclusive access to the string.
    /// @param format The printf format specifier to use.
    /// @param args The additional arguments to the printf formatting mechanism.
    /// @return Whether the formatted text got successfully appended to the end
    /// of the string.
    /// @retval INVALID_ARGUMENTS A nullptr format specifier was provided.
    /// @retval INVALID_STATE There was an encoding error when printing, the old
    /// value is preserved.
    /// @retval INVALID_STATE There was a nul-terminator in the middle of the
    /// formatted text. The old value is preserved.
    /// @retval INSUFFICIENT_RESOURCES The formatted text did not fit into the
    /// string. The old value is preserved.
    template <typename... Args>
    StdReturnType TryPrintInto(char const* const format, Args const... args)
    {
        TRY(EnsureNotNullptr(format)); // Not covered: At least one monomorphisation is covering all branches.

        Integer const additionalLen = snprintf(&buf[len], CAPACITY - len, format, args...);
        TRY(EnsureTheresNoEncodingErrorOrReNulTerminate(additionalLen)); // Not covered: At least one monomorphisation is covering all branches.

        size_t const newLen = len + static_cast<size_t>(additionalLen);
        TRY(BoundsCheckNewLenOrReNulTerminate(newLen)); // Not covered: At least one monomorphisation is covering all branches.

        TRY(EnsureThereAreNoNulTerminatorsInRangeOrReNulTerminate(len, newLen)); // Not covered: At least one monomorphisation is covering all branches.

        JustSetLenAndDontNulTerminate(newLen);
        return StdReturnType::OK;
    }

    /// @brief Tries to print into the string via the printf formatting
    /// mechanism, but with a va_list. The format specified may not be nullptr.
    /// The formatted text gets appended to the end of the string. If it does
    /// not fit at the end of string, the operation fails and the old value is
    /// preserved. The formatted text may also not contain a nul-terminator. The
    /// operation fails and the old value is preserved in that case as well.
    /// @warning The format specifier and the args MUST NOT be referencing the
    /// string to print into in any way. This is Undefined Behavior.
    /// @warning You need exclusive access to the string.
    /// @param format The printf format specifier to use.
    /// @param argp The additional arguments to the printf formatting mechanism.
    /// @return Whether the formatted text got successfully appended to the end
    /// of the string.
    /// @retval INVALID_ARGUMENTS A nullptr format specifier was provided.
    /// @retval INVALID_STATE There was an encoding error when printing, the old
    /// value is preserved.
    /// @retval INVALID_STATE There was a nul-terminator in the middle of the
    /// formatted text. The old value is preserved.
    /// @retval INSUFFICIENT_RESOURCES The formatted text did not fit into the
    /// string. The old value is preserved.
    StdReturnType TryPrintIntoWithVaList(char const* const format, va_list argp)
    {
        TRY(EnsureNotNullptr(format));

        Integer const additionalLen = vsnprintf(buf + len, CAPACITY - len, format, argp);
        TRY(EnsureTheresNoEncodingErrorOrReNulTerminate(additionalLen)); // Not covered: Can't reach failing branch

        size_t const newLen = len + static_cast<size_t>(additionalLen);
        TRY(BoundsCheckNewLenOrReNulTerminate(newLen));

        TRY(EnsureThereAreNoNulTerminatorsInRangeOrReNulTerminate(len, newLen));

        JustSetLenAndDontNulTerminate(newLen);
        return StdReturnType::OK;
    }

    /// @brief Tries to print into the string via the printf formatting
    /// mechanism. The format specified may not be nullptr. The formatted text
    /// gets appended to the end of the string. If it does not fit at the end of
    /// string, the operation does not fail. The formatted text gets appended as
    /// far as is possible. In that case you end up with a string that is the
    /// maximum length specified and the rest of the formatted text gets
    /// discarded. The formatted text may not contain a nul-terminator. The
    /// operation fails and the old value is preserved in that case.
    /// @warning The format specifier and the args MUST NOT be referencing the
    /// string to print into in any way. This is Undefined Behavior.
    /// @warning You need exclusive access to the string.
    /// @param format The printf format specifier to use.
    /// @param args The additional arguments to the printf formatting mechanism.
    /// @return Whether the formatted text got successfully appended to the end
    /// of the string.
    /// @retval INVALID_ARGUMENTS A nullptr format specifier was provided.
    /// @retval INVALID_STATE There was an encoding error when printing, the old
    /// value is preserved.
    /// @retval INVALID_STATE There was a nul-terminator in the middle of the
    /// formatted text. The old value is preserved.
    template <typename... Args>
    StdReturnType TryPrintIntoAsFarAsPossible(char const* const format, Args const... args)
    {
        TRY(EnsureNotNullptr(format)); // Not covered: At least one monomorphisation is covering all branches.

        Integer const additionalLen = snprintf(&buf[len], CAPACITY - len, format, args...);
        TRY(EnsureTheresNoEncodingErrorOrReNulTerminate(additionalLen)); // Not covered: Can't reach failing branch

        size_t const unsaturatedNewLen = len + static_cast<size_t>(additionalLen);
        size_t const newLen = SaturateNewLen(unsaturatedNewLen);

        TRY(EnsureThereAreNoNulTerminatorsInRangeOrReNulTerminate(len, newLen)); // Not covered: In reality only two branches are existing, both of which are executed

        SetLenAndNulTerminate(newLen);
        return StdReturnType::OK;
    }

    /// @brief Tries to print into the string via the printf formatting
    /// mechanism, but with a va_list. The format specified may not be nullptr.
    /// The formatted text gets appended to the end of the string. If it does
    /// not fit at the end of string, the operation does not fail. The formatted
    /// text gets appended as far as is possible. In that case you end up with a
    /// string that is the maximum length specified and the rest of the
    /// formatted text gets discarded. The formatted text may not contain a
    /// nul-terminator. The operation fails and the old value is preserved in
    /// that case.
    /// @warning The format specifier and the args MUST NOT be referencing the
    /// string to print into in any way. This is Undefined Behavior.
    /// @warning You need exclusive access to the string.
    /// @param format The printf format specifier to use.
    /// @param argp The additional arguments to the printf formatting mechanism.
    /// @return Whether the formatted text got successfully appended to the end
    /// of the string.
    /// @retval INVALID_ARGUMENTS A nullptr format specifier was provided.
    /// @retval INVALID_STATE There was an encoding error when printing, the old
    /// value is preserved.
    /// @retval INVALID_STATE There was a nul-terminator in the middle of the
    /// formatted text. The old value is preserved.
    StdReturnType TryPrintIntoAsFarAsPossibleWithVaList(char const* const format, va_list argp)
    {
        TRY(EnsureNotNullptr(format));

        Integer const additionalLen = vsnprintf(&buf[len], CAPACITY - len, format, argp);
        TRY(EnsureTheresNoEncodingErrorOrReNulTerminate(additionalLen)); // Not covered: Can't reach failing branch

        size_t const unsaturatedNewLen = len + static_cast<size_t>(additionalLen);
        size_t const newLen = SaturateNewLen(unsaturatedNewLen);

        TRY(EnsureThereAreNoNulTerminatorsInRangeOrReNulTerminate(len, newLen));

        SetLenAndNulTerminate(newLen);
        return StdReturnType::OK;
    }

    /// @brief Accesses the string as a C string. The string is properly
    /// nul-terminated, never nullptr, contains no interior nul-terminators, has
    /// the length specified via Len() and is always shorter than or equal to
    /// the maximum length.
    /// @warning No one may modify the String during the duration of this call.
    /// @warning The C string gets invalidated on modification.
    /// @warning The C String is borrowed from this String instance. It may not
    /// outlive the instance.
    /// @return The string as a C string.
    /* non-nullable */ constexpr char const* AsStr() const { return buf; }

    // The user intentionally never gets access to the buffer directly as a
    // char*. This could invalidate the invariants of the String.

    // ======================== "View" Methods =================================

    /// @brief Checks whether the string is empty. That is the case when the
    /// length of the string is equal to 0. There are no characters within the
    /// string. The string is still properly nul-terminator though.
    /// @warning No one may modify the String during the duration of this call.
    /// @return Returns whether the string is empty.
    constexpr bool IsEmpty() const { return 0U == len; }

    /// @brief Returns the length of the string in bytes. That is how many
    /// characters (chars / bytes) are within the string that are not the final
    /// nul-terminator. The length thus always points to the final
    /// nul-terminator. The length of the string is always less than or equal to
    /// the maximum length specified.
    /// @warning No one may modify the String during the duration of this call.
    /// @return The length of the string in bytes.
    constexpr size_t Len() const { return len; }

    /// @brief Tries to find the character specified in the string. A pointer to
    /// the first character, starting from the beginning of the string, that is
    /// equal to the character specified, is returned. If the character is not
    /// within the string or a nul-terminator is supposed to be searched, a
    /// nullptr is returned.
    /// @warning No one may modify the String during the duration of this call.
    /// @warning The C String is borrowed from this String instance. It may not
    /// outlive the instance.
    /// @param c The character to find in the string.
    /// @return Returns either a nullptr or a pointer to the position of the
    /// first character found, starting from the beginning of the string.
    /// @retval nullptr The string does not contain the character.
    /* nullable */ char const* TryFind(char const c) const
    {
        return static_cast<char const*>(memchr(buf, c, len));
    }

    /// @brief Tries to find the character specified in the string. A pointer to
    /// the last character, starting from the end of the string, that is equal
    /// to the character specified, is returned. If the character is not within
    /// the string or a nul-terminator is supposed to be searched, a nullptr is
    /// returned.
    /// @warning No one may modify the String during the duration of this call.
    /// @warning The C String is borrowed from this String instance. It may not
    /// outlive the instance.
    /// @param c The character to find in the string.
    /// @return Returns either a nullptr or a pointer to the position of the
    /// last character found, starting from the end of the string.
    /// @retval nullptr The string does not contain the character.
    /* nullable */ char const* TryFindReverse(char const c) const
    {
        size_t idx = len;
        while (0U < idx)
        {
            idx -= 1u;
            if (c == buf[idx])
            {
                return &buf[idx];
            }
        }
        return nullptr;
    }

    /// @brief Checks whether the character specified is in the string. If the
    /// character is not in within the string or a nul-terminator is supposed to
    /// be searched, false is returned.
    /// @warning No one may modify the String during the duration of this call.
    /// @param c The character to find in the string.
    /// @return Whether the character is in the string.
    bool Contains(char const c) const { return nullptr != TryFind(c); }

    /// @brief Checks whether the two strings are the same, i.e. they have the
    /// same length and all the characters are the same.
    /// @warning No one may modify the String during the duration of this call.
    /// @param other The other string to compare the current string to.
    /// @return Whether the two strings are the same.
    template <size_t OTHER_MAX_LEN>
    bool Eq(String<OTHER_MAX_LEN> const& other) const
    {
        return 0 == Compare(other);
    }

    /// @brief Checks whether the two strings are the same, i.e. they have the
    /// same length and all the characters are the same. Passing a nullptr
    /// always compares as false.
    /// @warning Text needs to be properly nul-terminated.
    /// You probably only want to use this with literals or values derived from
    /// a String.
    /// @warning No one may modify the String during the duration of this call.
    /// @param other The other string to compare the current string to.
    /// @return Whether the two strings are the same.
    bool Eq(char const* const other) const
    {
        Integer diffOut = 0;
        StdReturnType const result = TryCompare(diffOut, other);
        return (StdReturnType::OK == result) && (0 == diffOut);
    }

    /// @brief Compares the two strings lexically and returns an integer
    /// indicating whether the current string is less than (<0), equal to (=0),
    /// or greater than (>0) the other string if they were to be lexically
    /// sorted. If the contents of both strings are the exact same 0 is
    /// returned.
    /// @warning No one may modify the String during the duration of this call.
    /// @param other The other string to compare the current string to.
    /// @return Integer indicating the which string is larger or 0 if they are
    /// equal.
    /// @retval <0 The current string is to be ordered before the other string.
    /// @retval =0 The current string is equal to the other string.
    /// @retval >0 The current string is to be ordered after the other string.
    template <size_t OTHER_MAX_LEN>
    Integer Compare(String<OTHER_MAX_LEN> const& other) const
    {
        return strcmp(AsStr(), other.AsStr());
    }

    /// @brief Tries to compares two strings lexically and sets diffOut to an
    /// integer indicating whether the current string is less than (<0), equal
    /// to (=0), or greater than (>0) the other string if they were to be
    /// lexically sorted. The comparison fails if a nullptr is passed to the
    /// function. In that case diffOut is set to 0.
    /// @warning Text needs to be properly nul-terminated.
    /// You probably only want to use this with literals or values derived from
    /// a String.
    /// @warning No one may modify the String during the duration of this call.
    /// @param[out] diffOut The result of the comparison
    /// @param other The other string to compare the current string to.
    /// @return Whether the comparison was successful.
    /// @retval INVALID_ARGUMENTS A nullptr was passed as the other string.
    StdReturnType TryCompare(Integer& diffOut, char const* const other) const
    {
        diffOut = 0;
        TRY(EnsureNotNullptr(other));
        diffOut = strncmp(AsStr(), other, len + 1u);
        return StdReturnType::OK;
    }

private:
    /// @brief Only set the length of the string and don't nul-terminate it.
    /// @warning You need to ensure the string is still properly nul-terminated
    /// at the new length, as it would otherwise break the invariants of the
    /// class.
    /// @warning You need to manually ensure that the new length is within the
    /// bounds of the maximum length.
    /// @warning You need to manually ensure that there is no nul-terminator
    /// inside the string now.
    /// @param newLen The new length to set the length of the string to.
    void JustSetLenAndDontNulTerminate(size_t const newLen) { len = newLen; }

    /// @brief Places a nul-terminator again at the end of the string (which is
    /// indicated by its length). Use this whenever you want to discard changes
    /// you were about to make, but noticed that the function has to fail. In
    /// order to not break the invariants of the class, you still need to ensure
    /// that the string is properly nul-terminated, so you re-nul-terminate.
    void ReNulTerminate() { buf[len] = '\0'; }

    /// @brief Modifies the length of the string and places a nul-terminator
    /// there. Do this when you just changed the contents of the string.
    /// @warning You need to manually ensure that the new length is within the
    /// bounds of the maximum length.
    /// @warning You need to manually ensure that there is no nul-terminator
    /// inside the string now.
    /// @param newLen The new length to set the length of the string to and
    /// nul-terminate at.
    void SetLenAndNulTerminate(size_t const newLen)
    {
        JustSetLenAndDontNulTerminate(newLen);
        ReNulTerminate();
    }

    /// @brief Bounds checks a new length you want to set the string to. If it's
    /// larger than the maximum length, the bounds check will fail.
    /// @param newLen The new length to bounds check.
    /// @return Whether the bounds check was successful.
    /// @retval INSUFFICIENT_RESOURCES The bounds check was not successful, the
    /// string's maximum length is too short.
    static StdReturnType JustBoundsCheckNewLen(size_t const newLen)
    {
        if (MAX_LEN < newLen)
        {
            return StdReturnType::INSUFFICIENT_RESOURCES;
        }
        return StdReturnType::OK;
    }

    /// @brief Bounds checks a new length you want to set the string to. If it's
    /// larger than the maximum length, the bounds check will fail. All new
    /// contents at the end of the string will be discarded and the original
    /// nul-terminator will be placed again.
    /// @param newLen The new length to bounds check and re-nul-terminate at.
    /// @return Whether the bounds check was successful.
    /// @retval INSUFFICIENT_RESOURCES The bounds check was not successful, the
    /// string's maximum length is too short. The new contents at the end of the
    /// string got discarded and the string is properly nul-terminated again at
    /// its original length.
    StdReturnType BoundsCheckNewLenOrReNulTerminate(size_t const newLen)
    {
        if (MAX_LEN < newLen)
        {
            ReNulTerminate();
            return StdReturnType::INSUFFICIENT_RESOURCES;
        }
        return StdReturnType::OK;
    }

    /// @brief Ensures that there are no nul-terminators within the range
    /// specified. You use this to verify the invariant that the string does not
    /// contain any interior nul-terminators that shouldn't be there. The end of
    /// the range is exclusive. If there are any nul-terminators, the additional
    /// changes at the end of the string are discarded, the original
    /// nul-terminator is placed again and an error is returned.
    /// @warning The range specified is not itself bounds checked. It needs to
    /// be valid.
    /// @param start The start of the range to check.
    /// @param endExclusive The end of the range to check (exclusive).
    /// @return Whether there was no interior nul-terminator that shouldn't be
    /// there.
    /// @retval INVALID_STATE There is an interior nul-terminator that shouldn't
    /// be there. The new contents at the end of the string got discarded and
    /// the string is properly nul-terminated again at its original length.
    StdReturnType EnsureThereAreNoNulTerminatorsInRangeOrReNulTerminate(
        size_t const start, size_t const endExclusive)
    {
        for (size_t i = start; i < endExclusive; ++i)
        {
            if ('\0' == buf[i])
            {
                ReNulTerminate();
                return StdReturnType::INVALID_STATE;
            }
        }
        return StdReturnType::OK;
    }

    /// @brief Ensures that the printf return value passed into this function is
    /// not an encoding error. If that's the case, the remaining contents
    /// created by the printf are discarded and the string is properly
    /// nul-terminated again.
    /// @param returnValueOfPrintf The return value of printf to check for an
    /// encoding error.
    /// @return Whether there was an encoding error or not.
    /// @retval INVALID_STATE There was an encoding error. The new contents at
    /// the end of the string got discarded and the string is properly
    /// nul-terminated again at its original length.
    StdReturnType EnsureTheresNoEncodingErrorOrReNulTerminate(Integer const returnValueOfPrintf)
    {
        if (0 > returnValueOfPrintf)
        {
            ReNulTerminate();
            return StdReturnType::INVALID_STATE;
        }
        return StdReturnType::OK;
    }

    /// @brief Does a nullptr check on the C string provided. The operation
    /// fails if it is indeed nullptr.
    /// @param text The text to check for a nullptr.
    /// @return Whether the C string is a nullptr or not.
    /// @retval INVALID_ARGUMENTS The C string is a nullptr.
    static StdReturnType EnsureNotNullptr(char const* const text)
    {
        if (nullptr == text)
        {
            return StdReturnType::INVALID_ARGUMENTS;
        }
        return StdReturnType::OK;
    }

    /// @brief Saturates the length provided to never be larger than the maximum
    /// length of the string. If a length larger than the maximum length is
    /// provided, the maximum length is returned. Otherwise the length provided
    /// is returned. You can use this to write lossy operations that may cut off
    /// the remainder of the text that does not fit.
    /// @param newLen The new length to saturate at the maximum length.
    /// @return The saturated length that is guaranteed to fit into the string,
    /// which may be capped by the maximum length.
    static size_t SaturateNewLen(size_t const newLen)
    {
        if (MAX_LEN < newLen)
        {
            return MAX_LEN;
        }
        return newLen;
    }

    /// @brief The length of the string. The valid part of the string always
    /// needs to be indicated by the length. There can never be any interior
    /// nul-terminators within the string. The length always has to point to a
    /// valid in-bounds nul-terminator. The length can never be larger than the
    /// maximum length provided.
    size_t len { 0U };
    /// @brief The buffer that contains the string. The valid part of the string
    /// starts at 0 and ends at the length specified by len. At buf[len] there
    /// always has to be a nul-terminator. All bytes of buf need to always be
    /// properly initialized. The final byte of buf always needs to be a
    /// nul-terminator.
    char buf[CAPACITY] { '\0' };
};
}

} // namespaces

#endif
