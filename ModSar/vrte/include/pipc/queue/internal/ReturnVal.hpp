#ifndef QUEUE_RETURNVAL_HPP
#define QUEUE_RETURNVAL_HPP

namespace pipc
{
/** 
 * @brief Legacy ReturnVal definition.
 *
 * @todo
 * Replace with ReturnCode.
 */
enum class ReturnVal
{
    kOk = 0,
    kGeneralError,
    kQueueFull,
    kQueueEmpty,
    kQueueStateCorrupt,
    kQueuePayloadCorrupt,
    kOutOfMemory,
    kExists
};

__attribute__((unused)) static const char* ToString(ReturnVal code)
{
    switch (code)
    {
    case ReturnVal::kOk:
        return "Ok";
    case ReturnVal::kGeneralError:
        return "GeneralError";
    case ReturnVal::kQueueFull:
        return "QueueFull";
    case ReturnVal::kQueueEmpty:
        return "QueueEmpty";
    case ReturnVal::kQueueStateCorrupt:
        return "QueueStateCorrupt";
    case ReturnVal::kQueuePayloadCorrupt:
        return "QueuePayloadCorrupt";
    case ReturnVal::kOutOfMemory:
        return "OutOfMemory";
    case ReturnVal::kExists:
        return "Exists";
    default:
        return "UnknownCode";
    }
}

}

#endif // QUEUE_RETURNVAL_HPP
