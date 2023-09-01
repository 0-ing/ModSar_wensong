#ifndef ECUCFG_PHM_2_2_METADATA_VARIANT
// =========================================================================================================================
// generated for PHM at 2020-07-16 07:17:07
//
// begin generated constexpr:
// =========================================================================================================================
#define ECUCFG_PHM_2_2_METADATA_VARIANT "THIS IS THE INCLUDE-GUARD"
#ifndef ECUCFG_PHM_METADATA_NAME
#define ECUCFG_PHM_METADATA_NAME "PHM"
#endif
//
class PHM_constexpr
{
public:
    static constexpr int majorVersion = 2; // approved
    static constexpr int minorVersion = 2;
    //
    static constexpr int N_ENUMS = 2;      // (most) ENUMS are defined in AUTOSAR Meta Model.
    static constexpr int C_ENUMS_ENUM = 0; // Name of the ENUM, e.g. SchedulingPolicyKindEnum
    //
    static constexpr int N_ENUM = 3;         // Name of the ENUM, e.g. SchedulingPolicyKindEnum
    static constexpr int C_ENUM_LITERAL = 0; // list of literals in ENUM, any reference to a literal needs to specif ENUM in processingHints as ENUM=…
    //
    static constexpr int N_IREFS = 5;
    static constexpr int A_IREFS_dummy = 0; // no specific attributes for IREFS container
    static constexpr int C_IREFS_irefHealthChannelExternalStatus = 1;
    static constexpr int C_IREFS_irefPhmRecoveryViaApplicationActionMapping = 2;
    static constexpr int C_IREFS_irefSupervisionCheckpoint = 0;
    //
    static constexpr int N_LITERAL = 4;       // list of literals in ENUM, any reference to a literal needs to specif ENUM in processingHints as ENUM=…
    static constexpr int A_LITERAL_value = 0; // provide ENUM value per LITERAL
    //
    static constexpr int N_PhmActionItem = 34;
    static constexpr int A_PhmActionItem_actionTypePlatform = 2;           // ENUM literal as text
    static constexpr int A_PhmActionItem_actionTypeProcess = 1;            // ENUM literal as text
    static constexpr int A_PhmActionItem_actionTypeWatchdog = 3;           // ENUM literal as text
    static constexpr int A_PhmActionItem_kind = 0;                         // type is one of ApplicationModeRequestPhmActionItem, FunctionGroupModeRequestPhmActionItem, PlatformPhmActionItem, ProcessPhmActionItem, RecoveryViaApplicationAction, WatchdogPhmActionItem
    static constexpr int R_PhmActionItem_actionTypePlatform = 2;           // targetNode[LITERAL]
    static constexpr int R_PhmActionItem_actionTypeProcess = 1;            // targetNode[LITERAL]
    static constexpr int R_PhmActionItem_actionTypeWatchdog = 3;           // targetNode[LITERAL]
    static constexpr int R_PhmActionItem_process = 0;                      // targetNode[Process]
    static constexpr int C_PhmActionItem_irefModeRequestApplication = 0;   // The IREF is handled as a container with 0..1 multiplicity (as there is no external triggering of the IREF defined)
    static constexpr int C_PhmActionItem_irefModeRequestFunctionGroup = 1; // The IREF is handled as a container with 0..1 multiplicity (as there is no external triggering of the IREF defined)
    //
    static constexpr int N_PhmActionListItem = 36;
    static constexpr int R_PhmActionListItem_actionListItem = 0; // targetNode[PhmActionItem]
    //
    static constexpr int N_PhmActionList = 35;
    static constexpr int A_PhmActionList_actionListExecution = 0; // ENUM literal as text
    static constexpr int R_PhmActionList_actionListExecution = 0; // targetNode[LITERAL]
    static constexpr int C_PhmActionList_actionListItem = 0;
    //
    static constexpr int N_PhmArbitrationExpressionArgHC = 39;
    static constexpr int R_PhmArbitrationExpressionArgHC_healthChannelArgument = 0; // targetNode[PhmHealthChannel]
    //
    static constexpr int N_PhmArbitrationExpressionArgLE = 40;
    static constexpr int R_PhmArbitrationExpressionArgLE_logicalExpressionArgument = 0; // targetNode[PhmArbitrationExpression]
    //
    static constexpr int N_PhmArbitrationExpression = 38;
    static constexpr int A_PhmArbitrationExpression_logicalOperator = 0; // ENUM literal as text
    static constexpr int R_PhmArbitrationExpression_logicalOperator = 0; // targetNode[LITERAL]
    static constexpr int C_PhmArbitrationExpression_healthChannelArgument = 0;
    static constexpr int C_PhmArbitrationExpression_logicalExpressionArgument = 1;
    //
    static constexpr int N_PhmArbitrationRule = 41;
    static constexpr int A_PhmArbitrationRule_ruleInitState = 0;   // ENUM literal as text
    static constexpr int R_PhmArbitrationRule_expression = 0;      // targetNode[PhmArbitrationExpression]
    static constexpr int R_PhmArbitrationRule_falseActionList = 2; // targetNode[PhmActionList]
    static constexpr int R_PhmArbitrationRule_ruleInitState = 3;   // targetNode[LITERAL]
    static constexpr int R_PhmArbitrationRule_trueActionList = 1;  // targetNode[PhmActionList]
    //
    static constexpr int N_PhmCheckpoint = 14;
    static constexpr int A_PhmCheckpoint_checkpointId = 0;
    //
    static constexpr int N_PhmGlobalSupervisionLocalRef = 31;
    static constexpr int R_PhmGlobalSupervisionLocalRef_localSupervision = 0; // targetNode[PhmLocalSupervision]
    //
    static constexpr int N_PhmGlobalSupervision = 30;
    static constexpr int A_PhmGlobalSupervision_expiredSupervisionCyclesTolerance = 0;
    static constexpr int A_PhmGlobalSupervision_supervisionCycle = 1; // TimeValue converted to [ms] with 3 digits precision
    static constexpr int C_PhmGlobalSupervision_localSupervision = 0;
    //
    static constexpr int N_PhmHealthChannelInterface = 16;
    static constexpr int A_PhmHealthChannelInterface_healthChannelId = 1; // placeholder IDs will be extracted as hash key from ARPATH of the interface
    static constexpr int A_PhmHealthChannelInterface_shortName = 0;
    static constexpr int C_PhmHealthChannelInterface_status = 0;
    //
    static constexpr int N_PhmHealthChannelStatus = 17;
    static constexpr int A_PhmHealthChannelStatus_statusId = 0;
    //
    static constexpr int N_PhmHealthChannel = 32;
    static constexpr int A_PhmHealthChannel_kind = 0;                     // type is one of HealthChannelExternalStatus, HealthChannelSupervision
    static constexpr int A_PhmHealthChannel_modeCondition = 2;            // ENUM literal as text
    static constexpr int A_PhmHealthChannel_supervisionCondition = 1;     // ENUM literal as text
    static constexpr int R_PhmHealthChannel_iref = 5;                     // targetNode[PhmIRefHealthChannelExternalStatus] IREF:PhmIRefHealthChannelExternalStatus
    static constexpr int R_PhmHealthChannel_modeCondition = 7;            // targetNode[LITERAL]
    static constexpr int R_PhmHealthChannel_supervisionCondition = 6;     // targetNode[LITERAL]
    static constexpr int R_PhmHealthChannel_supervisionGlobal = 4;        // targetNode[PhmGlobalSupervision]
    static constexpr int R_PhmHealthChannel_supervisionLocal = 0;         // targetNode[PhmLocalSupervision]
    static constexpr int R_PhmHealthChannel_supervisionLocalAlive = 1;    // targetNode[PhmLocalAliveSupervision]
    static constexpr int R_PhmHealthChannel_supervisionLocalDeadline = 2; // targetNode[PhmLocalDeadlineSupervision]
    static constexpr int R_PhmHealthChannel_supervisionLocalLogical = 3;  // targetNode[PhmLocalLogicalSupervision]
    //
    static constexpr int N_PhmIRefHealthChannelExternalStatusOWNERS = 54;
    static constexpr int R_PhmIRefHealthChannelExternalStatusOWNERS_irefOwner = 0; // targetNode[PhmHealthChannel]
    //
    static constexpr int N_PhmIRefHealthChannelExternalStatus = 53;
    static constexpr int A_PhmIRefHealthChannelExternalStatus_executable = 0;
    static constexpr int A_PhmIRefHealthChannelExternalStatus_healthChannelId = 7; // placeholder IDs will be extracted as hash key from ARPATH of the interface
    static constexpr int A_PhmIRefHealthChannelExternalStatus_portInterface = 3;   // port interface name attribute is kept for compatibility reaseons
    static constexpr int A_PhmIRefHealthChannelExternalStatus_portPrototype = 2;
    static constexpr int A_PhmIRefHealthChannelExternalStatus_processShortName = 4;
    static constexpr int A_PhmIRefHealthChannelExternalStatus_rootCPT = 1;
    static constexpr int A_PhmIRefHealthChannelExternalStatus_statusId = 6;
    static constexpr int A_PhmIRefHealthChannelExternalStatus_statusName = 5;
    static constexpr int R_PhmIRefHealthChannelExternalStatus_portInterface = 1; // targetNode[PhmHealthChannelInterface]
    static constexpr int R_PhmIRefHealthChannelExternalStatus_process = 0;       // targetNode[Process]
    static constexpr int C_PhmIRefHealthChannelExternalStatus_OWNERS = 0;
    //
    static constexpr int N_PhmIRefModeRequestApplication = 56;
    static constexpr int A_PhmIRefModeRequestApplication_hostingProcess = 0;
    static constexpr int A_PhmIRefModeRequestApplication_modeGroup = 2;
    static constexpr int A_PhmIRefModeRequestApplication_modeMachine = 1;
    static constexpr int A_PhmIRefModeRequestApplication_modeName = 3;
    static constexpr int A_PhmIRefModeRequestApplication_modeValue = 4;
    //
    static constexpr int N_PhmIRefModeRequestFunctionGroup = 59;
    static constexpr int A_PhmIRefModeRequestFunctionGroup_hostingMachine = 0;
    static constexpr int A_PhmIRefModeRequestFunctionGroup_modeGroup = 2;
    static constexpr int A_PhmIRefModeRequestFunctionGroup_modeMachine = 1;
    static constexpr int A_PhmIRefModeRequestFunctionGroup_modeName = 3;
    static constexpr int A_PhmIRefModeRequestFunctionGroup_modeValue = 4;
    //
    static constexpr int N_PhmIRefSupervisionCheckpointOWNERS = 51;
    static constexpr int R_PhmIRefSupervisionCheckpointOWNERS_irefOwner = 0; // targetNode[PhmSupervisionCheckpoint]
    //
    static constexpr int N_PhmIRefSupervisionCheckpoint = 50;
    static constexpr int A_PhmIRefSupervisionCheckpoint_CheckpointId = 6;
    static constexpr int A_PhmIRefSupervisionCheckpoint_checkpointName = 5;
    static constexpr int A_PhmIRefSupervisionCheckpoint_executable = 0;
    static constexpr int A_PhmIRefSupervisionCheckpoint_portInterface = 3; // port interface name attribute is kept for compatibility reaseons
    static constexpr int A_PhmIRefSupervisionCheckpoint_portPrototype = 2;
    static constexpr int A_PhmIRefSupervisionCheckpoint_processShortName = 4;
    static constexpr int A_PhmIRefSupervisionCheckpoint_rootCPT = 1;
    static constexpr int A_PhmIRefSupervisionCheckpoint_supervisedEntityId = 7; // placeholder IDs will be extracted as hash key from ARPATH of the interface
    static constexpr int R_PhmIRefSupervisionCheckpoint_portInterface = 1;      // targetNode[PhmSupervisedEntityInterface]
    static constexpr int R_PhmIRefSupervisionCheckpoint_process = 0;            // targetNode[Process]
    static constexpr int C_PhmIRefSupervisionCheckpoint_OWNERS = 0;
    //
    static constexpr int N_PhmLocalAliveSupervision = 23;
    static constexpr int A_PhmLocalAliveSupervision_aliveReferenceCycle = 0; // TimeValue converted to [ms] with 3 digits precision
    static constexpr int A_PhmLocalAliveSupervision_expectedAliveIndications = 1;
    static constexpr int A_PhmLocalAliveSupervision_maxMargin = 2;
    static constexpr int A_PhmLocalAliveSupervision_minMargin = 3;
    static constexpr int R_PhmLocalAliveSupervision_checkpoint = 0; // targetNode[PhmSupervisionCheckpoint]
    //
    static constexpr int N_PhmLocalCheckpointTransition = 24;
    static constexpr int R_PhmLocalCheckpointTransition_source = 0; // targetNode[PhmSupervisionCheckpoint]
    static constexpr int R_PhmLocalCheckpointTransition_target = 1; // targetNode[PhmSupervisionCheckpoint]
    //
    static constexpr int N_PhmLocalDeadlineSupervision = 25;
    static constexpr int A_PhmLocalDeadlineSupervision_maxDeadline = 0;          // TimeValue converted to [ms] with 3 digits precision
    static constexpr int A_PhmLocalDeadlineSupervision_minDeadline = 1;          // TimeValue converted to [ms] with 3 digits precision
    static constexpr int R_PhmLocalDeadlineSupervision_checkpointTransition = 0; // targetNode[PhmLocalCheckpointTransition]
    //
    static constexpr int N_PhmLocalLogicalSupervisionFinal = 27;
    static constexpr int R_PhmLocalLogicalSupervisionFinal_finalCheckpoint = 0; // targetNode[PhmSupervisionCheckpoint]
    //
    static constexpr int N_PhmLocalLogicalSupervisionInitial = 28;
    static constexpr int R_PhmLocalLogicalSupervisionInitial_initialCheckpoint = 0; // targetNode[PhmSupervisionCheckpoint]
    //
    static constexpr int N_PhmLocalLogicalSupervisionTransition = 29;
    static constexpr int R_PhmLocalLogicalSupervisionTransition_transition = 0; // targetNode[PhmLocalCheckpointTransition]
    //
    static constexpr int N_PhmLocalLogicalSupervision = 26;
    static constexpr int C_PhmLocalLogicalSupervision_finalCheckpoint = 0;
    static constexpr int C_PhmLocalLogicalSupervision_initialCheckpoint = 1;
    static constexpr int C_PhmLocalLogicalSupervision_transition = 2;
    //
    static constexpr int N_PhmLocalSupervision = 22;
    static constexpr int A_PhmLocalSupervision_failedSupervisionCyclesTolerance = 0;
    static constexpr int C_PhmLocalSupervision_aliveSupervision = 0;
    static constexpr int C_PhmLocalSupervision_deadlineSupervision = 2;
    static constexpr int C_PhmLocalSupervision_logicalSupervision = 3;
    static constexpr int C_PhmLocalSupervision_transition = 1;
    //
    static constexpr int N_PhmRecoveryActionInterface = 18;
    static constexpr int A_PhmRecoveryActionInterface_shortName = 0;
    static constexpr int C_PhmRecoveryActionInterface_recovery = 0;
    //
    static constexpr int N_PhmRecoveryActionOperation = 19;
    static constexpr int A_PhmRecoveryActionOperation_fireAndForget = 0;
    //
    static constexpr int N_PhmRecoveryViaApplicationActionMappingIrefOWNERS = 47;
    static constexpr int R_PhmRecoveryViaApplicationActionMappingIrefOWNERS_irefOwner = 0; // targetNode[PhmRecoveryViaApplicationActionMapping]
    //
    static constexpr int N_PhmRecoveryViaApplicationActionMappingIref = 46;
    static constexpr int A_PhmRecoveryViaApplicationActionMappingIref_executable = 0;
    static constexpr int A_PhmRecoveryViaApplicationActionMappingIref_pPort = 2;
    static constexpr int A_PhmRecoveryViaApplicationActionMappingIref_processShortName = 3;
    static constexpr int A_PhmRecoveryViaApplicationActionMappingIref_rootCPT = 1;
    static constexpr int R_PhmRecoveryViaApplicationActionMappingIref_process = 1;      // targetNode[Process]
    static constexpr int R_PhmRecoveryViaApplicationActionMappingIref_targetMethod = 0; // targetNode[PhmRecoveryActionOperation]
    static constexpr int C_PhmRecoveryViaApplicationActionMappingIref_OWNERS = 0;
    //
    static constexpr int N_PhmRecoveryViaApplicationActionMapping = 45;
    static constexpr int A_PhmRecoveryViaApplicationActionMapping_shortName = 0;
    static constexpr int R_PhmRecoveryViaApplicationActionMapping_iref = 2;                         // targetNode[PhmRecoveryViaApplicationActionMappingIref] IREF: PhmRecoveryViaApplicationActionMappingIref
    static constexpr int R_PhmRecoveryViaApplicationActionMapping_process = 1;                      // targetNode[Process]
    static constexpr int R_PhmRecoveryViaApplicationActionMapping_recoveryViaApplicationAction = 0; // targetNode[PhmActionItem]
    //
    static constexpr int N_PhmSupervisedEntityInterface = 13;
    static constexpr int A_PhmSupervisedEntityInterface_shortName = 0;
    static constexpr int A_PhmSupervisedEntityInterface_supervisedEntityId = 1; // placeholder IDs will be extracted as hash key from ARPATH of the interface
    static constexpr int C_PhmSupervisedEntityInterface_checkpoint = 0;
    //
    static constexpr int N_PhmSupervisionCheckpoint = 21;
    static constexpr int R_PhmSupervisionCheckpoint_iref = 0;    // targetNode[PhmIRefSupervisionCheckpoint] IREF:PhmIRefSupervisionCheckpoint
    static constexpr int R_PhmSupervisionCheckpoint_process = 1; // targetNode[Process]
    //
    static constexpr int N_PlatformHealthManagementContribution = 20;
    static constexpr int A_PlatformHealthManagementContribution_shortName = 0;
    static constexpr int C_PlatformHealthManagementContribution_action = 4;
    static constexpr int C_PlatformHealthManagementContribution_actionList = 5;
    static constexpr int C_PlatformHealthManagementContribution_checkpoint = 0;
    static constexpr int C_PlatformHealthManagementContribution_globalSupervision = 2;
    static constexpr int C_PlatformHealthManagementContribution_healthChannel = 3;
    static constexpr int C_PlatformHealthManagementContribution_localSupervision = 1;
    static constexpr int C_PlatformHealthManagementContribution_logicalExpression = 6;
    static constexpr int C_PlatformHealthManagementContribution_rule = 7;
    //
    static constexpr int N_Process = 10;
    static constexpr int A_Process_exectutableName = 1;
    static constexpr int A_Process_shortName = 0;
    //
    static constexpr int N_ROOT = 0;       // ROOT Structure NOT TO BE CHANGED !
    static constexpr int A_ROOT_name = 0;  // ROOT Structure NOT TO BE CHANGED !
    static constexpr int C_ROOT_ENUMS = 1; // ENUMS container
    static constexpr int C_ROOT_IREFS = 2; // IREFS container
    static constexpr int C_ROOT_PhmHealthChannelInterface = 5;
    static constexpr int C_ROOT_PhmRecoveryActionInterface = 7;
    static constexpr int C_ROOT_PhmRecoveryViaApplicationActionMapping = 8;
    static constexpr int C_ROOT_PhmSupervisedEntityInterface = 4;
    static constexpr int C_ROOT_PlatformHealthManagementContribution = 6;
    static constexpr int C_ROOT_Process = 3;
    static constexpr int C_ROOT_UNUSED = 0; // UNUSED container allows to keep nodeIndex sequence if nodes are disabled.
    //
    static constexpr int N_UNUSED = 1; // UNUSED container allows to keep nodeIndex sequence if nodes are disabled.
    //
};
// =========================================================================================================================
// end generated constexpr
// =========================================================================================================================
#endif // ECUCFG_PHM_2_2_METADATA_VARIANT
