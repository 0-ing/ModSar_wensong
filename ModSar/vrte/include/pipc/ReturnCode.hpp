#ifndef RETURN_CODE_HPP
#define RETURN_CODE_HPP

#include <cstdint>
namespace pipc
{
enum class ReturnCode : uint8_t
{
    // General errors
    kOk = 0,
    kGeneralError,
    kBusy,
    kPermissionDenied,
    kExists,
    kCallbackAlreadyRegistered,
    kMaxSamplesReached,
    kSampleIdOutOfRange,
    kSequenceCounterMismatch,
    kLoanAlreadyReclaimed,
    kLoanStillHasDebitors,
    // Network layer errors
    kNetworkError,
    // Transport layer errors
    kTransportError,
    kPortInUse,
    kPortOutOfBounds,
    // Session layer errors
    kSessionError,
    kNotConnected,
    // App layer errors
    kAppError,
    kInvalidSubscriptionMsg,
    kExecutorAlreadyRegistered,
    kNoExecutorRegistered,
    /* Sd error codes */
    kSdInvalidInput,
    kSdIamGrantDenied,
    kSdRegistryFull,
    kSdAlreadyRegistered,
    kSdFailToAddPermission,
};

// TODO: move to cpp, also change to array access
__attribute__((unused)) static const char* ToString(ReturnCode code)
{
    switch (code)
    {
    case ReturnCode::kOk:
        return "Ok";
    case ReturnCode::kGeneralError:
        return "GeneralError";
    case ReturnCode::kBusy:
        return "Busy";
    case ReturnCode::kPermissionDenied:
        return "PermissionDenied";
    case ReturnCode::kExists:
        return "Exists";
    case ReturnCode::kCallbackAlreadyRegistered:
        return "CallbackAlreadyRegistered";
    case ReturnCode::kMaxSamplesReached:
        return "MaxSamplesReached";
    case ReturnCode::kSampleIdOutOfRange:
        return "SampleIdOutOfRange";
    case ReturnCode::kSequenceCounterMismatch:
        return "SequenceCounterMismatch";
    case ReturnCode::kLoanAlreadyReclaimed:
        return "LoanAlreadyReclaimed";
    case ReturnCode::kLoanStillHasDebitors:
        return "LoanStillHasDebitors";
    case ReturnCode::kNetworkError:
        return "NetworkError";
    case ReturnCode::kTransportError:
        return "TransportError";
    case ReturnCode::kPortInUse:
        return "PortInUse";
    case ReturnCode::kPortOutOfBounds:
        return "PortOutOfBounds";
    case ReturnCode::kSessionError:
        return "SessionError";
    case ReturnCode::kNotConnected:
        return "NotConnected";
    case ReturnCode::kAppError:
        return "AppError";
    case ReturnCode::kInvalidSubscriptionMsg:
        return "InvalidSubscriptionMsg";
    case ReturnCode::kExecutorAlreadyRegistered:
        return "ExecutorAlreadyRegistered";
    case ReturnCode::kNoExecutorRegistered:
        return "NoExecutorRegistered";
    case ReturnCode::kSdInvalidInput:
        return "SdInvalidInput";
    case ReturnCode::kSdIamGrantDenied:
        return "SdIamGrantDenied";
    case ReturnCode::kSdRegistryFull:
        return "SdRegistryFull";
    case ReturnCode::kSdAlreadyRegistered:
        return "SdAlreadyRegistered";
    case ReturnCode::kSdFailToAddPermission:
        return "SdFailToAddPermission";
    default:
        return "UnknownCode";
    }
}

} // namespace pipc

#endif // RETURN_CODE_HPP
