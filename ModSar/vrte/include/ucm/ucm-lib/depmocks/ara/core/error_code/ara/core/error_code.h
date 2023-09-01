// --------------------------------------------------------------------------
// |              _    _ _______     .----.      _____         _____        |
// |         /\  | |  | |__   __|  .  ____ .    / ____|  /\   |  __ \       |
// |        /  \ | |  | |  | |    .  / __ \ .  | (___   /  \  | |__) |      |
// |       / /\ \| |  | |  | |   .  / / / / v   \___ \ / /\ \ |  _  /       |
// |      / /__\ \ |__| |  | |   . / /_/ /  .   ____) / /__\ \| | \ \       |
// |     /________\____/   |_|   ^ \____/  .   |_____/________\_|  \_\      |
// |                              . _ _  .                                  |
// --------------------------------------------------------------------------
//
// All Rights Reserved.
// Any use of this source code is subject to a license agreement with the
// AUTOSAR development cooperation.
// More information is available at www.autosar.org.
//
// Disclaimer
//
// This work (specification and/or software implementation) and the material
// contained in it, as released by AUTOSAR, is for the purpose of information
// only. AUTOSAR and the companies that have contributed to it shall not be
// liable for any use of the work.
//
// The material contained in this work is protected by copyright and other
// types of intellectual property rights. The commercial exploitation of the
// material contained in this work requires a license to such intellectual
// property rights.
//
// This work may be utilized or reproduced without any modification, in any
// form or by any means, for informational purposes only. For any other
// purpose, no part of the work may be utilized or reproduced, in any form
// or by any means, without permission in writing from the publisher.
//
// The work has been developed for automotive applications only. It has
// neither been developed, nor tested for non-automotive applications.
//
// The word AUTOSAR and the AUTOSAR logo are registered trademarks.
// --------------------------------------------------------------------------

#ifndef APD_ARA_CORE_ERROR_CODE_H_
#define APD_ARA_CORE_ERROR_CODE_H_

#include "ara/core/error_domain.h"
#include "ara/core/string_view.h"

#include <ostream>
#include <cstdint>

namespace ara
{
namespace core
{

class ErrorCode
{
    friend std::ostream& operator<<(std::ostream& out, ErrorCode const& e) { return out; }

    using CodeType = ErrorDomain::CodeType;
    using SupportDataType = ErrorDomain::SupportDataType;

public:
    template <typename EnumT, typename = typename std::enable_if<std::is_enum<EnumT>::value>::type>
    constexpr ErrorCode(EnumT e, SupportDataType data = 0) noexcept
        : ErrorCode(MakeErrorCode(e, data)) {}

    constexpr ErrorCode(CodeType value, ErrorDomain const& domain, SupportDataType data = 0) noexcept
        : mValue(value),
          mSupportData(data),
          mDomain(&domain) {}

    constexpr CodeType Value() const noexcept { return mValue; }
    constexpr SupportDataType SupportData() const noexcept { return mSupportData; }
    constexpr ErrorDomain const& Domain() const noexcept { return *mDomain; }
    StringView Message() const noexcept { return Domain().Message(Value()); }

    [[noreturn]] void ThrowAsException() const noexcept(false)
    {
        Domain().ThrowAsException(*this);

        std::terminate();
    }

private:
    CodeType mValue;
    SupportDataType mSupportData;
    ErrorDomain const* mDomain; // non-owning pointer to the associated ErrorDomain
};

constexpr inline bool operator==(ErrorCode const& lhs, ErrorCode const& rhs)
{
    return lhs.Domain() == rhs.Domain() && lhs.Value() == rhs.Value();
}

constexpr inline bool operator!=(ErrorCode const& lhs, ErrorCode const& rhs)
{
    return lhs.Domain() != rhs.Domain() || lhs.Value() != rhs.Value();
}

template <typename ExceptionType>
void ThrowOrTerminate(ErrorCode errorCode)
{
#ifndef ARA_NO_EXCEPTIONS
    throw ExceptionType(std::move(errorCode));
#else
    (void)errorCode;
    std::terminate();
#endif
}

} // namespace core
} // namespace ara

#endif // APD_ARA_CORE_ERROR_CODE_H_
