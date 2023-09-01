#ifndef ARA_DIAG_ERROR_DOMAIN_H_INCLUDED
#define ARA_DIAG_ERROR_DOMAIN_H_INCLUDED

#include <ara/core/exception.h>
#include <ara/core/error_domain.h>
#include <ara/core/error_code.h>
#include <cstdint>

namespace ara {

namespace diag {

/**
 * @brief Specifies the types of internal errors that can occur upon calling Offer or ReportMonitorAction.
 *
 * @traceid{SWS_DM_00514}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00125}
 */
enum class DiagErrc : ara::core::ErrorDomain::CodeType
{
   kAlreadyOffered                      = 101, ///< The service is already offered
   kConfigurationMismatch               = 102, ///< monitor configuration does not match dext
   kDebouncingConfigurationInconsistent = 103, ///<  monitor debouncing configuration invalid, e.g. passed threshold larger than failed threshold...
   kReportIgnored                       = 104, ///<  Enable Conditions disabled, OC not started, ...
   kInvalidArgument                     = 105, ///<  e.g. kPreFailed with internal debouncing
   kNotOffered                          = 106, ///<  Offer not called before reporting
   kGenericError                        = 107, ///<  generic issue, e.g. connection to DM lost
   kNoSuchDTC                           = 108, ///< No DTC available.
   kBusy                                = 109, ///< Interface is busy with processing.
   kFailed                              = 110, ///< Failed to process.
   kMemoryError                         = 111, ///< A memory error occurred during processing.
   kWrongDtc                            = 112, ///< A wrong DTC number was requested.
   kRejected                            = 113, ///< Requested operation was rejected due to StateManagements/machines internal state.
   kResetTypeNotSupported               = 114, ///< The requested Diagnostic reset type is not supported by the Diagnostic Address instance.
   kRequestFailed                       = 115, ///< Diagnostic request could not be performed successfully.
   kCustomResetTypeNotSupported                ///< The requested Diagnostic custom reset type is not supported by the Diagnostic Address instance.
};

/**
 * @brief The DiagOfferErrc enumeration defines the error codes for the DiagErrorDomain.
 *
 * @traceid{SWS_DM_00559}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00125}
 */
enum class DiagOfferErrc : ara::core::ErrorDomain::CodeType
{
   kAlreadyOffered                      = 101, ///< The service is already offered
   kConfigurationMismatch               = 102, ///<  monitor configuration does not match dext
   kDebouncingConfigurationInconsistent = 103, ///<  monitor debouncing configuration invalid, e.g. passed threshold larger than failed threshold...
};


/**
 * @brief The DiagReportingErrc enumeration defines the error codes for the DiagReportingErrorDomain.
 * @traceid{SWS_DM_00560}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00125}
 */
enum class DiagReportingErrc : ara::core::ErrorDomain::CodeType
{
   kAlreadyOffered                      = 101, ///< The service is already offered
   kConfigurationMismatch               = 102, ///< monitor configuration does not match dext
   kDebouncingConfigurationInconsistent = 103, ///<  monitor debouncing configuration invalid, e.g. passed threshold larger than failed threshold...
   kReportIgnored                       = 104, ///<  Enable Conditions disabled, OC not started, ...
   kInvalidArgument                     = 105, ///<  e.g. kPreFailed with internal debouncing
   kNotOffered                          = 106, ///<  Offer not called before reporting
   kGenericError                        = 107  ///<  generic issue, e.g. connection to DM lost
};

/**
 * @brief Exception type thrown by Diag classes.
 *
 * @traceid{SWS_DM_00515}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00132}
 */
class DiagException
   : public ara::core::Exception
{
public:

   /**
    * @brief Construct a new DiagException from an ErrorCode.
    * @param err  the ErrorCode
    *
    * @traceid{SWS_DM_00516}@tracestatus{draft}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_AP_00132}
    */
   explicit DiagException( ara::core::ErrorCode err ) noexcept
      : Exception( err )
   {
   }
};

/**
 * @brief Exception type thrown by Diag classes.
 *
 * @traceid{SWS_DM_00985}@tracestatus{draft}
 */
class DiagOfferException
   : public ara::core::Exception
{
public:

   /**
    * @brief Construct a new DiagException from an ErrorCode.
    * @param err  the ErrorCode
    *
    * @traceid{SWS_DM_00986}@tracestatus{draft}
    */
   explicit DiagOfferException( ara::core::ErrorCode err ) noexcept
      : Exception( err )
   {
   }
};

/**
 * @brief Exception type thrown by Diag classes.
 *
 * @traceid{SWS_DM_00987}@tracestatus{draft}
 */
class DiagReportingException
   : public ara::core::Exception
{
public:

   /**
    * @brief Construct a new DiagException from an ErrorCode.
    * @param err  the ErrorCode
    *
    * @traceid{SWS_DM_00988}@tracestatus{draft}
    */
   explicit DiagReportingException( ara::core::ErrorCode err ) noexcept
      : Exception( err )
   {
   }
};

/**
 * @brief Error domain for diagnostic errors.
 *
 * @domainid{0x8000'0000'0000'0401}
 * @traceid{SWS_DM_00517}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00132}
 */
class DiagErrorDomain final
   : public ara::core::ErrorDomain
{
   constexpr static ErrorDomain::IdType kId = 0x8000000000000401;

public:
   /// @brief Alias for the error code value enumeration
   ///
   /// @traceid{SWS_DM_00518}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   using Errc = DiagErrc;

   /// @brief Alias for the exception base class
   ///
   /// @traceid{SWS_DM_00519}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   using Exception = DiagException;

   /// @brief Default constructor
   ///
   /// @traceid{SWS_DM_00520}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   constexpr DiagErrorDomain() noexcept
      : ErrorDomain( kId )
   {
   }

   /// @brief Return the "shortname" ApApplicationErrorDomain.SN of this error domain.
   /// @returns "Diag"
   ///
   /// @traceid{SWS_DM_00521}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   const char* Name() const noexcept override
   {
      return "DiagErrorDomain";
   }

   /// @brief Translate an error code value into a text message.
   /// @param errorCode  the error code value
   /// @returns the text message, never nullptr
   ///
   /// @traceid{SWS_DM_00522}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   const char* Message( ara::core::ErrorDomain::CodeType errorCode ) const noexcept override
   {
      Errc const code = static_cast<Errc>( errorCode );

      switch( code )
      {
         case Errc::kAlreadyOffered:
            return "kAlreadyOffered";

         case Errc::kConfigurationMismatch:
            return "kConfigurationMismatch";

         case Errc::kDebouncingConfigurationInconsistent:
            return "kDebouncingConfigurationInconsistent";

         case Errc::kReportIgnored:
            return "kReportIgnored";

         case Errc::kInvalidArgument:
            return "kInvalidArgument";

         case Errc::kNotOffered:
            return "kNotOffered";

         case Errc::kGenericError:
            return "kGenericError";

         case Errc::kNoSuchDTC:
            return "kNoSuchDTC";

         case Errc::kBusy:
            return "kBusy";

         case Errc::kFailed:
            return "kFailed";

         case Errc::kMemoryError:
            return "kMemoryError";

         case Errc::kWrongDtc:
            return "kWrongDtc";

         case Errc::kRejected:
            return "kRejected";

         case Errc::kResetTypeNotSupported:
            return "kResetTypeNotSupported";

         case Errc::kRequestFailed:
            return "kRequestFailed";

         case Errc::kCustomResetTypeNotSupported:
            return "kCustomResetTypeNotSupported";

         default:
            return "Unknown error";
      }
   }

   /// @brief Throw the exception type corresponding to the given ErrorCode.
   /// @param errorCode  the ErrorCode instance
   ///
   /// @traceid{SWS_DM_00523}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   void ThrowAsException( const ara::core::ErrorCode& errorCode ) const noexcept( false ) override
   {
      ara::core::ThrowOrTerminate<Exception>( errorCode );
   }

   // Justification: UT does not cover this line (i.e. closing bracket) because of the exception thrown.
};

/**
 * @brief Error domain for diagnostic offer errors.
 *
 * @domainid{0x8000'0000'0000'0403}
 * @traceid{SWS_DM_00989}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00132}
 */
class DiagOfferErrorDomain final
   : public ara::core::ErrorDomain
{
   constexpr static ErrorDomain::IdType kId = 0x8000000000000403;

public:
   /// @brief Alias for the error code value enumeration
   ///
   /// @traceid{SWS_DM_00990}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   using Errc = DiagOfferErrc;

   /// @brief Alias for the exception base class
   ///
   /// @traceid{SWS_DM_00991}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   using Exception = DiagException;

   /// @brief Default constructor
   ///
   /// @traceid{SWS_DM_00992}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   constexpr DiagOfferErrorDomain() noexcept
      : ErrorDomain( kId )
   {
   }

   /// @brief Return the "shortname" ApApplicationErrorDomain.SN of this error domain.
   /// @returns "DiagOffer"
   ///
   /// @traceid{SWS_DM_00993}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   const char* Name() const noexcept override
   {
      return "DiagOfferErrorDomain";
   }

   /// @brief Translate an error code value into a text message.
   /// @param errorCode  the error code value
   /// @returns the text message, never nullptr
   ///
   /// @traceid{SWS_DM_00994}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   const char* Message( ara::core::ErrorDomain::CodeType errorCode ) const noexcept override
   {
      Errc const code = static_cast<Errc>( errorCode );

      switch( code )
      {
         case Errc::kAlreadyOffered:
            return "kAlreadyOffered";

         case Errc::kConfigurationMismatch:
            return "kConfigurationMismatch";

         case Errc::kDebouncingConfigurationInconsistent:
            return "kDebouncingConfigurationInconsistent";

         default:
            return "Unknown error";
      }
   }

   /// @brief Throw the exception type corresponding to the given ErrorCode.
   /// @param errorCode  the ErrorCode instance
   ///
   /// @traceid{SWS_DM_00995}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   void ThrowAsException( const ara::core::ErrorCode& errorCode ) const noexcept( false ) override
   {
      ara::core::ThrowOrTerminate<Exception>( errorCode );
   }

   // Justification: UT does not cover this line (i.e. closing bracket) because of the exception thrown.
};

/**
 * @brief Error domain for diagnostic reporting errors.
 *
 * @domainid{0x8000'0000'0000'0402}
 * @traceid{SWS_DM_00996}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00132}
 */
class DiagReportingErrorDomain final
   : public ara::core::ErrorDomain
{
   constexpr static ErrorDomain::IdType kId = 0x8000000000000402;

public:
   /// @brief Alias for the error code value enumeration
   ///
   /// @traceid{SWS_DM_00997}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   using Errc = DiagReportingErrc;

   /// @brief Alias for the exception base class
   ///
   /// @traceid{SWS_DM_00998}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   using Exception = DiagReportingException;

   /// @brief Default constructor
   ///
   /// @traceid{SWS_DM_00999}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   constexpr DiagReportingErrorDomain() noexcept
      : ErrorDomain( kId )
   {
   }

   /// @brief Return the "shortname" ApApplicationErrorDomain.SN of this error domain.
   /// @returns "DiagReporting"
   ///
   /// @traceid{SWS_DM_01000}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   const char* Name() const noexcept override
   {
      return "DiagReportingErrorDomain";
   }

   /// @brief Translate an error code value into a text message.
   /// @param errorCode  the error code value
   /// @returns the text message, never nullptr
   ///
   /// @traceid{SWS_DM_01001}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   const char* Message( ara::core::ErrorDomain::CodeType errorCode ) const noexcept override
   {
      Errc const code = static_cast<Errc>( errorCode );

      switch( code )
      {
         case Errc::kAlreadyOffered:
            return "kAlreadyOffered";

         case Errc::kConfigurationMismatch:
            return "kConfigurationMismatch";

         case Errc::kDebouncingConfigurationInconsistent:
            return "kDebouncingConfigurationInconsistent";

         case Errc::kGenericError:
            return "kGenericError";

         case Errc::kInvalidArgument:
            return "kInvalidArgument";

         case Errc::kNotOffered:
            return "kNotOffered";

         case Errc::kReportIgnored:
            return "kReportIgnored";

         default:
            return "Unknown error";
      }
   }

   /// @brief Throw the exception type corresponding to the given ErrorCode.
   /// @param errorCode  the ErrorCode instance
   ///
   /// @traceid{SWS_DM_01002}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   void ThrowAsException( const ara::core::ErrorCode& errorCode ) const noexcept( false ) override
   {
      ara::core::ThrowOrTerminate<Exception>( errorCode );
   }

   // Justification: UT does not cover this line (i.e. closing bracket) because of the exception thrown.
};

namespace internal {

constexpr DiagErrorDomain          g_DiagErrorDomain;
constexpr DiagOfferErrorDomain     g_DiagOfferErrorDomain;
constexpr DiagReportingErrorDomain g_DiagReportingErrorDomain;

}

/**
 * @brief Obtain the reference to the single global DiagErrorDomain instance.
 * @returns reference to the DiagErrorDomain instance
 *
 * @traceid{SWS_DM_00524}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00132}
 */
constexpr const ara::core::ErrorDomain& GetDiagDomain() noexcept
{
   return internal::g_DiagErrorDomain;
}

/**
 * @brief Obtain the reference to the single global DiagErrorDomain instance.
 * @returns reference to the DiagOfferErrorDomain instance
 *
 * @traceid{SWS_DM_01003}@tracestatus{draft}
 */
constexpr const ara::core::ErrorDomain& GetDiagOfferDomain() noexcept
{
   return internal::g_DiagOfferErrorDomain;
}

/**
 * @brief Obtain the reference to the single global DiagReportingErrorDomain instance.
 * @returns reference to the DiagOfferErrorDomain instance
 *
 * @traceid{SWS_DM_01004}@tracestatus{draft}
 */
constexpr const ara::core::ErrorDomain& GetDiagReportingDomain() noexcept
{
   return internal::g_DiagReportingErrorDomain;
}

/**
 * @brief Create a new ErrorCode for DiagErrorDomain with the given support data type.
 *
 * @param code  an enumeration value from future_errc
 * @param data  a vendor-defined supplementary value
 * @returns the new ErrorCode instance
 *
 * @traceid{SWS_DM_00525}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00132}
 */
constexpr ara::core::ErrorCode MakeErrorCode( DiagErrc code, ara::core::ErrorDomain::SupportDataType data ) noexcept
{
   return core::ErrorCode( static_cast<core::ErrorDomain::CodeType>( code ), GetDiagDomain(), data );
}

/**
 * @brief Create a new ErrorCode for DiagOfferErrorDomain with the given support data type.
 *
 * @param code  an enumeration value from future_errc
 * @param data  a vendor-defined supplementary value
 * @returns the new ErrorCode instance
 *
 * @traceid{SWS_DM_01005}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00132}
 */
constexpr ara::core::ErrorCode MakeErrorCode( DiagOfferErrc code, ara::core::ErrorDomain::SupportDataType data ) noexcept
{
   return core::ErrorCode( static_cast<core::ErrorDomain::CodeType>( code ), GetDiagOfferDomain(), data );
}

/**
 * @brief Create a new ErrorCode for DiagReportingErrorDomain with the given support data type.
 *
 * @param code  an enumeration value from future_errc
 * @param data  a vendor-defined supplementary value
 * @returns the new ErrorCode instance
 *
 * @traceid{SWS_DM_01006}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00132}
 */
constexpr ara::core::ErrorCode MakeErrorCode( DiagReportingErrc code, ara::core::ErrorDomain::SupportDataType data ) noexcept
{
   return core::ErrorCode( static_cast<core::ErrorDomain::CodeType>( code ), GetDiagReportingDomain(), data );
}

}     //namespace diag

} //namespace ara
#endif //ARA_DIAG_ERROR_DOMAIN_H_INCLUDED
