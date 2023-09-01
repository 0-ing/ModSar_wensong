//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

#ifndef RB_TED_API_HPP_INCLUDED
#define RB_TED_API_HPP_INCLUDED

// TODO: Check if there is a need for version information of this header file/class declaration necessary.
//       So we can change the class later on without update all plugin libraries.
// TODO: Avoid pre-processor macros to ensure that they match to rb_ted. Maybe by using enums.

#include <cstddef>
#include <cstdint>
#include <list>
#include <pthread.h>
#include <string>
#include <vector>

// Common return codes of class methods

#define RB_TED_RET_CODE_OK                   0 // Ok/no error
#define RB_TED_RET_CODE_CMD_UNKNOWN          1 // Error: Command is unknown/not available
#define RB_TED_RET_CODE_CMD_ARGS_MISMATCH    2 // Error: Mismatch of command arguments
#define RB_TED_RET_CODE_CMD_ARGS_INVALID     3 // Error: Command arguments are invalid
#define RB_TED_RET_CODE_CMD_PRECOND_MISS    15 // Error: Precondition for successful command execution is missing
#define RB_TED_RET_CODE_CMD_FAILED          16 // Error: Command execution failed (that means: Everything
                                               // is ok and it is expected that the command executes now
                                               // sucessfully but still fails -> normally that means we have
                                               // found and issue)
#define RB_TED_RET_CODE_THREAD_LIFE_FAILED  19 // Error: Thread creation or termination failed
#define RB_TED_RET_CODE_THREAD_NOT_EXIST    20 // Error: Thread is not existing
#define RB_TED_RET_CODE_LIMIT_REACHED       21 // Error: Limit of a resource reached



namespace bosch
{
namespace vrte
{
namespace saf
{
namespace ted
{

// Type of command information
typedef struct
{
    // Command ID (terminated by \0)
    char m_cmdId_ac[10];
    // Description of command (terminated by \0)
    char m_description_ac[60];
} CCmdInfo;
// Thread maintenance information
typedef struct
{
    // Thread ID
    pthread_t m_threadId;
    void *(* m_main_pfn)(uint8_t &, void *);
    // Pointer to thread specific data buffer
    void *m_data_p;
    // State of thread (1=running, 0xFE=shutdown requested, 0xFF=shutdown)
    uint8_t m_state_u8;
} CThread;

class CPlugin
{
public:
    // *************************************************************************************************
    // \brief Constructor.
    // *************************************************************************************************
    CPlugin();

    // *************************************************************************************************
    // \brief Destructor.
    // *************************************************************************************************
    virtual ~CPlugin();

    // *************************************************************************************************
    // \brief Get the version information of the plugin. This methode should be overwritten by the
    //        the deriving class.
    // \return Pointer to C-string (terminated by \0) which holds the version information.
    // *************************************************************************************************
    virtual const char * getVersionInfo(void);

    // *************************************************************************************************
    // \brief Set the verbose level of plugin messages.
    // \param[in] f_verboseLevel_pu8 Pointer to the globally set verbose level (in the range 0 to 255).
    // *************************************************************************************************
    void setVerboseLevel(const uint8_t *f_verboseLevel_pu8);

    // *************************************************************************************************
    // \brief Get the list of available commands supported by the plugin. It is a abstract methode
    //        which shall be implemented by the deriving class.
    // \param[out] f_cmdInfo_pa Pointer to list of supported commands.
    // \param[out] f_count_pu8 Pointer to number of command list entries.
    // *************************************************************************************************
    virtual void getCmdInfo(const CCmdInfo **f_cmdInfo_pa, uint8_t *f_count_pu8) = 0;

    // *************************************************************************************************
    // \brief Execute the plugin command given by f_cmdArgs_r. It is a abstract methode which shall be
    //        implemented by the deriving class.
    // \param[in] f_cmdArgs_r Reference to command arguments (at least contains 1 element).
    // \param[out] f_cmdResultDetails_r Reference to string where the command result details can be
    //             stored.
    // \return Return code of the methode. For details refer to macros RB_TED_RET_CODE_<x>.
    // *************************************************************************************************
    virtual int execCmd(const std::vector<std::string> &f_cmdArgs_r, std::string &f_cmdResultDetails_r) = 0;

