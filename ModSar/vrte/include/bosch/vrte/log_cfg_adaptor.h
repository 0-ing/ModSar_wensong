// =============================================================================
//  C O P Y R I G H T
// -----------------------------------------------------------------------------
//  Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
//  This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
//  distribution is an offensive act against international law and may be
//  prosecuted under federal law. Its content is company confidential.
// =============================================================================

#ifndef LOG_CFG_ADAPTOR_H_INCLUDED
#define LOG_CFG_ADAPTOR_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

// !!! Sync and Mode definitions below are mirrored in ecucfgdsl. PLEASE don't change !!!
/* Offline Logstorage sync strategies */
#define LOGCFG_LOGSTORAGE_SYNC_ON_ERROR                  -1 /* error case */
#define LOGCFG_LOGSTORAGE_SYNC_UNSET                     0  /* strategy not set */
#define LOGCFG_LOGSTORAGE_SYNC_ON_MSG                    1 /* default, on message sync */
#define LOGCFG_LOGSTORAGE_SYNC_ON_DAEMON_EXIT            (1 << 1) /* sync on daemon exit */
#define LOGCFG_LOGSTORAGE_SYNC_ON_DEMAND                 (1 << 2) /* sync on demand */
#define LOGCFG_LOGSTORAGE_SYNC_ON_DEVICE_DISCONNECT      (1 << 3) /* sync on device disconnect*/
#define LOGCFG_LOGSTORAGE_SYNC_ON_SPECIFIC_SIZE          (1 << 4) /* sync on after specific size */
#define LOGCFG_LOGSTORAGE_SYNC_ON_FILE_SIZE              (1 << 5) /* sync on file size reached */

/* Supported DLT log output destinations */
#define LOGCFG_LOG_MODE_CONSOLE (1 << 0)
#define LOGCFG_LOG_MODE_FILE    (1 << 1)
#define LOGCFG_LOG_MODE_DLT     (1 << 2)
#define LOGCFG_LOG_MODE_REMOTE  (1 << 3)

/**
 * @brief log level values
 *
 */
typedef enum {
    LOGCFG_LOG_DEFAULT  = -1,               /**@ Default log level */
    LOGCFG_LOG_OFF      = 0x00,             /**@ Log level off */
    LOGCFG_LOG_FATAL    = 0x01,             /**@ fatal system error */
    LOGCFG_LOG_ERROR    = 0x02,             /**@ error with impact to correct functionality */
    LOGCFG_LOG_WARN     = 0x03,             /**@ warning, correct behaviour could not be ensured */
    LOGCFG_LOG_INFO     = 0x04,             /**@ informational */
    LOGCFG_LOG_DEBUG    = 0x05,             /**@ debug  */
    LOGCFG_LOG_VERBOSE  = 0x06,             /**@ highest grade of information */
    LOGCFG_LOG_MAX                          /**@ maximum value, used for range check */
} LogCfgLogLevel;

/**
 * @brief API result values
 *
 */
typedef enum {
    LOGCFG_RESULT_OK,                           /**@ Method completed successfully */
    LOGCFG_RESULT_ERR_PARAM,                    /**@ An invalid parameter was passed to a method */
    LOGCFG_RESULT_ERR_DEFAULTS,                 /**@ Config could not be loaded, defaults are being returned */
    LOGCFG_RESULT_ERR_INIT,                     /**@ Config initialization with flatcfg ran into an error */
    LOGCFG_RESULT_ERR_LOAD                      /**@ Config load with flatcfg ran into an error */
}
LogCfgResult;

 /**
 * @brief LogCfgLogSink structure
 */
typedef struct {
    int32_t vrte_specific_size;
    int32_t vrte_max_no_files;
    int32_t vrte_sync_behavior; /* see DLTCFG_LOGSTORAGE_SYNC_* defines */
    int32_t vrte_max_file_size;

    LogCfgLogLevel dls_default_log_threshold;
    bool dls_non_verbose_mode;
    const char* dls_path;   // uri string
    const char *dls_context_id;
    const char *dls_context_description;
    const char *dls_application_id;
    const char *dls_application_description;
    int32_t log_category;
}
LogCfgLogSink;

/**
 * @brief DltCfgLogAndTraceInstantiation structure
 *
 */
typedef struct {
    int32_t vrte_offline_storage_cache_size;
    const char* vrte_offline_log_storage_delimiter;
    int32_t vrte_offline_log_storage_timestamp;
    const char* ecu_id;
    int32_t num_log_sinks;
    LogCfgLogSink* log_sinks;
}
LogCfgLogAndTraceInstantiation;

/**
 * @brief Obtains a shared pointer to the flatcfg binary file, denoting the entry point of
 *        process specific log and trace configuration values.
 *
 * @param none
 *
 * @return LogCfgResult value
 */
LogCfgResult log_cfg_load();

/**
 * @brief Obtains a set of log and trace configuration values (daemon use case)
 *        Please call log_cfg_unload_daemon() when you are done using configuration values.
 *
 * @param daemonCfg - config struct to be filled
 *
 * @return LogCfgResult value
 */
LogCfgResult log_cfg_load_daemon(LogCfgLogAndTraceInstantiation* daemonCfg);

/**
 * @brief Free a set of log and trace configuration values (daemon use case)
 *
 * @param daemonCfg - config struct to be freed
 *
 */
void log_cfg_unload_daemon(LogCfgLogAndTraceInstantiation* daemonCfg);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LOG_CFG_ADAPTOR_H_INCLUDED */
