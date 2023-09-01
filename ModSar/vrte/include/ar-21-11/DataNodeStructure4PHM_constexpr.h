#ifndef ECUCFG_PHM_4_1_METADATA_VARIANT
// =========================================================================================================================
// generated for PHM at 2022-09-29 04:10:25 
//
// begin generated constexpr:
// =========================================================================================================================
#define ECUCFG_PHM_4_1_METADATA_VARIANT "THIS IS THE INCLUDE-GUARD"
#ifndef ECUCFG_PHM_METADATA_NAME 
#define ECUCFG_PHM_METADATA_NAME "PHM"
#endif
//
class PHM_constexpr {
public:
static constexpr int majorVersion = 4; // unspecified
static constexpr int minorVersion = 1;
//
static constexpr int N_IREFS                                  = 5;
static constexpr int C_IREFS_irefSupervisionCheckpoint        = 11; // childNode[PhmIRefSupervisionCheckpoint]
// 
static constexpr int N_PhmAliveSupervision                    = 16;
static constexpr int A_PhmAliveSupervision_aliveReferenceCycle  = 1;
static constexpr int A_PhmAliveSupervision_failedSupervisionCyclesTolerance  = 6;
static constexpr int A_PhmAliveSupervision_isMaxCheckDisabled  = 5;
static constexpr int A_PhmAliveSupervision_isMinCheckDisabled  = 4;
static constexpr int A_PhmAliveSupervision_maxAliveIndications  = 3;
static constexpr int A_PhmAliveSupervision_minAliveIndications  = 2;
static constexpr int A_PhmAliveSupervision_refCheckPointIndex  = 0;
static constexpr int A_PhmAliveSupervision_refProcessIndex    = 7;
static constexpr int R_PhmAliveSupervision_infoCheckpoint     = 0;
static constexpr int C_PhmAliveSupervision_refFunctionGroupStates  = 0; // childNode[PhmRefFunctionGroupStates]
// 
static constexpr int N_PhmCheckpointTransition                = 15;
static constexpr int A_PhmCheckpointTransition_refSourceCPIndex  = 0;
static constexpr int A_PhmCheckpointTransition_refTargetCPIndex  = 1;
static constexpr int R_PhmCheckpointTransition_infoSource     = 0;
static constexpr int R_PhmCheckpointTransition_infoTarget     = 1;
// 
static constexpr int N_PhmDeadlineSupervision                 = 17;
static constexpr int A_PhmDeadlineSupervision_maxDeadline     = 1;
static constexpr int A_PhmDeadlineSupervision_minDeadline     = 2;
static constexpr int R_PhmDeadlineSupervision_checkpointTransition  = 0;
static constexpr int C_PhmDeadlineSupervision_refFunctionGroupStates  = 1; // childNode[PhmRefFunctionGroupStates]
static constexpr int C_PhmDeadlineSupervision_refProcesses    = 0; // childNode[PhmRefProcess]
// 
static constexpr int N_PhmGlobalSupervisionLocalRef           = 27;
static constexpr int A_PhmGlobalSupervisionLocalRef_refLocalSupervisionIndex  = 0;
// 
static constexpr int N_PhmGlobalSupervision                   = 26;
static constexpr int A_PhmGlobalSupervision_expiredSupervisionCyclesTolerance  = 1;
static constexpr int A_PhmGlobalSupervision_supervisionCycle  = 0;
static constexpr int C_PhmGlobalSupervision_localSupervision  = 2; // childNode[PhmGlobalSupervisionLocalRef]
static constexpr int C_PhmGlobalSupervision_refFunctionGroupStates  = 4; // childNode[PhmRefFunctionGroupStatesGlobal]
static constexpr int C_PhmGlobalSupervision_refProcesses      = 3; // childNode[PhmRefProcess]
// 
static constexpr int N_PhmIRefSupervisionCheckpoint           = 31;
static constexpr int A_PhmIRefSupervisionCheckpoint_checkpointId  = 6;
static constexpr int A_PhmIRefSupervisionCheckpoint_checkpointName  = 5;
static constexpr int A_PhmIRefSupervisionCheckpoint_portPrototype  = 2;
static constexpr int A_PhmIRefSupervisionCheckpoint_processShortName  = 4;
static constexpr int A_PhmIRefSupervisionCheckpoint_supervisedEntityId  = 7;
// 
static constexpr int N_PhmLocalSupervision                    = 22;
static constexpr int A_PhmLocalSupervision_infoRefInterfacePath  = 0;
static constexpr int C_PhmLocalSupervision_PhmRefAliveSupervision  = 0; // childNode[PhmRefAliveSupervision]
static constexpr int C_PhmLocalSupervision_PhmRefDeadlineSupervision  = 1; // childNode[PhmRefDeadlineSupervision]
static constexpr int C_PhmLocalSupervision_PhmRefLogicalSupervision  = 2; // childNode[PhmRefLogicalSupervision]
// 
static constexpr int N_PhmLogicalSupervisionFinal             = 19;
static constexpr int R_PhmLogicalSupervisionFinal_finalCheckpoint  = 0;
// 
static constexpr int N_PhmLogicalSupervisionInitial           = 20;
static constexpr int R_PhmLogicalSupervisionInitial_initialCheckpoint  = 0;
// 
static constexpr int N_PhmLogicalSupervisionTransition        = 21;
static constexpr int R_PhmLogicalSupervisionTransition_transition  = 0;
// 
static constexpr int N_PhmLogicalSupervision                  = 18;
static constexpr int C_PhmLogicalSupervision_finalCheckpoint  = 2; // childNode[PhmLogicalSupervisionFinal]
static constexpr int C_PhmLogicalSupervision_initialCheckpoint  = 0; // childNode[PhmLogicalSupervisionInitial]
static constexpr int C_PhmLogicalSupervision_refFunctionGroupStates  = 4; // childNode[PhmRefFunctionGroupStates]
static constexpr int C_PhmLogicalSupervision_refProcesses     = 3; // childNode[PhmRefProcess]
static constexpr int C_PhmLogicalSupervision_transition       = 1; // childNode[PhmLogicalSupervisionTransition]
// 
static constexpr int N_PhmRecoveryNotificationToPPortPrototypeMapping  = 29;
static constexpr int C_PhmRecoveryNotificationToPPortPrototypeMapping_recoveryNotification  = 0; // childNode[RecoveryNotification]
// 
static constexpr int N_PhmRefAliveSupervision                 = 24;
static constexpr int A_PhmRefAliveSupervision_autosarPath     = 0;
static constexpr int A_PhmRefAliveSupervision_refAliveSupervisionIdx  = 1;
static constexpr int R_PhmRefAliveSupervision_refPhmAliveSupervision  = 0;
// 
static constexpr int N_PhmRefDeadlineSupervision              = 23;
static constexpr int A_PhmRefDeadlineSupervision_autosarPath  = 0;
static constexpr int A_PhmRefDeadlineSupervision_refDeadlineSpervisionIdx  = 1;
static constexpr int R_PhmRefDeadlineSupervision_refPhmDeadlineSupervision  = 0;
// 
static constexpr int N_PhmRefFunctionGroupStatesGlobal        = 28;
static constexpr int A_PhmRefFunctionGroupStatesGlobal_autosarPath  = 0;
static constexpr int A_PhmRefFunctionGroupStatesGlobal_expiredSupervisionTolerance  = 1;
// 
static constexpr int N_PhmRefFunctionGroupStates              = 11;
static constexpr int A_PhmRefFunctionGroupStates_autosarPath  = 1;
// 
static constexpr int N_PhmRefLogicalSupervision               = 25;
static constexpr int A_PhmRefLogicalSupervision_autosarPath   = 0;
static constexpr int A_PhmRefLogicalSupervision_refLogicalSupervisionIdx  = 1;
static constexpr int R_PhmRefLogicalSupervision_refPhmLogicalSupervision  = 0;
// 
static constexpr int N_PhmRefProcess                          = 12;
static constexpr int A_PhmRefProcess_index                    = 0;
// 
static constexpr int N_PhmSupervisedEntityInterface           = 13;
static constexpr int A_PhmSupervisedEntityInterface_instanceSpecifier  = 0;
static constexpr int A_PhmSupervisedEntityInterface_interfacePath  = 4;
static constexpr int A_PhmSupervisedEntityInterface_portPrototype  = 3;
static constexpr int A_PhmSupervisedEntityInterface_processShortName  = 1;
static constexpr int A_PhmSupervisedEntityInterface_refProcessIndex  = 5;
static constexpr int A_PhmSupervisedEntityInterface_supervisedEntityId  = 2;
// 
static constexpr int N_PhmSupervisionCheckpoint               = 14;
static constexpr int A_PhmSupervisionCheckpoint_checkpointId  = 1;
static constexpr int A_PhmSupervisionCheckpoint_infoExecutable  = 4;
static constexpr int A_PhmSupervisionCheckpoint_infoInterfaceName  = 6;
static constexpr int A_PhmSupervisionCheckpoint_infoPortPrototype  = 8;
static constexpr int A_PhmSupervisionCheckpoint_infoProcess   = 3;
static constexpr int A_PhmSupervisionCheckpoint_infoRootCPT   = 5;
static constexpr int A_PhmSupervisionCheckpoint_infoSupervisedEntityId  = 7;
static constexpr int A_PhmSupervisionCheckpoint_refInterfaceIndex  = 2;
static constexpr int A_PhmSupervisionCheckpoint_shortName     = 0;
static constexpr int R_PhmSupervisionCheckpoint_iref          = 0;
static constexpr int R_PhmSupervisionCheckpoint_process       = 1;
// 
static constexpr int N_Process                                = 10;
static constexpr int A_Process_autosarPath                    = 2;
static constexpr int A_Process_executableName                 = 1;
static constexpr int A_Process_index                          = 3;
static constexpr int A_Process_shortName                      = 0;
static constexpr int C_Process_refFunctionGroupStates         = 0; // childNode[PhmRefFunctionGroupStates]
// 
static constexpr int N_ROOT                                   = 0;
static constexpr int C_ROOT_IREFS                             = 0; // childNode[IREFS]
static constexpr int C_ROOT_PhmAliveSupervision               = 5; // childNode[PhmAliveSupervision]
static constexpr int C_ROOT_PhmCheckpointTransition           = 4; // childNode[PhmCheckpointTransition]
static constexpr int C_ROOT_PhmDeadlineSupervision            = 6; // childNode[PhmDeadlineSupervision]
static constexpr int C_ROOT_PhmGlobalSupervision              = 9; // childNode[PhmGlobalSupervision]
static constexpr int C_ROOT_PhmLocalSupervision               = 8; // childNode[PhmLocalSupervision]
static constexpr int C_ROOT_PhmLogicalSupervision             = 7; // childNode[PhmLogicalSupervision]
static constexpr int C_ROOT_PhmRecoveryNotification           = 10; // childNode[RecoveryNotification]
static constexpr int C_ROOT_PhmRecoveryNotificationToPPortPrototypeMapping  = 12; // childNode[PhmRecoveryNotificationToPPortPrototypeMapping]
static constexpr int C_ROOT_PhmSupervisedEntityInterface      = 2; // childNode[PhmSupervisedEntityInterface]
static constexpr int C_ROOT_PhmSupervisionCheckpoint          = 3; // childNode[PhmSupervisionCheckpoint]
static constexpr int C_ROOT_Process                           = 1; // childNode[Process]
// 
static constexpr int N_RecoveryNotification                   = 30;
static constexpr int A_RecoveryNotification_contextkeyIref    = 7;
static constexpr int A_RecoveryNotification_functionGroupMetaModelIdentifier  = 3;
static constexpr int A_RecoveryNotification_instaceSpecifier  = 5;
static constexpr int A_RecoveryNotification_recoveryNotificationRetry  = 6;
static constexpr int A_RecoveryNotification_recoveryNotificationTimeout  = 2;
static constexpr int A_RecoveryNotification_refGlobalSupervisionIndex  = 4;
static constexpr int A_RecoveryNotification_shortName         = 1;
// 
};
// =========================================================================================================================
// end generated constexpr
// =========================================================================================================================
#endif // ECUCFG_PHM_4_1_METADATA_VARIANT
