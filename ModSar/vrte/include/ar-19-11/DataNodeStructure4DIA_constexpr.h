#ifndef ECUCFG_DIA_2_1_METADATA_VARIANT
// =========================================================================================================================
// generated for DIA at 2020-10-29 09:04:20
//
// begin generated constexpr:
// =========================================================================================================================
#define ECUCFG_DIA_2_1_METADATA_VARIANT "THIS IS THE INCLUDE-GUARD"
#ifndef ECUCFG_DIA_METADATA_NAME
#define ECUCFG_DIA_METADATA_NAME "DIA"
#endif
//
class DIA_constexpr
{
public:
    static constexpr int majorVersion = 2; // approved
    static constexpr int minorVersion = 1;
    //
    static constexpr int N_AdaptiveIB = 80;
    static constexpr int A_AdaptiveIB_shortName = 0;
    static constexpr int C_AdaptiveIB_serviceDependency = 0; // childNode[SwcServiceDependency]
    //
    static constexpr int N_AdaptivePPort = 71;
    static constexpr int A_AdaptivePPort_shortName = 0;
    //
    static constexpr int N_AdaptivePRPort = 77;
    static constexpr int A_AdaptivePRPort_shortName = 0;
    //
    static constexpr int N_AdaptiveRPort = 74;
    static constexpr int A_AdaptiveRPort_shortName = 0;
    //
    static constexpr int N_AdaptiveSWC = 70;
    static constexpr int A_AdaptiveSWC_shortName = 0;
    static constexpr int C_AdaptiveSWC_IB = 3;     // childNode[AdaptiveIB]
    static constexpr int C_AdaptiveSWC_pPort = 0;  // childNode[AdaptivePPort]
    static constexpr int C_AdaptiveSWC_prPort = 2; // childNode[AdaptivePRPort]
    static constexpr int C_AdaptiveSWC_rPort = 1;  // childNode[AdaptiveRPort]
    //
    static constexpr int N_DiagnosticAccessPermissionSecurityLevel = 112;             // ref. with mul=*
    static constexpr int R_DiagnosticAccessPermissionSecurityLevel_securityLevel = 0; // targetNode[DiagnosticSecurityLevel] ref. with mul=*
    //
    static constexpr int N_DiagnosticAccessPermissionSession = 111;                 // ref. with mul=*
    static constexpr int R_DiagnosticAccessPermissionSession_diagnosticSession = 0; // targetNode[DiagnosticSession] ref. with mul=*
    //
    static constexpr int N_DiagnosticAccessPermission = 110;
    static constexpr int A_DiagnosticAccessPermission_shortName = 0;
    static constexpr int R_DiagnosticAccessPermission_environmentalCondition = 0; // targetNode[DiagnosticEnvironmentalCondition]
    static constexpr int C_DiagnosticAccessPermission_diagnosticSessions = 0;     // childNode[DiagnosticAccessPermissionSession] ref. with mul=*
    static constexpr int C_DiagnosticAccessPermission_securityLevels = 1;         // childNode[DiagnosticAccessPermissionSecurityLevel] ref. with mul=*
    //
    static constexpr int N_DiagnosticConditionGroupRefClear = 52;               // ref. with mul=*
    static constexpr int R_DiagnosticConditionGroupRefClear_clearCondition = 0; // targetNode[DiagnosticCondition] ref. with mul=*
    //
    static constexpr int N_DiagnosticConditionGroupRefEnable = 53;                // variant ref. with mul=*
    static constexpr int R_DiagnosticConditionGroupRefEnable_enableCondition = 0; // targetNode[DiagnosticCondition] variant ref. with mul=*
    //
    static constexpr int N_DiagnosticConditionGroupRefStorage = 54;                 // variant ref. with mul=*
    static constexpr int R_DiagnosticConditionGroupRefStorage_storageCondition = 0; // targetNode[DiagnosticCondition] variant ref. with mul=*
    //
    static constexpr int N_DiagnosticConditionGroup = 51;     // specializations are DiagnosticClearConditionGroup, DiagnosticEnableConditionGroup, DiagnosticStorageConditionGroup
    static constexpr int A_DiagnosticConditionGroup_kind = 1; // specializations are DiagnosticClearConditionGroup, DiagnosticEnableConditionGroup, DiagnosticStorageConditionGroup
    static constexpr int A_DiagnosticConditionGroup_shortName = 0;
    static constexpr int C_DiagnosticConditionGroup_refClear = 0;   // childNode[DiagnosticConditionGroupRefClear] ref. with mul=*
    static constexpr int C_DiagnosticConditionGroup_refEnable = 1;  // childNode[DiagnosticConditionGroupRefEnable] variant ref. with mul=*
    static constexpr int C_DiagnosticConditionGroup_refStorage = 2; // childNode[DiagnosticConditionGroupRefStorage] variant ref. with mul=*
    //
    static constexpr int N_DiagnosticCondition = 46;          // specializations are DiagnosticClearCondition DiagnosticEnableCondition, DiagnosticStorageCondition
    static constexpr int A_DiagnosticCondition_initValue = 2; // type=boolean value=0|1|true|false
    static constexpr int A_DiagnosticCondition_kind = 1;      // specializations are DiagnosticClearCondition DiagnosticEnableCondition, DiagnosticStorageCondition
    static constexpr int A_DiagnosticCondition_shortName = 0;
    //
    static constexpr int N_DiagnosticConnectedIndicator = 36;
    static constexpr int A_DiagnosticConnectedIndicator_indicator_shortName = 0;
    static constexpr int R_DiagnosticConnectedIndicator_behavior = 1;       // targetNode[LITERAL]
    static constexpr int R_DiagnosticConnectedIndicator_healingCycle = 0;   // targetNode[DiagnosticOperationCycle]
    static constexpr int R_DiagnosticConnectedIndicator_indicator_type = 2; // targetNode[LITERAL]
    //
    static constexpr int N_DiagnosticContributionSet = 100;
    static constexpr int A_DiagnosticContributionSet_prop_maxNumberOfRequestCorrectlyReceivedResponsePending = 1; // type=uint
    static constexpr int A_DiagnosticContributionSet_prop_securityDelayTimeOnBoot = 2;                            // type=double dimension=s
    static constexpr int A_DiagnosticContributionSet_shortName = 0;
    static constexpr int R_DiagnosticContributionSet_prop_clearDtcLimitation = 0; // targetNode[LITERAL]
    static constexpr int R_DiagnosticContributionSet_prop_typeOfDtcSupported = 1; // targetNode[LITERAL]
    static constexpr int C_DiagnosticContributionSet_debounceAlgorithmProps = 0;  // childNode[DiagnosticDebounceAlgorithmProps]
    //
    static constexpr int N_DiagnosticDataElement2 = 119; // item is sliced off since aggregated multiply
    static constexpr int A_DiagnosticDataElement2_basetype_shortName = 12;
    static constexpr int A_DiagnosticDataElement2_basetype_size = 13;      // type=uint
    static constexpr int A_DiagnosticDataElement2_maxNumberOfElements = 1; // type=uint
    static constexpr int A_DiagnosticDataElement2_scalingInfoSize = 2;     // type=uint
    static constexpr int A_DiagnosticDataElement2_shortName = 0;
    static constexpr int A_DiagnosticDataElement2_swDataDefProps_additionalNativeTypeQualifier = 3;
    static constexpr int A_DiagnosticDataElement2_swDataDefProps_displayFormat = 4;
    static constexpr int A_DiagnosticDataElement2_swDataDefProps_stepSize = 5; // type=float
    static constexpr int A_DiagnosticDataElement2_swDataDefProps_swAlignment = 6;
    static constexpr int A_DiagnosticDataElement2_swDataDefProps_swIntendedResolution = 7; // type=numerical (allows different formats such as Decimal, Octal, / Hexadecimal, Float)
    static constexpr int A_DiagnosticDataElement2_swDataDefProps_swInterpolationMethod = 8;
    static constexpr int A_DiagnosticDataElement2_swDataDefProps_swIsVirtual = 9;           // type=boolean value=0|1|true|false
    static constexpr int A_DiagnosticDataElement2_swDataDefProps_swValueBlockSize = 10;     // type=numerical (allows different formats such as Decimal, Octal, / Hexadecimal, Float)
    static constexpr int A_DiagnosticDataElement2_swDataDefProps_swValueBlockSizeMult = 11; // array type attribute not yet supported
    static constexpr int R_DiagnosticDataElement2_arraySizeSemantics = 0;                   // targetNode[LITERAL]
    static constexpr int R_DiagnosticDataElement2_swDataDefProps_displayPresentation = 1;   // targetNode[LITERAL]
    static constexpr int R_DiagnosticDataElement2_swDataDefProps_swCalibrationAccess = 2;   // targetNode[LITERAL]
    static constexpr int R_DiagnosticDataElement2_swDataDefProps_swImplPolicy = 3;          // targetNode[LITERAL]
    //
    static constexpr int N_DiagnosticDataElement = 65; // item is sliced off since aggregated multiply
    static constexpr int A_DiagnosticDataElement_basetype_shortName = 12;
    static constexpr int A_DiagnosticDataElement_basetype_size = 13;      // type=uint
    static constexpr int A_DiagnosticDataElement_maxNumberOfElements = 1; // type=uint
    static constexpr int A_DiagnosticDataElement_scalingInfoSize = 2;     // type=uint
    static constexpr int A_DiagnosticDataElement_shortName = 0;
    static constexpr int A_DiagnosticDataElement_swDataDefProps_additionalNativeTypeQualifier = 3;
    static constexpr int A_DiagnosticDataElement_swDataDefProps_displayFormat = 4;
    static constexpr int A_DiagnosticDataElement_swDataDefProps_stepSize = 5; // type=float
    static constexpr int A_DiagnosticDataElement_swDataDefProps_swAlignment = 6;
    static constexpr int A_DiagnosticDataElement_swDataDefProps_swIntendedResolution = 7; // type=numerical (allows different formats such as Decimal, Octal, / Hexadecimal, Float)
    static constexpr int A_DiagnosticDataElement_swDataDefProps_swInterpolationMethod = 8;
    static constexpr int A_DiagnosticDataElement_swDataDefProps_swIsVirtual = 9;           // type=boolean value=0|1|true|false
    static constexpr int A_DiagnosticDataElement_swDataDefProps_swValueBlockSize = 10;     // type=numerical (allows different formats such as Decimal, Octal, / Hexadecimal, Float)
    static constexpr int A_DiagnosticDataElement_swDataDefProps_swValueBlockSizeMult = 11; // array type attribute not yet supported
    static constexpr int R_DiagnosticDataElement_arraySizeSemantics = 0;                   // targetNode[LITERAL]
    static constexpr int R_DiagnosticDataElement_swDataDefProps_displayPresentation = 1;   // targetNode[LITERAL]
    static constexpr int R_DiagnosticDataElement_swDataDefProps_swCalibrationAccess = 2;   // targetNode[LITERAL]
    static constexpr int R_DiagnosticDataElement_swDataDefProps_swImplPolicy = 3;          // targetNode[LITERAL]
    //
    static constexpr int N_DiagnosticDataIdentifierParameter = 62;
    static constexpr int A_DiagnosticDataIdentifierParameter_bitOffset = 0;   // type=uint
    static constexpr int R_DiagnosticDataIdentifierParameter_dataElement = 0; // targetNode[DiagnosticDataElement] item is sliced off since aggregated multiply
    //
    static constexpr int N_DiagnosticDataIdentifierSetRefs = 64;               // ref. with mul=*
    static constexpr int R_DiagnosticDataIdentifierSetRefs_dataIdentifier = 0; // targetNode[DiagnosticDataIdentifier] ref. with mul=*
    //
    static constexpr int N_DiagnosticDataIdentifierSet = 63;
    static constexpr int A_DiagnosticDataIdentifierSet_shortName = 0;
    static constexpr int C_DiagnosticDataIdentifierSet_refDid = 0; // childNode[DiagnosticDataIdentifierSetRefs] ref. with mul=*
    //
    static constexpr int N_DiagnosticDataIdentifier = 61;              // specializations are DiagnosticDataIdentifier, DiagnosticDynamicDataIdentifier
    static constexpr int A_DiagnosticDataIdentifier_didSize = 3;       // type=uint
    static constexpr int A_DiagnosticDataIdentifier_id = 1;            // type=uint
    static constexpr int A_DiagnosticDataIdentifier_kind = 2;          // specializations are DiagnosticDataIdentifier, DiagnosticDynamicDataIdentifier
    static constexpr int A_DiagnosticDataIdentifier_representsVin = 4; // type=boolean value=0|1|true|false
    static constexpr int A_DiagnosticDataIdentifier_shortName = 0;
    static constexpr int C_DiagnosticDataIdentifier_dataElement = 0; // childNode[DiagnosticDataIdentifierParameter]
    //
    static constexpr int N_DiagnosticDebounceAlgorithmProps = 106;
    static constexpr int A_DiagnosticDebounceAlgorithmProps_algo_counterFailedThreshold = 2; // type=int
    static constexpr int A_DiagnosticDebounceAlgorithmProps_algo_counterPassedThreshold = 3; // type=int
    static constexpr int A_DiagnosticDebounceAlgorithmProps_algo_kind = 1;
    static constexpr int A_DiagnosticDebounceAlgorithmProps_algo_shortName = 0;
    //
    static constexpr int N_DiagnosticEnableConditionPortIrefOWNERS = 49;
    static constexpr int R_DiagnosticEnableConditionPortIrefOWNERS_irefOwner = 0; // targetNode[DiagnosticEnableConditionPortMapping]
    //
    static constexpr int N_DiagnosticEnableConditionPortIref = 48;
    static constexpr int A_DiagnosticEnableConditionPortIref_executable = 0;
    static constexpr int A_DiagnosticEnableConditionPortIref_processDesignShortName = 2;
    static constexpr int A_DiagnosticEnableConditionPortIref_rootCPT = 1;
    static constexpr int A_DiagnosticEnableConditionPortIref_targetPortContextKey = 3;
    static constexpr int A_DiagnosticEnableConditionPortIref_targetPortShortName = 4;
    static constexpr int R_DiagnosticEnableConditionPortIref_processDesign = 1;              // targetNode[ProcessDesign]
    static constexpr int R_DiagnosticEnableConditionPortIref_targetSwcServiceDependency = 0; // targetNode[SwcServiceDependency]
    static constexpr int C_DiagnosticEnableConditionPortIref_OWNERS = 0;                     // childNode[DiagnosticEnableConditionPortIrefOWNERS]
    //
    static constexpr int N_DiagnosticEnableConditionPortMapping = 47; // filtered by existence of referenced processDesign
    static constexpr int A_DiagnosticEnableConditionPortMapping_shortName = 0;
    static constexpr int R_DiagnosticEnableConditionPortMapping_enableCondition = 0; // targetNode[DiagnosticCondition]
    static constexpr int R_DiagnosticEnableConditionPortMapping_iref = 2;            // targetNode[DiagnosticEnableConditionPortIref] IREF: DiagnosticEnableConditionPortIref
    static constexpr int R_DiagnosticEnableConditionPortMapping_processDesign = 1;   // targetNode[ProcessDesign]
    //
    static constexpr int N_DiagnosticEnvironmentalCondition = 104;
    static constexpr int A_DiagnosticEnvironmentalCondition_shortName = 0;
    //
    static constexpr int N_DiagnosticEventPortIrefOWNERS = 34;
    static constexpr int R_DiagnosticEventPortIrefOWNERS_irefOwner = 0; // targetNode[DiagnosticEventPortMapping]
    //
    static constexpr int N_DiagnosticEventPortIref = 33;
    static constexpr int A_DiagnosticEventPortIref_executable = 0;
    static constexpr int A_DiagnosticEventPortIref_processDesignShortName = 2;
    static constexpr int A_DiagnosticEventPortIref_rootCPT = 1;
    static constexpr int A_DiagnosticEventPortIref_targetPortContextKey = 3;
    static constexpr int A_DiagnosticEventPortIref_targetPortShortName = 4;
    static constexpr int R_DiagnosticEventPortIref_processDesign = 1;              // targetNode[ProcessDesign]
    static constexpr int R_DiagnosticEventPortIref_targetSwcServiceDependency = 0; // targetNode[SwcServiceDependency]
    static constexpr int C_DiagnosticEventPortIref_OWNERS = 0;                     // childNode[DiagnosticEventPortIrefOWNERS]
    //
    static constexpr int N_DiagnosticEventPortMapping = 32; // filtered by existence of referenced processDesign
    static constexpr int A_DiagnosticEventPortMapping_shortName = 0;
    static constexpr int R_DiagnosticEventPortMapping_diagnosticEvent = 0; // targetNode[DiagnosticEvent]
    static constexpr int R_DiagnosticEventPortMapping_iref = 2;            // targetNode[DiagnosticEventPortIref] IREF: DiagnosticEventPortIref
    static constexpr int R_DiagnosticEventPortMapping_processDesign = 1;   // targetNode[ProcessDesign]
    //
    static constexpr int N_DiagnosticEventToDebounceAlgorithmMapping = 107;
    static constexpr int A_DiagnosticEventToDebounceAlgorithmMapping_shortName = 0;
    static constexpr int R_DiagnosticEventToDebounceAlgorithmMapping_debounceAlgorithm = 0; // targetNode[DiagnosticDebounceAlgorithmProps]
    static constexpr int R_DiagnosticEventToDebounceAlgorithmMapping_diagnosticEvent = 1;   // targetNode[DiagnosticEvent]
    //
    static constexpr int N_DiagnosticEventToEnableConditionGroupMapping = 37;
    static constexpr int A_DiagnosticEventToEnableConditionGroupMapping_shortName = 0;
    static constexpr int R_DiagnosticEventToEnableConditionGroupMapping_diagnosticEvent = 0;      // targetNode[DiagnosticEvent]
    static constexpr int R_DiagnosticEventToEnableConditionGroupMapping_enableConditionGroup = 1; // targetNode[DiagnosticConditionGroup]
    //
    static constexpr int N_DiagnosticEventToOperationCycleMapping = 35;
    static constexpr int A_DiagnosticEventToOperationCycleMapping_shortName = 0;
    static constexpr int R_DiagnosticEventToOperationCycleMapping_diagnosticEvent = 0; // targetNode[DiagnosticEvent]
    static constexpr int R_DiagnosticEventToOperationCycleMapping_operationCycle = 1;  // targetNode[DiagnosticOperationCycle]
    //
    static constexpr int N_DiagnosticEventToTroubleCodeUdsMapping = 38;
    static constexpr int A_DiagnosticEventToTroubleCodeUdsMapping_shortName = 0;
    static constexpr int R_DiagnosticEventToTroubleCodeUdsMapping_diagnosticEvent = 0; // targetNode[DiagnosticEvent]
    static constexpr int R_DiagnosticEventToTroubleCodeUdsMapping_troubleCodeUds = 1;  // targetNode[DiagnosticTroubleCode]
    //
    static constexpr int N_DiagnosticEvent = 31;
    static constexpr int A_DiagnosticEvent_eventFailureCycleCounterThreshold = 4; // type=uint
    static constexpr int A_DiagnosticEvent_prestorageFreezeFrame = 1;             // type=boolean value=0|1|true|false
    static constexpr int A_DiagnosticEvent_prestoredFreezeframeStoredInNvm = 2;   // type=boolean value=0|1|true|false
    static constexpr int A_DiagnosticEvent_recoverableInSameOperationCycle = 3;   // type=boolean value=0|1|true|false
    static constexpr int A_DiagnosticEvent_shortName = 0;
    static constexpr int R_DiagnosticEvent_clearEventBehavior = 0; // targetNode[LITERAL]
    static constexpr int C_DiagnosticEvent_connectedIndicator = 0; // childNode[DiagnosticConnectedIndicator]
    //
    static constexpr int N_DiagnosticExtendedDataRecordParameter = 67;
    static constexpr int A_DiagnosticExtendedDataRecordParameter_bitOffset = 0;   // type=uint
    static constexpr int R_DiagnosticExtendedDataRecordParameter_dataElement = 0; // targetNode[DiagnosticDataElement] item is sliced off since aggregated multiply
    //
    static constexpr int N_DiagnosticExtendedDataRecord = 66;
    static constexpr int A_DiagnosticExtendedDataRecord_customTrigger = 1;
    static constexpr int A_DiagnosticExtendedDataRecord_recordNumber = 2; // type=uint
    static constexpr int A_DiagnosticExtendedDataRecord_shortName = 0;
    static constexpr int A_DiagnosticExtendedDataRecord_update = 3;        // type=boolean value=0|1|true|false
    static constexpr int R_DiagnosticExtendedDataRecord_trigger = 0;       // targetNode[LITERAL]
    static constexpr int C_DiagnosticExtendedDataRecord_recordElement = 0; // childNode[DiagnosticExtendedDataRecordParameter]
    //
    static constexpr int N_DiagnosticFreezeFrame = 91;
    static constexpr int A_DiagnosticFreezeFrame_customTrigger = 1;
    static constexpr int A_DiagnosticFreezeFrame_recordNumber = 3; // type=uint
    static constexpr int A_DiagnosticFreezeFrame_shortName = 0;
    static constexpr int A_DiagnosticFreezeFrame_update = 2;  // type=boolean value=0|1|true|false
    static constexpr int R_DiagnosticFreezeFrame_trigger = 0; // targetNode[LITERAL]
    //
    static constexpr int N_DiagnosticGenericUdsPortIrefOWNERS = 130;
    static constexpr int R_DiagnosticGenericUdsPortIrefOWNERS_irefOwner = 0; // targetNode[DiagnosticGenericUdsPortMapping]
    //
    static constexpr int N_DiagnosticGenericUdsPortIref = 129;
    static constexpr int A_DiagnosticGenericUdsPortIref_executable = 0;
    static constexpr int A_DiagnosticGenericUdsPortIref_processDesignShortName = 2;
    static constexpr int A_DiagnosticGenericUdsPortIref_rootCPT = 1;
    static constexpr int A_DiagnosticGenericUdsPortIref_targetPortContextKey = 3;
    static constexpr int A_DiagnosticGenericUdsPortIref_targetPortShortName = 4;
    static constexpr int R_DiagnosticGenericUdsPortIref_processDesign = 1;              // targetNode[ProcessDesign]
    static constexpr int R_DiagnosticGenericUdsPortIref_targetSwcServiceDependency = 0; // targetNode[SwcServiceDependency]
    static constexpr int C_DiagnosticGenericUdsPortIref_OWNERS = 0;                     // childNode[DiagnosticGenericUdsPortIrefOWNERS]
    //
    static constexpr int N_DiagnosticGenericUdsPortMappingServiceInstance = 131;               // ref. with mul=*
    static constexpr int R_DiagnosticGenericUdsPortMappingServiceInstance_serviceInstance = 0; // targetNode[DiagnosticServiceInstance] ref. with mul=*
    //
    static constexpr int N_DiagnosticGenericUdsPortMapping = 128; // filtered by existence of referenced processDesign
    static constexpr int A_DiagnosticGenericUdsPortMapping_shortName = 0;
    static constexpr int R_DiagnosticGenericUdsPortMapping_iref = 1;             // targetNode[DiagnosticGenericUdsPortIref] IREF: DiagnosticGenericUdsPortIref
    static constexpr int R_DiagnosticGenericUdsPortMapping_processDesign = 0;    // targetNode[ProcessDesign]
    static constexpr int C_DiagnosticGenericUdsPortMapping_serviceInstances = 0; // childNode[DiagnosticGenericUdsPortMappingServiceInstance] ref. with mul=*
    //
    static constexpr int N_DiagnosticMemoryDestinationPortIrefOWNERS = 135;
    static constexpr int R_DiagnosticMemoryDestinationPortIrefOWNERS_irefOwner = 0; // targetNode[DiagnosticMemoryDestinationPortMapping]
    //
    static constexpr int N_DiagnosticMemoryDestinationPortIref = 134;
    static constexpr int A_DiagnosticMemoryDestinationPortIref_executable = 0;
    static constexpr int A_DiagnosticMemoryDestinationPortIref_processDesignShortName = 2;
    static constexpr int A_DiagnosticMemoryDestinationPortIref_rootCPT = 1;
    static constexpr int A_DiagnosticMemoryDestinationPortIref_targetPortContextKey = 3;
    static constexpr int A_DiagnosticMemoryDestinationPortIref_targetPortShortName = 4;
    static constexpr int R_DiagnosticMemoryDestinationPortIref_processDesign = 1;              // targetNode[ProcessDesign]
    static constexpr int R_DiagnosticMemoryDestinationPortIref_targetSwcServiceDependency = 0; // targetNode[SwcServiceDependency]
    static constexpr int C_DiagnosticMemoryDestinationPortIref_OWNERS = 0;                     // childNode[DiagnosticMemoryDestinationPortIrefOWNERS]
    //
    static constexpr int N_DiagnosticMemoryDestinationPortMapping = 133; // filtered by existence of referenced processDesign
    static constexpr int A_DiagnosticMemoryDestinationPortMapping_shortName = 0;
    static constexpr int R_DiagnosticMemoryDestinationPortMapping_iref = 2;              // targetNode[DiagnosticMemoryDestinationPortIref] IREF: DiagnosticMemoryDestinationPortIref
    static constexpr int R_DiagnosticMemoryDestinationPortMapping_memoryDestination = 0; // targetNode[DiagnosticMemoryDestination]
    static constexpr int R_DiagnosticMemoryDestinationPortMapping_processDesign = 1;     // targetNode[ProcessDesign]
    //
    static constexpr int N_DiagnosticMemoryDestination = 98;
    static constexpr int A_DiagnosticMemoryDestination_dtcStatusAvailabilityMask = 1; // type=uint
    static constexpr int A_DiagnosticMemoryDestination_kind = 2;                      // restrict to specialization DiagnosticMemoryDestinationPrimary
    static constexpr int A_DiagnosticMemoryDestination_shortName = 0;
    static constexpr int R_DiagnosticMemoryDestination_typeOfFreezeFrameRecordNumeration = 0; // targetNode[LITERAL]
    //
    static constexpr int N_DiagnosticOperationCyclePortIrefOWNERS = 44;
    static constexpr int R_DiagnosticOperationCyclePortIrefOWNERS_irefOwner = 0; // targetNode[DiagnosticOperationCyclePortMapping]
    //
    static constexpr int N_DiagnosticOperationCyclePortIref = 43;
    static constexpr int A_DiagnosticOperationCyclePortIref_executable = 0;
    static constexpr int A_DiagnosticOperationCyclePortIref_processDesignShortName = 2;
    static constexpr int A_DiagnosticOperationCyclePortIref_rootCPT = 1;
    static constexpr int A_DiagnosticOperationCyclePortIref_targetPortContextKey = 3;
    static constexpr int A_DiagnosticOperationCyclePortIref_targetPortShortName = 4;
    static constexpr int R_DiagnosticOperationCyclePortIref_processDesign = 1;              // targetNode[ProcessDesign]
    static constexpr int R_DiagnosticOperationCyclePortIref_targetSwcServiceDependency = 0; // targetNode[SwcServiceDependency]
    static constexpr int C_DiagnosticOperationCyclePortIref_OWNERS = 0;                     // childNode[DiagnosticOperationCyclePortIrefOWNERS]
    //
    static constexpr int N_DiagnosticOperationCyclePortMapping = 42; // filtered by existence of referenced processDesign
    static constexpr int A_DiagnosticOperationCyclePortMapping_shortName = 0;
    static constexpr int R_DiagnosticOperationCyclePortMapping_iref = 2;           // targetNode[DiagnosticOperationCyclePortIref] IREF: DiagnosticOperationCyclePortIref
    static constexpr int R_DiagnosticOperationCyclePortMapping_operationCycle = 0; // targetNode[DiagnosticOperationCycle]
    static constexpr int R_DiagnosticOperationCyclePortMapping_processDesign = 1;  // targetNode[ProcessDesign]
    //
    static constexpr int N_DiagnosticOperationCycle = 41;
    static constexpr int A_DiagnosticOperationCycle_automaticEnd = 1;       // type=boolean value=0|1|true|false
    static constexpr int A_DiagnosticOperationCycle_cycleAutostart = 2;     // type=boolean value=0|1|true|false
    static constexpr int A_DiagnosticOperationCycle_cycleStatusStorage = 3; // type=boolean value=0|1|true|false
    static constexpr int A_DiagnosticOperationCycle_shortName = 0;
    //
    static constexpr int N_DiagnosticProvidedDataMapping = 85;
    static constexpr int A_DiagnosticProvidedDataMapping_dataProvider = 1;
    static constexpr int A_DiagnosticProvidedDataMapping_shortName = 0;
    static constexpr int R_DiagnosticProvidedDataMapping_dataElement = 0; // targetNode[DiagnosticDataElement]
    //
    static constexpr int N_DiagnosticRoutineSubfunctionRequest = 117;
    static constexpr int A_DiagnosticRoutineSubfunctionRequest_bitOffset = 0;   // type=uint
    static constexpr int R_DiagnosticRoutineSubfunctionRequest_dataElement = 0; // targetNode[DiagnosticDataElement2] item is sliced off since aggregated multiply
    //
    static constexpr int N_DiagnosticRoutineSubfunctionResponse = 118;
    static constexpr int A_DiagnosticRoutineSubfunctionResponse_bitOffset = 0;   // type=uint
    static constexpr int R_DiagnosticRoutineSubfunctionResponse_dataElement = 0; // targetNode[DiagnosticDataElement2] item is sliced off since aggregated multiply
    //
    static constexpr int N_DiagnosticRoutineSubfunction = 116;
    static constexpr int A_DiagnosticRoutineSubfunction_kind = 0;     // distinct start + stop + requestResult by type
    static constexpr int A_DiagnosticRoutineSubfunction_role = 1;     // distinct start + stop + requestResult by role
    static constexpr int C_DiagnosticRoutineSubfunction_request = 0;  // childNode[DiagnosticRoutineSubfunctionRequest]
    static constexpr int C_DiagnosticRoutineSubfunction_response = 1; // childNode[DiagnosticRoutineSubfunctionResponse]
    //
    static constexpr int N_DiagnosticRoutine = 115;
    static constexpr int A_DiagnosticRoutine_id = 1; // type=uint
    static constexpr int A_DiagnosticRoutine_shortName = 0;
    static constexpr int C_DiagnosticRoutine_subfunction = 0; // childNode[DiagnosticRoutineSubfunction] merge start + stop + requestResult into one container
    //
    static constexpr int N_DiagnosticSecurityLevelPortIrefOWNERS = 126;
    static constexpr int R_DiagnosticSecurityLevelPortIrefOWNERS_irefOwner = 0; // targetNode[DiagnosticSecurityLevelPortMapping]
    //
    static constexpr int N_DiagnosticSecurityLevelPortIref = 125;
    static constexpr int A_DiagnosticSecurityLevelPortIref_executable = 0;
    static constexpr int A_DiagnosticSecurityLevelPortIref_processDesignShortName = 2;
    static constexpr int A_DiagnosticSecurityLevelPortIref_rootCPT = 1;
    static constexpr int A_DiagnosticSecurityLevelPortIref_targetPortContextKey = 3;
    static constexpr int A_DiagnosticSecurityLevelPortIref_targetPortShortName = 4;
    static constexpr int R_DiagnosticSecurityLevelPortIref_processDesign = 1;              // targetNode[ProcessDesign]
    static constexpr int R_DiagnosticSecurityLevelPortIref_targetSwcServiceDependency = 0; // targetNode[SwcServiceDependency]
    static constexpr int C_DiagnosticSecurityLevelPortIref_OWNERS = 0;                     // childNode[DiagnosticSecurityLevelPortIrefOWNERS]
    //
    static constexpr int N_DiagnosticSecurityLevelPortMapping = 124; // filtered by existence of referenced processDesign
    static constexpr int A_DiagnosticSecurityLevelPortMapping_shortName = 0;
    static constexpr int R_DiagnosticSecurityLevelPortMapping_iref = 2;          // targetNode[DiagnosticSecurityLevelPortIref] IREF: DiagnosticSecurityLevelPortIref
    static constexpr int R_DiagnosticSecurityLevelPortMapping_processDesign = 1; // targetNode[ProcessDesign]
    static constexpr int R_DiagnosticSecurityLevelPortMapping_securityLevel = 0; // targetNode[DiagnosticSecurityLevel]
    //
    static constexpr int N_DiagnosticSecurityLevel = 103;
    static constexpr int A_DiagnosticSecurityLevel_keySize = 1;                 // type=uint
    static constexpr int A_DiagnosticSecurityLevel_numFailedSecurityAccess = 2; // type=uint
    static constexpr int A_DiagnosticSecurityLevel_securityDelayTime = 3;       // type=double dimension=s
    static constexpr int A_DiagnosticSecurityLevel_seedSize = 4;                // type=uint
    static constexpr int A_DiagnosticSecurityLevel_shortName = 0;
    //
    static constexpr int N_DiagnosticServiceClass = 96;     // specializations are DiagnosticControlDTCSettingClass and many more
    static constexpr int A_DiagnosticServiceClass_kind = 1; // specializations are DiagnosticControlDTCSettingClass and many more
    static constexpr int A_DiagnosticServiceClass_shortName = 0;
    static constexpr int R_DiagnosticServiceClass_accessPermission = 1;         // targetNode[DiagnosticAccessPermission]
    static constexpr int R_DiagnosticServiceClass_accessPermissionValidity = 0; // targetNode[LITERAL]
    //
    static constexpr int N_DiagnosticServiceDataIdentifierPortIrefOWNERS = 122;
    static constexpr int R_DiagnosticServiceDataIdentifierPortIrefOWNERS_irefOwner = 0; // targetNode[DiagnosticServiceDataIdentifierPortMapping]
    //
    static constexpr int N_DiagnosticServiceDataIdentifierPortIref = 121;
    static constexpr int A_DiagnosticServiceDataIdentifierPortIref_executable = 0;
    static constexpr int A_DiagnosticServiceDataIdentifierPortIref_processDesignShortName = 2;
    static constexpr int A_DiagnosticServiceDataIdentifierPortIref_rootCPT = 1;
    static constexpr int A_DiagnosticServiceDataIdentifierPortIref_targetPortContextKey = 3;
    static constexpr int A_DiagnosticServiceDataIdentifierPortIref_targetPortShortName = 4;
    static constexpr int R_DiagnosticServiceDataIdentifierPortIref_processDesign = 1;              // targetNode[ProcessDesign]
    static constexpr int R_DiagnosticServiceDataIdentifierPortIref_targetSwcServiceDependency = 0; // targetNode[SwcServiceDependency]
    static constexpr int C_DiagnosticServiceDataIdentifierPortIref_OWNERS = 0;                     // childNode[DiagnosticServiceDataIdentifierPortIrefOWNERS]
    //
    static constexpr int N_DiagnosticServiceDataIdentifierPortMapping = 120; // filtered by existence of referenced processDesign
    static constexpr int A_DiagnosticServiceDataIdentifierPortMapping_shortName = 0;
    static constexpr int R_DiagnosticServiceDataIdentifierPortMapping_diagnosticDataIdentifier = 0; // targetNode[DiagnosticDataIdentifier]
    static constexpr int R_DiagnosticServiceDataIdentifierPortMapping_iref = 2;                     // targetNode[DiagnosticServiceDataIdentifierPortIref] IREF: DiagnosticServiceDataIdentifierPortIref
    static constexpr int R_DiagnosticServiceDataIdentifierPortMapping_processDesign = 1;            // targetNode[ProcessDesign]
    //
    static constexpr int N_DiagnosticServiceInstance = 97; // specializations are DiagnosticControlDTCSetting and many more
    static constexpr int A_DiagnosticServiceInstance_category = 2;
    static constexpr int A_DiagnosticServiceInstance_comControl_customSubFunctionNumber = 5; // type=uint
    static constexpr int A_DiagnosticServiceInstance_dtcSettingParameter = 3;                // type=uint
    static constexpr int A_DiagnosticServiceInstance_ecuReset_customSubFunctionNumber = 6;   // type=uint
    static constexpr int A_DiagnosticServiceInstance_kind = 1;                               // specializations are DiagnosticControlDTCSetting and many more
    static constexpr int A_DiagnosticServiceInstance_securityAccess_requestSeedId = 4;       // type=uint
    static constexpr int A_DiagnosticServiceInstance_shortName = 0;
    static constexpr int R_DiagnosticServiceInstance_accessPermission = 0;                // targetNode[DiagnosticAccessPermission]
    static constexpr int R_DiagnosticServiceInstance_clearDiagnosticInformationClass = 9; // targetNode[DiagnosticServiceClass]
    static constexpr int R_DiagnosticServiceInstance_comControlClass = 15;                // targetNode[DiagnosticServiceClass]
    static constexpr int R_DiagnosticServiceInstance_dataIdentifier = 12;                 // targetNode[DiagnosticDataIdentifier] DiagnosticDataByIdentifier is an abstract intermediate class
    static constexpr int R_DiagnosticServiceInstance_dataTransferClass = 7;               // targetNode[DiagnosticServiceClass]
    static constexpr int R_DiagnosticServiceInstance_diagnosticSession = 5;               // targetNode[DiagnosticSession]
    static constexpr int R_DiagnosticServiceInstance_dtcSettingClass = 1;                 // targetNode[DiagnosticServiceClass]
    static constexpr int R_DiagnosticServiceInstance_ecuResetClass = 8;                   // targetNode[DiagnosticServiceClass]
    static constexpr int R_DiagnosticServiceInstance_readClass = 13;                      // targetNode[DiagnosticServiceClass]
    static constexpr int R_DiagnosticServiceInstance_readDTCInformationClass = 6;         // targetNode[DiagnosticServiceClass]
    static constexpr int R_DiagnosticServiceInstance_requestDownloadClass = 11;           // targetNode[DiagnosticServiceClass]
    static constexpr int R_DiagnosticServiceInstance_routine = 17;                        // targetNode[DiagnosticRoutine]
    static constexpr int R_DiagnosticServiceInstance_routineControlClass = 16;            // targetNode[DiagnosticServiceClass]
    static constexpr int R_DiagnosticServiceInstance_securityAccessClass = 2;             // targetNode[DiagnosticServiceClass]
    static constexpr int R_DiagnosticServiceInstance_securityLevel = 3;                   // targetNode[DiagnosticSecurityLevel]
    static constexpr int R_DiagnosticServiceInstance_sessionControlClass = 4;             // targetNode[DiagnosticServiceClass]
    static constexpr int R_DiagnosticServiceInstance_transferExitClass = 10;              // targetNode[DiagnosticServiceClass]
    static constexpr int R_DiagnosticServiceInstance_writeClass = 14;                     // targetNode[DiagnosticServiceClass]
    //
    static constexpr int N_DiagnosticSession = 102;
    static constexpr int A_DiagnosticSession_id = 1;              // type=uint
    static constexpr int A_DiagnosticSession_p2ServerMax = 2;     // type=double dimension=s
    static constexpr int A_DiagnosticSession_p2StarServerMax = 3; // type=double dimension=s
    static constexpr int A_DiagnosticSession_shortName = 0;
    static constexpr int A_DiagnosticSession_vrte_p2ServerMaxThreshold = 4;     // type=double dimension=s
    static constexpr int A_DiagnosticSession_vrte_p2StarServerMaxThreshold = 5; // type=double dimension=s
    //
    static constexpr int N_DiagnosticTroubleCodeGroupRefDtc = 58;    // variant ref. with mul=*
    static constexpr int R_DiagnosticTroubleCodeGroupRefDtc_dtc = 0; // targetNode[DiagnosticTroubleCode] variant ref. with mul=* (TBC: handling for abstract ref.target)
    //
    static constexpr int N_DiagnosticTroubleCodeGroup = 57;
    static constexpr int A_DiagnosticTroubleCodeGroup_groupNumber = 1; // type=uint
    static constexpr int A_DiagnosticTroubleCodeGroup_shortName = 0;
    static constexpr int C_DiagnosticTroubleCodeGroup_refDtc = 0; // childNode[DiagnosticTroubleCodeGroupRefDtc] variant ref. with mul=*
    //
    static constexpr int N_DiagnosticTroubleCodeRefExtendedDataRecord = 93;                   // variant ref. with mul=*
    static constexpr int R_DiagnosticTroubleCodeRefExtendedDataRecord_extendedDataRecord = 0; // targetNode[DiagnosticExtendedDataRecord] variant ref. with mul=*
    //
    static constexpr int N_DiagnosticTroubleCodeRefFreezeFrame = 94;            // variant ref. with mul=*
    static constexpr int R_DiagnosticTroubleCodeRefFreezeFrame_freezeFrame = 0; // targetNode[DiagnosticFreezeFrame] variant ref. with mul=*
    //
    static constexpr int N_DiagnosticTroubleCodeRefMemoryDestination = 99;                  // ref. with mul=*
    static constexpr int R_DiagnosticTroubleCodeRefMemoryDestination_memoryDestination = 0; // targetNode[DiagnosticMemoryDestination] ref. with mul=*
    //
    static constexpr int N_DiagnosticTroubleCodeUdsToClearConditionGroupMapping = 59;
    static constexpr int A_DiagnosticTroubleCodeUdsToClearConditionGroupMapping_shortName = 0;
    static constexpr int R_DiagnosticTroubleCodeUdsToClearConditionGroupMapping_clearConditionGroup = 0; // targetNode[DiagnosticConditionGroup]
    static constexpr int R_DiagnosticTroubleCodeUdsToClearConditionGroupMapping_troubleCodeUds = 1;      // targetNode[DiagnosticTroubleCode]
    //
    static constexpr int N_DiagnosticTroubleCode = 56; // specializations are DiagnosticTroubleCodeJ1939, DiagnosticTroubleCodeObd, DiagnosticTroubleCodeUds
    static constexpr int A_DiagnosticTroubleCode_aging_shortName = 8;
    static constexpr int A_DiagnosticTroubleCode_aging_threshold = 9; // type=uint
    static constexpr int A_DiagnosticTroubleCode_kind = 1;            // specializations are DiagnosticTroubleCodeJ1939, DiagnosticTroubleCodeObd, DiagnosticTroubleCodeUds
    static constexpr int A_DiagnosticTroubleCode_shortName = 0;
    static constexpr int A_DiagnosticTroubleCode_uds_agingAllowed = 4;                  // type=boolean value=0|1|true|false
    static constexpr int A_DiagnosticTroubleCode_uds_functionalUnit = 2;                // type=uint
    static constexpr int A_DiagnosticTroubleCode_uds_immediateNvDataStorage = 5;        // type=boolean value=0|1|true|false
    static constexpr int A_DiagnosticTroubleCode_uds_maxNumberFreezeFrameRecords = 6;   // type=uint
    static constexpr int A_DiagnosticTroubleCode_uds_priority = 7;                      // type=uint
    static constexpr int A_DiagnosticTroubleCode_uds_udsDtcValue = 3;                   // type=uint
    static constexpr int R_DiagnosticTroubleCode_uds_environmentCaptureToReporting = 1; // targetNode[LITERAL]
    static constexpr int R_DiagnosticTroubleCode_uds_severity = 0;                      // targetNode[LITERAL]
    static constexpr int R_DiagnosticTroubleCode_uds_significance = 2;                  // targetNode[LITERAL]
    static constexpr int R_DiagnosticTroubleCode_uds_snapshotRecordContent = 3;         // targetNode[DiagnosticDataIdentifierSet] variant ref.
    static constexpr int C_DiagnosticTroubleCode_refExtendedDataRecord = 0;             // childNode[DiagnosticTroubleCodeRefExtendedDataRecord] variant ref. with mul=*
    static constexpr int C_DiagnosticTroubleCode_refFreezeFrame = 1;                    // childNode[DiagnosticTroubleCodeRefFreezeFrame] variant ref. with mul=*
    static constexpr int C_DiagnosticTroubleCode_refMemoryDestination = 2;              // childNode[DiagnosticTroubleCodeRefMemoryDestination] ref. with mul=*
    //
    static constexpr int N_ENUMS = 2;       // (most) ENUMS are defined in AUTOSAR Meta Model.
    static constexpr int A_ENUMS_dummy = 0; // no specific attributes for ENUMS container
    static constexpr int C_ENUMS_ENUM = 0;  // childNode[ENUM] Name of the ENUM, e.g. SchedulingPolicyKindEnum
    //
    static constexpr int N_ENUM = 3;         // Name of the ENUM, e.g. SchedulingPolicyKindEnum
    static constexpr int A_ENUM_dummy = 0;   // no specific attributes for the invidual ENUM container
    static constexpr int C_ENUM_LITERAL = 0; // childNode[LITERAL] list of literals in ENUM, any reference to a literal needs to specif ENUM in processingHints as ENUM=…
    //
    static constexpr int N_IREFS = 5;
    static constexpr int A_IREFS_dummy = 0;                                   // no specific attributes for IREFS container
    static constexpr int C_IREFS_DiagnosticEnableConditionPortIref = 2;       // childNode[DiagnosticEnableConditionPortIref]
    static constexpr int C_IREFS_DiagnosticEventPortIref = 0;                 // childNode[DiagnosticEventPortIref]
    static constexpr int C_IREFS_DiagnosticGenericUdsPortIref = 3;            // childNode[DiagnosticGenericUdsPortIref]
    static constexpr int C_IREFS_DiagnosticMemoryDestinationPortIref = 7;     // childNode[DiagnosticMemoryDestinationPortIref]
    static constexpr int C_IREFS_DiagnosticOperationCyclePortIref = 1;        // childNode[DiagnosticOperationCyclePortIref]
    static constexpr int C_IREFS_DiagnosticSecurityLevelPortIref = 6;         // childNode[DiagnosticSecurityLevelPortIref]
    static constexpr int C_IREFS_DiagnosticServiceDataIdentifierPortIref = 4; // childNode[DiagnosticServiceDataIdentifierPortIref]
    static constexpr int C_IREFS_ServiceInstanceToPortPrototypeIref = 5;      // childNode[ServiceInstanceToPortPrototypeIref]
    //
    static constexpr int N_LITERAL = 4;       // list of literals in ENUM, any reference to a literal needs to specif ENUM in processingHints as ENUM=…
    static constexpr int A_LITERAL_value = 0; // provide ENUM value per LITERAL
    //
    static constexpr int N_ProcessDesign = 9;
    static constexpr int A_ProcessDesign_machineShortName = 1;
    static constexpr int A_ProcessDesign_processShortName = 2;
    static constexpr int A_ProcessDesign_shortName = 0;
    //
    static constexpr int N_ROOT = 0;                                                       // ROOT Structure NOT TO BE CHANGED !
    static constexpr int A_ROOT_name = 0;                                                  // ROOT Structure NOT TO BE CHANGED !
    static constexpr int C_ROOT_AdaptiveSWC = 21;                                          // childNode[AdaptiveSWC]
    static constexpr int C_ROOT_DiagnosticAccessPermission = 32;                           // childNode[DiagnosticAccessPermission]
    static constexpr int C_ROOT_DiagnosticCondition = 10;                                  // childNode[DiagnosticCondition] specializations are DiagnosticClearCondition DiagnosticEnableCondition, DiagnosticStorageCondition
    static constexpr int C_ROOT_DiagnosticConditionGroup = 12;                             // childNode[DiagnosticConditionGroup] specializations are DiagnosticClearConditionGroup, DiagnosticEnableConditionGroup, DiagnosticStorageConditionGroup
    static constexpr int C_ROOT_DiagnosticContributionSet = 28;                            // childNode[DiagnosticContributionSet]
    static constexpr int C_ROOT_DiagnosticDataElement = 35;                                // childNode[DiagnosticDataElement] item is sliced off since aggregated multiply
    static constexpr int C_ROOT_DiagnosticDataElement2 = 36;                               // childNode[DiagnosticDataElement2] item is sliced off since aggregated multiply
    static constexpr int C_ROOT_DiagnosticDataIdentifier = 18;                             // childNode[DiagnosticDataIdentifier] specializations are DiagnosticDataIdentifier, DiagnosticDynamicDataIdentifier
    static constexpr int C_ROOT_DiagnosticDataIdentifierSet = 19;                          // childNode[DiagnosticDataIdentifierSet]
    static constexpr int C_ROOT_DiagnosticEnableConditionPortMapping = 11;                 // childNode[DiagnosticEnableConditionPortMapping] filtered by existence of referenced ProcessDesign
    static constexpr int C_ROOT_DiagnosticEnvironmentalCondition = 31;                     // childNode[DiagnosticEnvironmentalCondition]
    static constexpr int C_ROOT_DiagnosticEvent = 5;                                       // childNode[DiagnosticEvent]
    static constexpr int C_ROOT_DiagnosticEventPortMapping = 7;                            // childNode[DiagnosticEventPortMapping] filtered by existence of referenced processDesign
    static constexpr int C_ROOT_DiagnosticEventToDebounceAlgorithmMapping = 37;            // childNode[DiagnosticEventToDebounceAlgorithmMapping]
    static constexpr int C_ROOT_DiagnosticEventToEnableConditionGroupMapping = 13;         // childNode[DiagnosticEventToEnableConditionGroupMapping]
    static constexpr int C_ROOT_DiagnosticEventToOperationCycleMapping = 6;                // childNode[DiagnosticEventToOperationCycleMapping]
    static constexpr int C_ROOT_DiagnosticEventToTroubleCodeUdsMapping = 17;               // childNode[DiagnosticEventToTroubleCodeUdsMapping]
    static constexpr int C_ROOT_DiagnosticExtendedDataRecord = 20;                         // childNode[DiagnosticExtendedDataRecord]
    static constexpr int C_ROOT_DiagnosticFreezeFrame = 24;                                // childNode[DiagnosticFreezeFrame]
    static constexpr int C_ROOT_DiagnosticGenericUdsPortMapping = 23;                      // childNode[DiagnosticGenericUdsPortMapping] filtered by existence of referenced ProcessDesign
    static constexpr int C_ROOT_DiagnosticMemoryDestination = 27;                          // childNode[DiagnosticMemoryDestination]
    static constexpr int C_ROOT_DiagnosticMemoryDestinationPortMapping = 39;               // childNode[DiagnosticMemoryDestinationPortMapping] filtered by existence of referenced ProcessDesign
    static constexpr int C_ROOT_DiagnosticOperationCycle = 8;                              // childNode[DiagnosticOperationCycle]
    static constexpr int C_ROOT_DiagnosticOperationCyclePortMapping = 9;                   // childNode[DiagnosticOperationCyclePortMapping] filtered by existence of referenced ProcessDesign
    static constexpr int C_ROOT_DiagnosticProvidedDataMapping = 22;                        // childNode[DiagnosticProvidedDataMapping]
    static constexpr int C_ROOT_DiagnosticRoutine = 33;                                    // childNode[DiagnosticRoutine]
    static constexpr int C_ROOT_DiagnosticSecurityLevel = 30;                              // childNode[DiagnosticSecurityLevel]
    static constexpr int C_ROOT_DiagnosticSecurityLevelPortMapping = 4;                    // childNode[DiagnosticSecurityLevelPortMapping] filtered by existence of referenced ProcessDesign
    static constexpr int C_ROOT_DiagnosticServiceClass = 25;                               // childNode[DiagnosticServiceClass] specializations are DiagnosticControlDTCSettingClass and many more
    static constexpr int C_ROOT_DiagnosticServiceDataIdentifierPortMapping = 34;           // childNode[DiagnosticServiceDataIdentifierPortMapping] filtered by existence of referenced ProcessDesign
    static constexpr int C_ROOT_DiagnosticServiceInstance = 26;                            // childNode[DiagnosticServiceInstance] specializations are DiagnosticControlDTCSetting and many more
    static constexpr int C_ROOT_DiagnosticSession = 29;                                    // childNode[DiagnosticSession]
    static constexpr int C_ROOT_DiagnosticTroubleCode = 14;                                // childNode[DiagnosticTroubleCode] specializations are DiagnosticTroubleCodeJ1939, DiagnosticTroubleCodeObd, DiagnosticTroubleCodeUds
    static constexpr int C_ROOT_DiagnosticTroubleCodeGroup = 15;                           // childNode[DiagnosticTroubleCodeGroup]
    static constexpr int C_ROOT_DiagnosticTroubleCodeUdsToClearConditionGroupMapping = 16; // childNode[DiagnosticTroubleCodeUdsToClearConditionGroupMapping]
    static constexpr int C_ROOT_ENUMS = 1;                                                 // childNode[ENUMS] ENUMS container
    static constexpr int C_ROOT_IREFS = 2;                                                 // childNode[IREFS] IREFS container
    static constexpr int C_ROOT_ProcessDesign = 3;                                         // childNode[ProcessDesign]
    static constexpr int C_ROOT_ServiceInstanceToPortPrototypeMapping = 38;                // childNode[ServiceInstanceToPortPrototypeMapping] filtered by existence of referenced ProcessDesign
    static constexpr int C_ROOT_UNUSED = 0;                                                // childNode[UNUSED] UNUSED container allows to keep nodeIndex sequence if nodes are disabled.
    //
    static constexpr int N_ServiceInstanceToPortPrototypeIrefOWNERS = 27;
    static constexpr int R_ServiceInstanceToPortPrototypeIrefOWNERS_irefOwner = 0; // targetNode[ServiceInstanceToPortPrototypeMapping]
    //
    static constexpr int N_ServiceInstanceToPortPrototypeIref = 26;
    static constexpr int A_ServiceInstanceToPortPrototypeIref_executable = 0;
    static constexpr int A_ServiceInstanceToPortPrototypeIref_processDesignShortName = 2;
    static constexpr int A_ServiceInstanceToPortPrototypeIref_rootCPT = 1;
    static constexpr int A_ServiceInstanceToPortPrototypeIref_targetPortShortName = 3;
    static constexpr int R_ServiceInstanceToPortPrototypeIref_processDesign = 3;         // targetNode[ProcessDesign]
    static constexpr int R_ServiceInstanceToPortPrototypeIref_targetPPortPrototype = 0;  // targetNode[AdaptivePPort]
    static constexpr int R_ServiceInstanceToPortPrototypeIref_targetPRPortPrototype = 2; // targetNode[AdaptivePRPort]
    static constexpr int R_ServiceInstanceToPortPrototypeIref_targetRPortPrototype = 1;  // targetNode[AdaptiveRPort]
    static constexpr int C_ServiceInstanceToPortPrototypeIref_OWNERS = 0;                // childNode[ServiceInstanceToPortPrototypeIrefOWNERS]
    //
    static constexpr int N_ServiceInstanceToPortPrototypeMapping = 25; // filtered by existence of referenced processDesign
    static constexpr int A_ServiceInstanceToPortPrototypeMapping_serviceDeploymentShortKind = 6;
    static constexpr int A_ServiceInstanceToPortPrototypeMapping_serviceDeploymentShortName = 5;
    static constexpr int A_ServiceInstanceToPortPrototypeMapping_serviceInstanceKind = 2;
    static constexpr int A_ServiceInstanceToPortPrototypeMapping_serviceInstanceShortName = 1;
    static constexpr int A_ServiceInstanceToPortPrototypeMapping_shortName = 0;
    static constexpr int A_ServiceInstanceToPortPrototypeMapping_someip_requiredServiceInstanceId = 4; // type=uint|ANY
    static constexpr int A_ServiceInstanceToPortPrototypeMapping_someip_serviceInstanceId = 3;         // type=uint
    static constexpr int A_ServiceInstanceToPortPrototypeMapping_someip_serviceInterfaceId = 7;        // type=uint
    static constexpr int R_ServiceInstanceToPortPrototypeMapping_iref = 1;                             // targetNode[ServiceInstanceToPortPrototypeIref] IREF: ServiceInstanceToPortPrototypeIref
    static constexpr int R_ServiceInstanceToPortPrototypeMapping_processDesign = 0;                    // targetNode[ProcessDesign] target is ProcessDesign
    //
    static constexpr int N_SwcServiceDependencyAudience = 83;
    static constexpr int R_SwcServiceDependencyAudience_audience = 0; // targetNode[LITERAL] DiagnosticCapabilityElement is an abstract intermediate level class.
    //
    static constexpr int N_SwcServiceDependencyPorts = 84;
    static constexpr int A_SwcServiceDependencyPorts_port_kind = 1; // PPortPrototype, PRPortPrototype or RPortPrototype
    static constexpr int A_SwcServiceDependencyPorts_port_name = 2;
    static constexpr int A_SwcServiceDependencyPorts_providedInterface_kind = 3;
    static constexpr int A_SwcServiceDependencyPorts_providedInterface_name = 4;
    static constexpr int A_SwcServiceDependencyPorts_providedRequiredInterface_kind = 5;
    static constexpr int A_SwcServiceDependencyPorts_providedRequiredInterface_name = 6;
    static constexpr int A_SwcServiceDependencyPorts_requiredInterface_kind = 7;
    static constexpr int A_SwcServiceDependencyPorts_requiredInterface_name = 8;
    static constexpr int A_SwcServiceDependencyPorts_role = 0;
    //
    static constexpr int N_SwcServiceDependency = 82;
    static constexpr int A_SwcServiceDependency_capabilityElement_diagRequirement = 3;              // DiagnosticCapabilityElement is an abstract intermediate level class
    static constexpr int A_SwcServiceDependency_capabilityElement_securityAccessLevel = 4;          // type=uint
    static constexpr int A_SwcServiceDependency_eventInfoNeeds_udsDtcNumber = 5;                    // type=uint
    static constexpr int A_SwcServiceDependency_operationCycleNeeds_operationCycleAutomaticEnd = 6; // type=boolean value=0|1|true|false
    static constexpr int A_SwcServiceDependency_operationCycleNeeds_operationCycleAutostart = 7;    // type=boolean value=0|1|true|false
    static constexpr int A_SwcServiceDependency_serviceNeeds_kind = 1;                              // many service needs specializations are defined, some of them are covered by ECUCFG
    static constexpr int A_SwcServiceDependency_serviceNeeds_shortName = 2;                         // ServiceNeeds is the top level generalization
    static constexpr int A_SwcServiceDependency_shortName = 0;
    static constexpr int R_SwcServiceDependency_communicationManagerNeeds_serviceRequestCallbackType = 0; // targetNode[LITERAL]
    static constexpr int R_SwcServiceDependency_enableConditionNeeds_initialStatus = 1;                   // targetNode[LITERAL]
    static constexpr int R_SwcServiceDependency_eventInfoNeeds_dtcKind = 2;                               // targetNode[LITERAL]
    static constexpr int R_SwcServiceDependency_operationCycleNeeds_operationCycle = 3;                   // targetNode[LITERAL]
    static constexpr int C_SwcServiceDependency_assignedPort = 1;                                         // childNode[SwcServiceDependencyPorts]
    static constexpr int C_SwcServiceDependency_capabilityElement_audience = 0;                           // childNode[SwcServiceDependencyAudience] enum with mul=*
    //
    static constexpr int N_UNUSED = 1;       // UNUSED container allows to keep nodeIndex sequence if nodes are disabled.
    static constexpr int A_UNUSED_dummy = 0; // no specific attributes for UNUSED container
    //
};
// =========================================================================================================================
// end generated constexpr
// =========================================================================================================================
#endif // ECUCFG_DIA_2_1_METADATA_VARIANT
