#ifndef ECUCFG_DIA_4_1_METADATA_VARIANT
// =========================================================================================================================
// generated for DIA at 2022-09-29 04:10:25 
//
// begin generated constexpr:
// =========================================================================================================================
#define ECUCFG_DIA_4_1_METADATA_VARIANT "THIS IS THE INCLUDE-GUARD"
#ifndef ECUCFG_DIA_METADATA_NAME 
#define ECUCFG_DIA_METADATA_NAME "DIA"
#endif
//
class DIA_constexpr {
public:
static constexpr int majorVersion = 4; // draft
static constexpr int minorVersion = 1;
//
static constexpr int N_AdaptivePPort                          = 71;
static constexpr int A_AdaptivePPort_shortName                = 0;
// 
static constexpr int N_AdaptiveRPort                          = 74;
static constexpr int A_AdaptiveRPort_shortName                = 0;
// 
static constexpr int N_DiagnosticAccessPermissionSecurityLevel  = 112;
static constexpr int R_DiagnosticAccessPermissionSecurityLevel_securityLevel  = 0;
// 
static constexpr int N_DiagnosticAccessPermissionSession      = 111;
static constexpr int R_DiagnosticAccessPermissionSession_diagnosticSession  = 0;
// 
static constexpr int N_DiagnosticAccessPermission             = 110;
static constexpr int A_DiagnosticAccessPermission_shortName   = 0;
static constexpr int C_DiagnosticAccessPermission_diagnosticSessions  = 0; // childNode[DiagnosticAccessPermissionSession]
static constexpr int C_DiagnosticAccessPermission_securityLevels  = 1; // childNode[DiagnosticAccessPermissionSecurityLevel]
// 
static constexpr int N_DiagnosticConditionGroupRefEnable      = 53;
static constexpr int R_DiagnosticConditionGroupRefEnable_enableCondition  = 0;
// 
static constexpr int N_DiagnosticConditionGroup               = 51;
static constexpr int A_DiagnosticConditionGroup_kind          = 1;
static constexpr int A_DiagnosticConditionGroup_shortName     = 0;
static constexpr int C_DiagnosticConditionGroup_refEnable     = 1; // childNode[DiagnosticConditionGroupRefEnable]
// 
static constexpr int N_DiagnosticCondition                    = 46;
static constexpr int A_DiagnosticCondition_kind               = 1;
static constexpr int A_DiagnosticCondition_shortName          = 0;
// 
static constexpr int N_DiagnosticContributionSet              = 100;
static constexpr int A_DiagnosticContributionSet_prop_maxNumberOfRequestCorrectlyReceivedResponsePending  = 1;
static constexpr int A_DiagnosticContributionSet_prop_responseOnSecondDeclinedRequest  = 2;
static constexpr int A_DiagnosticContributionSet_shortName    = 0;
static constexpr int R_DiagnosticContributionSet_prop_clearDtcLimitation  = 1;
static constexpr int C_DiagnosticContributionSet_debounceAlgorithmProps  = 0; // childNode[DiagnosticDebounceAlgorithmProps]
// 
static constexpr int N_DiagnosticDataElement                  = 65;
static constexpr int A_DiagnosticDataElement_basetype_shortName  = 12;
static constexpr int A_DiagnosticDataElement_basetype_size    = 13;
static constexpr int A_DiagnosticDataElement_maxNumberOfElements  = 1;
static constexpr int A_DiagnosticDataElement_shortName        = 0;
static constexpr int R_DiagnosticDataElement_arraySizeSemantics  = 0;
// 
static constexpr int N_DiagnosticDataIdentifierParameter      = 62;
static constexpr int A_DiagnosticDataIdentifierParameter_bitOffset  = 0;
static constexpr int R_DiagnosticDataIdentifierParameter_dataElement  = 0;
// 
static constexpr int N_DiagnosticDataIdentifierPortIref       = 121;
static constexpr int A_DiagnosticDataIdentifierPortIref_processDesignShortName  = 0;
static constexpr int A_DiagnosticDataIdentifierPortIref_targetPortContextKey  = 1;
static constexpr int R_DiagnosticDataIdentifierPortIref_processDesign  = 0;
// 
static constexpr int N_DiagnosticDataIdentifierSetRefs        = 64;
static constexpr int R_DiagnosticDataIdentifierSetRefs_dataIdentifier  = 0;
// 
static constexpr int N_DiagnosticDataIdentifierSet            = 63;
static constexpr int A_DiagnosticDataIdentifierSet_shortName  = 0;
static constexpr int C_DiagnosticDataIdentifierSet_refDid     = 0; // childNode[DiagnosticDataIdentifierSetRefs]
// 
static constexpr int N_DiagnosticDataIdentifier               = 61;
static constexpr int A_DiagnosticDataIdentifier_didSize       = 3;
static constexpr int A_DiagnosticDataIdentifier_id            = 1;
static constexpr int A_DiagnosticDataIdentifier_kind          = 2;
static constexpr int A_DiagnosticDataIdentifier_representsVin  = 4;
static constexpr int A_DiagnosticDataIdentifier_shortName     = 0;
static constexpr int C_DiagnosticDataIdentifier_dataElement   = 0; // childNode[DiagnosticDataIdentifierParameter]
// 
static constexpr int N_DiagnosticDataPortMapping              = 120;
static constexpr int A_DiagnosticDataPortMapping_shortName    = 0;
static constexpr int R_DiagnosticDataPortMapping_diagnosticDataElement  = 1;
static constexpr int R_DiagnosticDataPortMapping_diagnosticDataIdentifier  = 0;
static constexpr int R_DiagnosticDataPortMapping_iref         = 2;
// 
static constexpr int N_DiagnosticDebounceAlgorithmProps       = 106;
static constexpr int A_DiagnosticDebounceAlgorithmProps_algo_shortName  = 0;
// 
static constexpr int N_DiagnosticEventPortIref                = 33;
static constexpr int A_DiagnosticEventPortIref_processDesignShortName  = 0;
static constexpr int A_DiagnosticEventPortIref_targetPortContextKey  = 1;
static constexpr int R_DiagnosticEventPortIref_processDesign  = 0;
// 
static constexpr int N_DiagnosticEventPortMapping             = 32;
static constexpr int A_DiagnosticEventPortMapping_shortName   = 0;
static constexpr int R_DiagnosticEventPortMapping_diagnosticEvent  = 0;
static constexpr int R_DiagnosticEventPortMapping_iref        = 1;
// 
static constexpr int N_DiagnosticEventToDebounceAlgorithmMapping  = 107;
static constexpr int A_DiagnosticEventToDebounceAlgorithmMapping_shortName  = 0;
static constexpr int R_DiagnosticEventToDebounceAlgorithmMapping_debounceAlgorithm  = 0;
static constexpr int R_DiagnosticEventToDebounceAlgorithmMapping_diagnosticEvent  = 1;
// 
static constexpr int N_DiagnosticEventToEnableConditionGroupMapping  = 37;
static constexpr int A_DiagnosticEventToEnableConditionGroupMapping_shortName  = 0;
static constexpr int R_DiagnosticEventToEnableConditionGroupMapping_diagnosticEvent  = 0;
static constexpr int R_DiagnosticEventToEnableConditionGroupMapping_enableConditionGroup  = 1;
// 
static constexpr int N_DiagnosticEventToOperationCycleMapping  = 35;
static constexpr int A_DiagnosticEventToOperationCycleMapping_shortName  = 0;
static constexpr int R_DiagnosticEventToOperationCycleMapping_diagnosticEvent  = 0;
static constexpr int R_DiagnosticEventToOperationCycleMapping_operationCycle  = 1;
// 
static constexpr int N_DiagnosticEventToTroubleCodeUdsMapping  = 38;
static constexpr int A_DiagnosticEventToTroubleCodeUdsMapping_shortName  = 0;
static constexpr int R_DiagnosticEventToTroubleCodeUdsMapping_diagnosticEvent  = 0;
static constexpr int R_DiagnosticEventToTroubleCodeUdsMapping_troubleCodeUds  = 1;
// 
static constexpr int N_DiagnosticEvent                        = 31;
static constexpr int A_DiagnosticEvent_confirmationthreshold  = 4;
static constexpr int A_DiagnosticEvent_shortName              = 0;
// 
static constexpr int N_DiagnosticExtendedDataRecordParameter  = 67;
static constexpr int A_DiagnosticExtendedDataRecordParameter_bitOffset  = 0;
static constexpr int R_DiagnosticExtendedDataRecordParameter_dataElement  = 0;
// 
static constexpr int N_DiagnosticExtendedDataRecord           = 66;
static constexpr int A_DiagnosticExtendedDataRecord_customTrigger  = 1;
static constexpr int A_DiagnosticExtendedDataRecord_recordNumber  = 2;
static constexpr int A_DiagnosticExtendedDataRecord_shortName  = 0;
static constexpr int A_DiagnosticExtendedDataRecord_update    = 3;
static constexpr int R_DiagnosticExtendedDataRecord_trigger   = 0;
static constexpr int C_DiagnosticExtendedDataRecord_recordElement  = 0; // childNode[DiagnosticExtendedDataRecordParameter]
// 
static constexpr int N_DiagnosticFreezeFrame                  = 91;
static constexpr int A_DiagnosticFreezeFrame_customTrigger    = 1;
static constexpr int A_DiagnosticFreezeFrame_recordNumber     = 3;
static constexpr int A_DiagnosticFreezeFrame_shortName        = 0;
static constexpr int A_DiagnosticFreezeFrame_update           = 2;
static constexpr int R_DiagnosticFreezeFrame_trigger          = 0;
// 
static constexpr int N_DiagnosticMemoryDestination            = 98;
static constexpr int A_DiagnosticMemoryDestination_dtcStatusAvailabilityMask  = 2;
static constexpr int A_DiagnosticMemoryDestination_kind       = 1;
static constexpr int A_DiagnosticMemoryDestination_shortName  = 0;
static constexpr int A_DiagnosticMemoryDestination_userDefined_memoryId  = 4;
static constexpr int R_DiagnosticMemoryDestination_clearDtcLimitation  = 3;
static constexpr int R_DiagnosticMemoryDestination_typeOfFreezeFrameRecordNumeration  = 2;
// 
static constexpr int N_DiagnosticMonitorPortIref              = 136;
static constexpr int A_DiagnosticMonitorPortIref_processDesignShortName  = 0;
static constexpr int A_DiagnosticMonitorPortIref_targetPortContextKey  = 1;
static constexpr int R_DiagnosticMonitorPortIref_processDesign  = 0;
// 
static constexpr int N_DiagnosticMonitorPortMapping           = 135;
static constexpr int A_DiagnosticMonitorPortMapping_shortName  = 0;
static constexpr int R_DiagnosticMonitorPortMapping_diagnosticEvent  = 0;
static constexpr int R_DiagnosticMonitorPortMapping_iref      = 1;
// 
static constexpr int N_DiagnosticOperationCyclePortIref       = 43;
static constexpr int A_DiagnosticOperationCyclePortIref_processDesignShortName  = 0;
static constexpr int A_DiagnosticOperationCyclePortIref_targetPortContextKey  = 1;
static constexpr int R_DiagnosticOperationCyclePortIref_processDesign  = 0;
// 
static constexpr int N_DiagnosticOperationCyclePortMapping    = 42;
static constexpr int A_DiagnosticOperationCyclePortMapping_shortName  = 0;
static constexpr int R_DiagnosticOperationCyclePortMapping_iref  = 1;
static constexpr int R_DiagnosticOperationCyclePortMapping_operationCycle  = 0;
// 
static constexpr int N_DiagnosticOperationCycle               = 41;
static constexpr int A_DiagnosticOperationCycle_cycleStatusStorage  = 2;
static constexpr int A_DiagnosticOperationCycle_shortName     = 0;
// 
static constexpr int N_DiagnosticRoutineSubfunctionRequest    = 117;
static constexpr int A_DiagnosticRoutineSubfunctionRequest_bitOffset  = 0;
static constexpr int R_DiagnosticRoutineSubfunctionRequest_dataElement  = 0;
// 
static constexpr int N_DiagnosticRoutineSubfunctionResponse   = 118;
static constexpr int A_DiagnosticRoutineSubfunctionResponse_bitOffset  = 0;
static constexpr int R_DiagnosticRoutineSubfunctionResponse_dataElement  = 0;
// 
static constexpr int N_DiagnosticRoutineSubfunction           = 116;
static constexpr int A_DiagnosticRoutineSubfunction_kind      = 0;
static constexpr int A_DiagnosticRoutineSubfunction_role      = 1;
static constexpr int C_DiagnosticRoutineSubfunction_request   = 0; // childNode[DiagnosticRoutineSubfunctionRequest]
static constexpr int C_DiagnosticRoutineSubfunction_response  = 1; // childNode[DiagnosticRoutineSubfunctionResponse]
// 
static constexpr int N_DiagnosticRoutine                      = 115;
static constexpr int A_DiagnosticRoutine_id                   = 1;
static constexpr int A_DiagnosticRoutine_shortName            = 0;
static constexpr int C_DiagnosticRoutine_subfunction          = 0; // childNode[DiagnosticRoutineSubfunction]
// 
static constexpr int N_DiagnosticSecurityLevelPortIref        = 125;
static constexpr int A_DiagnosticSecurityLevelPortIref_processDesignShortName  = 0;
static constexpr int A_DiagnosticSecurityLevelPortIref_targetPortContextKey  = 1;
static constexpr int R_DiagnosticSecurityLevelPortIref_processDesign  = 0;
// 
static constexpr int N_DiagnosticSecurityLevelPortMapping     = 124;
static constexpr int A_DiagnosticSecurityLevelPortMapping_shortName  = 0;
static constexpr int R_DiagnosticSecurityLevelPortMapping_iref  = 1;
static constexpr int R_DiagnosticSecurityLevelPortMapping_securityLevel  = 0;
// 
static constexpr int N_DiagnosticSecurityLevel                = 103;
static constexpr int A_DiagnosticSecurityLevel_keySize        = 1;
static constexpr int A_DiagnosticSecurityLevel_numFailedSecurityAccess  = 2;
static constexpr int A_DiagnosticSecurityLevel_securityDelayTime  = 3;
static constexpr int A_DiagnosticSecurityLevel_seedSize       = 4;
static constexpr int A_DiagnosticSecurityLevel_shortName      = 0;
// 
static constexpr int N_DiagnosticServiceClass                 = 96;
static constexpr int A_DiagnosticServiceClass_kind            = 1;
static constexpr int A_DiagnosticServiceClass_readData_maxDidToRead  = 2;
static constexpr int A_DiagnosticServiceClass_shortName       = 0;
// 
static constexpr int N_DiagnosticServiceGenericIref           = 129;
static constexpr int A_DiagnosticServiceGenericIref_processDesignShortName  = 0;
static constexpr int A_DiagnosticServiceGenericIref_targetPortContextKey  = 1;
static constexpr int R_DiagnosticServiceGenericIref_processDesign  = 0;
// 
static constexpr int N_DiagnosticServiceGenericMapping        = 128;
static constexpr int A_DiagnosticServiceGenericMapping_shortName  = 0;
static constexpr int R_DiagnosticServiceGenericMapping_iref   = 0;
static constexpr int R_DiagnosticServiceGenericMapping_serviceInstance  = 1;
// 
static constexpr int N_DiagnosticServiceInstance              = 97;
static constexpr int A_DiagnosticServiceInstance_category     = 2;
static constexpr int A_DiagnosticServiceInstance_kind         = 1;
static constexpr int A_DiagnosticServiceInstance_securityAccess_requestSeedId  = 3;
static constexpr int A_DiagnosticServiceInstance_shortName    = 0;
static constexpr int R_DiagnosticServiceInstance_accessPermission  = 0;
static constexpr int R_DiagnosticServiceInstance_clearDiagnosticInformationClass  = 9;
static constexpr int R_DiagnosticServiceInstance_comControlClass  = 15;
static constexpr int R_DiagnosticServiceInstance_dataIdentifier  = 12;
static constexpr int R_DiagnosticServiceInstance_dataTransferClass  = 7;
static constexpr int R_DiagnosticServiceInstance_diagnosticSession  = 5;
static constexpr int R_DiagnosticServiceInstance_dtcSettingClass  = 1;
static constexpr int R_DiagnosticServiceInstance_ecuResetClass  = 8;
static constexpr int R_DiagnosticServiceInstance_readClass    = 13;
static constexpr int R_DiagnosticServiceInstance_readDTCInformationClass  = 6;
static constexpr int R_DiagnosticServiceInstance_requestDownloadClass  = 11;
static constexpr int R_DiagnosticServiceInstance_routine      = 17;
static constexpr int R_DiagnosticServiceInstance_routineControlClass  = 16;
static constexpr int R_DiagnosticServiceInstance_securityAccessClass  = 2;
static constexpr int R_DiagnosticServiceInstance_securityLevel  = 3;
static constexpr int R_DiagnosticServiceInstance_sessionControlClass  = 4;
static constexpr int R_DiagnosticServiceInstance_transferExitClass  = 10;
static constexpr int R_DiagnosticServiceInstance_writeClass   = 14;
// 
static constexpr int N_DiagnosticSession                      = 102;
static constexpr int A_DiagnosticSession_id                   = 1;
static constexpr int A_DiagnosticSession_p2ServerMax          = 2;
static constexpr int A_DiagnosticSession_p2StarServerMax      = 3;
static constexpr int A_DiagnosticSession_shortName            = 0;
static constexpr int A_DiagnosticSession_vrte_p2ServerMaxThreshold  = 4;
static constexpr int A_DiagnosticSession_vrte_p2StarServerMaxThreshold  = 5;
// 
static constexpr int N_DiagnosticTroubleCodeRefExtendedDataRecord  = 93;
static constexpr int R_DiagnosticTroubleCodeRefExtendedDataRecord_extendedDataRecord  = 0;
// 
static constexpr int N_DiagnosticTroubleCodeRefFreezeFrame    = 94;
static constexpr int R_DiagnosticTroubleCodeRefFreezeFrame_freezeFrame  = 0;
// 
static constexpr int N_DiagnosticTroubleCodeRefMemoryDestination  = 99;
static constexpr int R_DiagnosticTroubleCodeRefMemoryDestination_memoryDestination  = 0;
// 
static constexpr int N_DiagnosticTroubleCode                  = 56;
static constexpr int A_DiagnosticTroubleCode_aging_shortName  = 8;
static constexpr int A_DiagnosticTroubleCode_aging_threshold  = 9;
static constexpr int A_DiagnosticTroubleCode_kind             = 1;
static constexpr int A_DiagnosticTroubleCode_shortName        = 0;
static constexpr int A_DiagnosticTroubleCode_uds_agingAllowed  = 4;
static constexpr int A_DiagnosticTroubleCode_uds_maxNumberFreezeFrameRecords  = 6;
static constexpr int A_DiagnosticTroubleCode_uds_priority     = 7;
static constexpr int A_DiagnosticTroubleCode_uds_udsDtcValue  = 3;
static constexpr int R_DiagnosticTroubleCode_uds_severity     = 0;
static constexpr int R_DiagnosticTroubleCode_uds_significance  = 2;
static constexpr int R_DiagnosticTroubleCode_uds_snapshotRecordContent  = 3;
static constexpr int C_DiagnosticTroubleCode_refExtendedDataRecord  = 1; // childNode[DiagnosticTroubleCodeRefExtendedDataRecord]
static constexpr int C_DiagnosticTroubleCode_refFreezeFrame   = 2; // childNode[DiagnosticTroubleCodeRefFreezeFrame]
static constexpr int C_DiagnosticTroubleCode_refMemoryDestination  = 0; // childNode[DiagnosticTroubleCodeRefMemoryDestination]
// 
static constexpr int N_ENUMS                                  = 2;
static constexpr int C_ENUMS_ENUM                             = 0; // childNode[ENUM]
// 
static constexpr int N_ENUM                                   = 3;
static constexpr int C_ENUM_LITERAL                           = 0; // childNode[LITERAL]
// 
static constexpr int N_IREFS                                  = 5;
static constexpr int C_IREFS_DiagnosticDataIdentifierPortIref  = 4; // childNode[DiagnosticDataIdentifierPortIref]
static constexpr int C_IREFS_DiagnosticEventPortIref          = 0; // childNode[DiagnosticEventPortIref]
static constexpr int C_IREFS_DiagnosticMonitorPortIref        = 8; // childNode[DiagnosticMonitorPortIref]
static constexpr int C_IREFS_DiagnosticOperationCyclePortIref  = 1; // childNode[DiagnosticOperationCyclePortIref]
static constexpr int C_IREFS_DiagnosticSecurityLevelPortIref  = 6; // childNode[DiagnosticSecurityLevelPortIref]
static constexpr int C_IREFS_DiagnosticServiceGenericIref     = 3; // childNode[DiagnosticServiceGenericIref]
// 
static constexpr int N_LITERAL                                = 4;
static constexpr int A_LITERAL_mappedValue                    = 1;
static constexpr int A_LITERAL_value                          = 0;
// 
static constexpr int N_ProcessDesign                          = 9;
static constexpr int A_ProcessDesign_processShortName         = 1;
static constexpr int A_ProcessDesign_shortName                = 0;
// 
static constexpr int N_ROOT                                   = 0;
static constexpr int C_ROOT_AdaptivePPort                     = 21; // childNode[AdaptivePPort]
static constexpr int C_ROOT_AdaptiveRPort                     = 22; // childNode[AdaptiveRPort]
static constexpr int C_ROOT_DiagnosticAccessPermission        = 34; // childNode[DiagnosticAccessPermission]
static constexpr int C_ROOT_DiagnosticCondition               = 10; // childNode[DiagnosticCondition]
static constexpr int C_ROOT_DiagnosticConditionGroup          = 12; // childNode[DiagnosticConditionGroup]
static constexpr int C_ROOT_DiagnosticContributionSet         = 30; // childNode[DiagnosticContributionSet]
static constexpr int C_ROOT_DiagnosticDataElement             = 37; // childNode[DiagnosticDataElement]
static constexpr int C_ROOT_DiagnosticDataIdentifier          = 18; // childNode[DiagnosticDataIdentifier]
static constexpr int C_ROOT_DiagnosticDataIdentifierSet       = 19; // childNode[DiagnosticDataIdentifierSet]
static constexpr int C_ROOT_DiagnosticDataPortMapping         = 36; // childNode[DiagnosticDataPortMapping]
static constexpr int C_ROOT_DiagnosticEvent                   = 5; // childNode[DiagnosticEvent]
static constexpr int C_ROOT_DiagnosticEventPortMapping        = 7; // childNode[DiagnosticEventPortMapping]
static constexpr int C_ROOT_DiagnosticEventToDebounceAlgorithmMapping  = 38; // childNode[DiagnosticEventToDebounceAlgorithmMapping]
static constexpr int C_ROOT_DiagnosticEventToEnableConditionGroupMapping  = 13; // childNode[DiagnosticEventToEnableConditionGroupMapping]
static constexpr int C_ROOT_DiagnosticEventToOperationCycleMapping  = 6; // childNode[DiagnosticEventToOperationCycleMapping]
static constexpr int C_ROOT_DiagnosticEventToTroubleCodeUdsMapping  = 17; // childNode[DiagnosticEventToTroubleCodeUdsMapping]
static constexpr int C_ROOT_DiagnosticExtendedDataRecord      = 20; // childNode[DiagnosticExtendedDataRecord]
static constexpr int C_ROOT_DiagnosticFreezeFrame             = 26; // childNode[DiagnosticFreezeFrame]
static constexpr int C_ROOT_DiagnosticMemoryDestination       = 29; // childNode[DiagnosticMemoryDestination]
static constexpr int C_ROOT_DiagnosticMonitorPortMapping      = 41; // childNode[DiagnosticMonitorPortMapping]
static constexpr int C_ROOT_DiagnosticOperationCycle          = 8; // childNode[DiagnosticOperationCycle]
static constexpr int C_ROOT_DiagnosticOperationCyclePortMapping  = 9; // childNode[DiagnosticOperationCyclePortMapping]
static constexpr int C_ROOT_DiagnosticRoutine                 = 35; // childNode[DiagnosticRoutine]
static constexpr int C_ROOT_DiagnosticSecurityLevel           = 32; // childNode[DiagnosticSecurityLevel]
static constexpr int C_ROOT_DiagnosticSecurityLevelPortMapping  = 4; // childNode[DiagnosticSecurityLevelPortMapping]
static constexpr int C_ROOT_DiagnosticServiceClass            = 27; // childNode[DiagnosticServiceClass]
static constexpr int C_ROOT_DiagnosticServiceGenericMapping   = 25; // childNode[DiagnosticServiceGenericMapping]
static constexpr int C_ROOT_DiagnosticServiceInstance         = 28; // childNode[DiagnosticServiceInstance]
static constexpr int C_ROOT_DiagnosticSession                 = 31; // childNode[DiagnosticSession]
static constexpr int C_ROOT_DiagnosticTroubleCode             = 14; // childNode[DiagnosticTroubleCode]
static constexpr int C_ROOT_ENUMS                             = 0; // childNode[ENUMS]
static constexpr int C_ROOT_IREFS                             = 1; // childNode[IREFS]
static constexpr int C_ROOT_ProcessDesign                     = 3; // childNode[ProcessDesign]
// 
};
// =========================================================================================================================
// end generated constexpr
// =========================================================================================================================
#endif // ECUCFG_DIA_4_1_METADATA_VARIANT
