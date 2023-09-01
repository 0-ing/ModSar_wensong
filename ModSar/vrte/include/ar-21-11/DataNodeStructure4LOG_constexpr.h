#ifndef ECUCFG_LOG_2_1_METADATA_VARIANT
// =========================================================================================================================
// generated for LOG at 2022-09-29 04:10:23 
//
// begin generated constexpr:
// =========================================================================================================================
#define ECUCFG_LOG_2_1_METADATA_VARIANT "THIS IS THE INCLUDE-GUARD"
#ifndef ECUCFG_LOG_METADATA_NAME 
#define ECUCFG_LOG_METADATA_NAME "LOG"
#endif
//
class LOG_constexpr {
public:
static constexpr int majorVersion = 2; // draft
static constexpr int minorVersion = 1;
//
static constexpr int N_DaemonConfig                           = 10;
static constexpr int A_DaemonConfig_ecuId                     = 0;
static constexpr int A_DaemonConfig_logStorageCacheSizeKB     = 12;
static constexpr int A_DaemonConfig_logStorageDelimiter       = 10;
static constexpr int A_DaemonConfig_logStorageTimestamp       = 11;
// 
static constexpr int N_DltApplication                         = 30;
static constexpr int A_DltApplication_description             = 1;
static constexpr int A_DltApplication_id                      = 0;
// 
static constexpr int N_DltContext                             = 31;
static constexpr int A_DltContext_description                 = 1;
static constexpr int A_DltContext_id                          = 0;
// 
static constexpr int N_DltSinkDaemon                          = 11;
static constexpr int A_DltSinkDaemon_category                 = 0;
static constexpr int A_DltSinkDaemon_defaultLogLevel          = 4;
static constexpr int A_DltSinkDaemon_logStorageMaxFileSizeB   = 6;
static constexpr int A_DltSinkDaemon_logStorageMaxNoFiles     = 7;
static constexpr int A_DltSinkDaemon_logStoragePath           = 5;
static constexpr int A_DltSinkDaemon_logStorageSpecificSizeB  = 9;
static constexpr int A_DltSinkDaemon_logStorageSyncBehavior   = 8;
static constexpr int A_DltSinkDaemon_nonVerboseMode           = 1;
static constexpr int R_DltSinkDaemon_application              = 2;
static constexpr int R_DltSinkDaemon_context                  = 3;
// 
static constexpr int N_DltSinkUser                            = 21;
static constexpr int A_DltSinkUser_category                   = 0;
static constexpr int A_DltSinkUser_defaultLogLevel            = 4;
static constexpr int A_DltSinkUser_nonVerboseMode             = 1;
static constexpr int R_DltSinkUser_context                    = 3;
// 
static constexpr int N_ROOT                                   = 0;
static constexpr int C_ROOT_daemonConfig                      = 1; // childNode[DaemonConfig]
static constexpr int C_ROOT_dltApplication                    = 5; // childNode[DltApplication]
static constexpr int C_ROOT_dltContext                        = 6; // childNode[DltContext]
static constexpr int C_ROOT_dltSinksDaemon                    = 2; // childNode[DltSinkDaemon]
static constexpr int C_ROOT_dltSinksUser                      = 4; // childNode[DltSinkUser]
static constexpr int C_ROOT_userConfig                        = 3; // childNode[UserConfig]
// 
static constexpr int N_UserConfig                             = 20;
static constexpr int A_UserConfig_defaultApplicationDescription  = 14;
static constexpr int A_UserConfig_defaultApplicationId        = 13;
static constexpr int A_UserConfig_defaultChannelContextDescription  = 11;
static constexpr int A_UserConfig_defaultChannelContextId     = 10;
static constexpr int A_UserConfig_defaultLibQueueSize         = 12;
static constexpr int A_UserConfig_disableLogging              = 3;
static constexpr int A_UserConfig_fifoAgainWait               = 24;
static constexpr int A_UserConfig_fifoWaitMillisec            = 23;
static constexpr int A_UserConfig_ipcPath                     = 21;
static constexpr int A_UserConfig_ipcUserDirPath              = 22;
static constexpr int A_UserConfig_queueSize                   = 1;
static constexpr int A_UserConfig_receiverThreadName          = 20;
static constexpr int A_UserConfig_sessionIdSupport            = 2;
static constexpr int R_UserConfig_application                 = 4;
// 
};
// =========================================================================================================================
// end generated constexpr
// =========================================================================================================================
#endif // ECUCFG_LOG_2_1_METADATA_VARIANT
