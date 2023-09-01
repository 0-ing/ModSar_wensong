#ifndef ARA_DIAG_UDS_NRC_ERROR_DOMAIN_H_INCLUDED
#define ARA_DIAG_UDS_NRC_ERROR_DOMAIN_H_INCLUDED

#include <ara/core/exception.h>
#include <ara/core/error_domain.h>
#include <ara/core/error_code.h>
#include <cstdint>

namespace ara {

namespace diag {

/**
 * @brief Specifies the types of internal errors that can occur upon calling Offer or ReportMonitorAction.
 *
 * @traceid{SWS_DM_00526}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00125}
 */
enum class DiagUdsNrcErrc : int32_t
{
   kGeneralReject                             = 0x10, ///< According to ISO.
   kServiceNotSupported                       = 0x11, ///<According to ISO.
   kSubfunctionNotSupported                   = 0x12, ///< According to ISO.
   kIncorrectMessageLengthOrInvalidFormat     = 0x13, ///< According to ISO.
   kResponseTooLong                           = 0x14, ///< According to ISO.
   kBusyRepeatRequest                         = 0x21, ///< According to ISO.
   kConditionsNotCorrect                      = 0x22, ///< According to ISO.
   kRequestSequenceError                      = 0x24, ///< According to ISO.
   kNoResponseFromSubnetComponent             = 0x25, ///< According to ISO.
   kFailurePreventsExecutionOfRequestedAction = 0x26, ///< According to ISO.
   kRequestOutOfRange                         = 0x31, ///< According to ISO.
   kSecurityAccessDenied                      = 0x33, ///< According to ISO.
   kInvalidKey                                = 0x35, ///< According to ISO.
   kExceedNumberOfAttempts                    = 0x36, ///< According to ISO.
   kRequiredTimeDelayNotExpired               = 0x37, ///< According to ISO.
   kUploadDownloadNotAccepted                 = 0x70, ///< According to ISO.
   kTransferDataSuspended                     = 0x71, ///< According to ISO.
   kGeneralProgrammingFailure                 = 0x72, ///< According to ISO.
   kWrongBlockSequenceCounter                 = 0x73, ///< According to ISO.
   kSubFunctionNotSupportedInActiveSession    = 0x7E, ///< According to ISO.
   kServiceNotSupportedInActiveSession        = 0x7F, ///< According to ISO.
   kRpmTooHigh                                = 0x81, ///< According to ISO.
   kRpmTooLow                                 = 0x82, ///< According to ISO.
   kEngineIsRunning                           = 0x83, ///< According to ISO.
   kEngineIsNotRunning                        = 0x84, ///< According to ISO.
   kEngineRunTimeTooLow                       = 0x85, ///< According to ISO.
   kTemperatureTooHigh                        = 0x86, ///< According to ISO.
   kTemperatureTooLow                         = 0x87, ///< According to ISO.
   kVehicleSpeedTooHigh                       = 0x88, ///< According to ISO.
   kVehicleSpeedTooLow                        = 0x89, ///< According to ISO.
   kThrottlePedalTooHigh                      = 0x8A, ///< According to ISO.
   kThrottlePedalTooLow                       = 0x8B, ///< According to ISO.
   kTransmissionRangeNotInNeutral             = 0x8C, ///< According to ISO.
   kTransmissionRangeNotInGear                = 0x8D, ///< According to ISO.
   kBrakeSwitchNotClosed                      = 0x8F, ///< According to ISO.
   kShifterLeverNotInPark                     = 0x90, ///< According to ISO.
   kTorqueConverterClutchLocked               = 0x91, ///< According to ISO.
   kVoltageTooHigh                            = 0x92, ///< According to ISO.
   kVoltageTooLow                             = 0x93, ///< According to ISO.
   kResourceTemporarilyNotAvailable           = 0x94, ///< According to ISO 14229-1 Table A.1.14229-1 Table A.1.
   kNoProcessingNoResponse                    = 0xFF, ///< Deviating from ISO - no further service processing and no response (silently ignore request message).
};

/**
 * @brief Exception type thrown by Diag classes.
 *
 * @traceid{SWS_DM_00527}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00132}
 */
class DiagUdsNrcException
   : public ara::core::Exception
{
public:

   /**
    * @brief Construct a new DiagException from an ErrorCode.
    * @param err  the ErrorCode
    *
    * @traceid{SWS_DM_00528}@tracestatus{draft}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_AP_00132}
    */
   explicit DiagUdsNrcException( ara::core::ErrorCode err ) noexcept
      : Exception( err )
   {
   };
};

/**
 * @brief Error domain for errors originating from several diagnostic classes.
 *
 * @domainid{0x8000'0000'0000'0411}
 * @traceid{SWS_DM_00529}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00132}
 */
class DiagUdsNrcErrorDomain final
   : public ara::core::ErrorDomain
{
   constexpr static ErrorDomain::IdType kId = 0x8000000000000411;

public:
   /// @brief Alias for the error code value enumeration
   ///
   /// @traceid{SWS_DM_00530}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   using Errc = DiagUdsNrcErrc;

   /// @brief Alias for the exception base class
   ///
   /// @traceid{SWS_DM_00531}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   using Exception = DiagUdsNrcException;

   /// @brief Default constructor
   ///
   /// @traceid{SWS_DM_00532}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   constexpr DiagUdsNrcErrorDomain() noexcept
      : ErrorDomain( kId )
   {
   };

   /// @brief Return the "shortname" ApApplicationErrorDomain.SN of this error domain.
   /// @returns "DiagUdsNrc"
   ///
   /// @traceid{SWS_DM_00533}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   const char* Name() const noexcept override
   {
      return "DiagUdsNrcErrorDomain";
   }

   /// @brief Translate an error code value into a text message.
   /// @param errorCode  the error code value
   /// @returns the text message, never nullptr
   ///
   /// @traceid{SWS_DM_00534}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132
   const char* Message( ara::core::ErrorDomain::CodeType errorCode ) const noexcept override
   {
      Errc const code = static_cast<Errc>( errorCode );

      switch( code )
      {
         case Errc::kBrakeSwitchNotClosed:
            return "kBrakeSwitchNotClosed";

         case Errc::kBusyRepeatRequest:
            return "kBusyRepeatRequest";

         case Errc::kConditionsNotCorrect:
            return "kConditionsNotCorrect";

         case Errc::kEngineIsNotRunning:
            return "kEngineIsNotRunning";

         case Errc::kEngineIsRunning:
            return "kEngineIsRunning";

         case Errc::kEngineRunTimeTooLow:
            return "kEngineRunTimeTooLow";

         case Errc::kExceedNumberOfAttempts:
            return "kExceedNumberOfAttempts";

         case Errc::kFailurePreventsExecutionOfRequestedAction:
            return "kFailurePreventsExecutionOfRequestedAction";

         case Errc::kGeneralProgrammingFailure:
            return "kGeneralProgrammingFailure";

         case Errc::kGeneralReject:
            return "kGeneralReject";

         case Errc::kIncorrectMessageLengthOrInvalidFormat:
            return "kIncorrectMessageLengthOrInvalidFormat";

         case Errc::kInvalidKey:
            return "kInvalidKey";

         case Errc::kNoProcessingNoResponse:
            return "kNoProcessingNoResponse";

         case Errc::kNoResponseFromSubnetComponent:
            return "kNoResponseFromSubnetComponent";

         case Errc::kRequestOutOfRange:
            return "kRequestOutOfRange";

         case Errc::kRequestSequenceError:
            return "kRequestSequenceError";

         case Errc::kRequiredTimeDelayNotExpired:
            return "kRequiredTimeDelayNotExpired";

         case Errc::kResponseTooLong:
            return "kResponseTooLong";

         case Errc::kRpmTooHigh:
            return "kRpmTooHigh";

         case Errc::kRpmTooLow:
            return "kRpmTooLow";

         case Errc::kSecurityAccessDenied:
            return "kSecurityAccessDenied";

         case Errc::kServiceNotSupported:
            return "kServiceNotSupported";

         case Errc::kServiceNotSupportedInActiveSession:
            return "kServiceNotSupportedInActiveSession";

         case Errc::kShifterLeverNotInPark:
            return "kShifterLeverNotInPark";

         case Errc::kSubfunctionNotSupported:
            return "kSubfunctionNotSupported";

         case Errc::kSubFunctionNotSupportedInActiveSession:
            return "kSubFunctionNotSupportedInActiveSession";

         case Errc::kTemperatureTooHigh:
            return "kTemperatureTooHigh";

         case Errc::kTemperatureTooLow:
            return "kTemperatureTooLow";

         case Errc::kThrottlePedalTooHigh:
            return "kThrottlePedalTooHigh";

         case Errc::kThrottlePedalTooLow:
            return "kThrottlePedalTooLow";

         case Errc::kTorqueConverterClutchLocked:
            return "kTorqueConverterClutchLocked";

         case Errc::kTransferDataSuspended:
            return "kTransferDataSuspended";

         case Errc::kTransmissionRangeNotInGear:
            return "kTransmissionRangeNotInGear";

         case Errc::kTransmissionRangeNotInNeutral:
            return "kTransmissionRangeNotInNeutral";

         case Errc::kUploadDownloadNotAccepted:
            return "kUploadDownloadNotAccepted";

         case Errc::kVehicleSpeedTooHigh:
            return "kVehicleSpeedTooHigh";

         case Errc::kVehicleSpeedTooLow:
            return "kVehicleSpeedTooLow";

         case Errc::kVoltageTooHigh:
            return "kVoltageTooHigh";

         case Errc::kVoltageTooLow:
            return "kVoltageTooLow";

         case Errc::kWrongBlockSequenceCounter:
            return "kWrongBlockSequenceCounter";

         case Errc::kResourceTemporarilyNotAvailable:
            return "kResourceTemporarilyNotAvailable";

         default:
            return "Unknown error";
      }
   }

   /// @brief Throw the exception type corresponding to the given ErrorCode.
   /// @param errorCode  the ErrorCode instance
   ///
   /// @traceid{SWS_DM_00535}@tracestatus{draft}
   /// @uptrace{RS_AP_00119}
   /// @uptrace{RS_AP_00132}
   void ThrowAsException( const ara::core::ErrorCode& errorCode ) const noexcept( false ) override
   {
      ara::core::ThrowOrTerminate<Exception>( errorCode );
   } // Justification: UT does not cover this line (the closing bracket) because of exception thrown hence structure coverage is 98%
};
namespace internal {

constexpr DiagUdsNrcErrorDomain g_DiagUdsNrcErrorDomain;

}

/**
 * @brief Obtain the reference to the single global DiagUdsNrcErrorDomain instance.
 * @returns reference to the DiagUdsNrcErrorDomain instance
 *
 * @traceid{SWS_DM_00536}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00132}
 */
constexpr const ara::core::ErrorDomain& GetDiagUdsNrcDomain() noexcept
{
   return internal::g_DiagUdsNrcErrorDomain;
}

/**
 * @brief Create a new ErrorCode for DiagUdsNrcErrorDomain with the given support data type and message.
 *
 * @param code  an enumeration value from diag_errc
 * @param data  a vendor-defined supplementary value
 * @returns the new ErrorCode instance
 *
 * @traceid{SWS_DM_00537}@tracestatus{draft}
 * @uptrace{RS_AP_00119}
 * @uptrace{RS_AP_00132}
 */
constexpr ara::core::ErrorCode MakeErrorCode( DiagUdsNrcErrc code, ara::core::ErrorDomain::SupportDataType data ) noexcept
{
   return core::ErrorCode( static_cast<core::ErrorDomain::CodeType>( code ), GetDiagUdsNrcDomain(), data );
}

} //namespace diag

} //namespace ara
#endif //ARA_DIAG_UDS_NRC_ERROR_DOMAIN_H_INCLUDED