    // *************************************************************************************************
    // \brief Start a new thread.
    // \param[in] f_function_pfn Pointer to function which is executed by the thread.
    // \param[in] f_threadData_p Pointer to thread data buffer passed to function specified by
    //            f_function_pfn. Could also be the nullptr pointer if there is no need for them.
    // \param[in] f_stackSize Size of thread stack in bytes. Internally increased to at least
    //            RB_TED_STACK_SIZE_MIN bytes.
    // \param[out] f_threadId_r Reference to variable which is filled with the thread ID after
    //             successful thread creation. Otherwise content is undefined.
    // \return 0 if thread could be successfully created, 1 otherwise.
    // *************************************************************************************************
    uint8_t startThread(void *(* f_function_pfn)(uint8_t &, void *), void *f_threadData_p,
                        size_t f_stackSize, pthread_t &f_threadId_r);

    // *************************************************************************************************
    // \brief Request specified thread to perform a shutdown.
    // \param[in] f_threadId Thread ID.
    // \return 0 if thread was found and request could be set, 1 otherwise.
    // *************************************************************************************************
    uint8_t requestShutdownThread(pthread_t f_threadId);

    // *************************************************************************************************
    // \brief Request all existing threads to perform a shutdown.
    // \return Number of threads which received the shutdonw request.
    // *************************************************************************************************
    uint8_t requestShutdownAllThreads(void);

    // *************************************************************************************************
    // \brief Cleanup (join) the specified thread.
    // \param[in] f_threadId Thread ID.
    // \param[out] f_threadData_p Pointer to thread data buffer. Could also be the nullptr pointer if
    //             there is no need for them.
    // \return 0 if thread was found and could be joined, 1 otherwise.
    // \note This method internally uses a blocking call.
    // *************************************************************************************************
    uint8_t cleanupThread(pthread_t f_threadId, void **f_threadData_p);

    // *************************************************************************************************
    // \brief Cleanup (join) the next thread which is in state "shutdown".
    // \param[out] f_threadId Reference to the thread ID of the thread which is cleaned
    //             up. Is not set if there is no thread for cleanup.
    // \param[out] f_threadData_p Pointer to thread data buffer. Could also be the nullptr pointer if
    //             there is no need for them. Is not set if there is no thread for cleanup.
    // \return 0 if a thread was found and could be joined, 1 otherwise.
    // *************************************************************************************************
    uint8_t cleanupNextThread(pthread_t &f_threadId, void **f_threadData_p);

    // *************************************************************************************************
    // \brief Check if the specified thread is existing.
    // \param[in] f_threadId Thread ID.
    // \return True if thread is existing, false if not.
    // *************************************************************************************************
    bool isThreadExisting(pthread_t f_threadId);

    // *************************************************************************************************
    // \brief Get the number of existing threads.
    // \return Number of threads.
    // *************************************************************************************************
    uint8_t getNumberOfThreads(void);

    // *************************************************************************************************
    // \brief Get the thread data buffer of the specified thread.
    // \param[in] f_threadId Thread ID.
    // \param[out] f_threadData_p Pointer to thread data buffer.
    // \return 0 if thread was found, 1 otherwise.
    // *************************************************************************************************
    uint8_t getThreadData(pthread_t f_threadId, void **f_threadData_p);
protected:
    // Verbose level (in the range of 0 to 255).
    const uint8_t *m_verboseLevel_pu8;
private:
    // *************************************************************************************************
    // \brief Shutdown specified thread. That means thread is set into state "shutdown".
    //        This method is called by the thread which currently performs the shutdown.
    // \param[out] f_thread_p Pointer to thread maintenance information. Must not be the nullptr
    //             pointer.
    // *************************************************************************************************
    static void shutdownThread(CThread *f_thread_p);

    // *************************************************************************************************
    // \brief Do the thread work. This is method is called within the thread.
    // \param[in] f_arg_p Pointer to the thread maintenance information.
    // \return The nullptr pointer.
    // *************************************************************************************************
    static void * doThread(void *f_arg_p);
    // List of active threads
    std::list<CThread> m_threads;
};

// Type of the create class factory
typedef CPlugin * rb_ted_createObject(void);
// Type of the destroy class factory
typedef void rb_ted_destroyObject(CPlugin *);

} // End of namespace ted
} // End of namespace saf
} // End of namespace vrte
} // End of namespace bosch

#endif // RB_TED_API_HPP_INCLUDED
