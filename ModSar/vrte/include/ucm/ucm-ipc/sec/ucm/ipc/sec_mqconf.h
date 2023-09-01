//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         exm/ucm/ipc/exm_mqconf.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__SEC_UCM_IPC__SEC_MQCONF__H_
#define UCM_AAP_IPC__SEC_UCM_IPC__SEC_MQCONF__H_

#ifdef UCM_MQIPC_SERVER_NAME
#error Bogus inclusion of IPC MQ configuration file
#endif

/// @brief Server mqueue file system name
#define UCM_MQIPC_SERVER_NAME "/ucm-ipc-sec-server"

/// @brief Client mqueue file system name template
#define UCM_MQIPC_CLIENT_NAME "/ucm-ipc-sec-client"

/// @brief Default client ID
#define UCM_MQIPC_CLIENT_UUID_DEFAULT 42

/// @brief Termination client UUID
#define UCM_MQIPC_CLIENT_UUID_TERM 43

/// @brief First free UUID for additional clients
#define UCM_MQIPC_CLIENT_UUID_FREE 44

#endif // UCM_AAP_IPC__SEC_UCM_IPC__SEC_MQCONF__H_

