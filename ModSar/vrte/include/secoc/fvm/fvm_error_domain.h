/// @file fvm_error_domain.h
/// @copyright 2021 Robert Bosch GmbH. All rights reserved.


#ifndef FVM_ERROR_DOMAIN_H_INCLUDED
#define FVM_ERROR_DOMAIN_H_INCLUDED

#include "ara/core/error_domain.h"
#include "ara/core/error_code.h"

namespace ara
{
namespace com
{
namespace secoc
{

/// @brief SecOC error Management
enum class SecOcFvmErrc : ara::core::ErrorDomain::CodeType
{
    /*
     * Recoverable Error meaning the Freshness Value not available.
     */
    kFVNotAvailable               = 1,

    /*
     * Unrecoverable Error meaning the Freshness Value Manager could not be used.
     */
    kFVInitializeFailed                = 2,
};

/* FVM is just a dummy implementation, below logic not needed */
/*class SecOcFvmErrorDomain final : public ara::core::ErrorDomain
{
public:

    constexpr static ErrorDomain::IdType kId = 0x8000000000001271;

    using Errc = SecOcFvmErrc;
    
    SecOcFvmErrorDomain() noexcept;


    char const* Name() const noexcept override;


    char const* Message(ara::core::ErrorDomain::CodeType errorCode) const noexcept override;

    [[noreturn]] virtual void ThrowAsException(ara::core::ErrorCode const& errorCode) const noexcept(false); 
};


ara::core::ErrorDomain const& GetSecOcFvmErrorDomain() noexcept;

ara::core::ErrorCode MakeErrorCode(SecOcFvmErrc code, ara::core::ErrorDomain::SupportDataType data = 0) noexcept; */

} // namespace secoc
} // namespace com
} // namespace ara

#endif // FVM_ERROR_DOMAIN_H_INCLUDED
