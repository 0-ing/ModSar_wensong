#ifndef ECUCFG_EXM_2_1_METADATA_VARIANT
// =========================================================================================================================
// generated for EXM at 2020-11-04 08:30:06
//
// begin generated constexpr:
// =========================================================================================================================
#define ECUCFG_EXM_2_1_METADATA_VARIANT "THIS IS THE INCLUDE-GUARD"
#ifndef ECUCFG_EXM_METADATA_NAME
#define ECUCFG_EXM_METADATA_NAME "EXM"
#endif
//
class EXM_constexpr
{
public:
    static constexpr int majorVersion = 2; // approved
    static constexpr int minorVersion = 1;
    //
    static constexpr int N_ENUMS = 2;      // ENUMS are defined in AUTOSAR Meta Model
    static constexpr int C_ENUMS_ENUM = 0; // childNode[ENUM]
    //
    static constexpr int N_ENUM = 3;         // e.g. CommandlinOptionKindEnum, SchedulingPolicyKindEnum
    static constexpr int C_ENUM_LITERAL = 0; // childNode[LITERAL]
    //
    static constexpr int N_EnvironmentVariable = 15;
    static constexpr int A_EnvironmentVariable_key = 0;
    static constexpr int A_EnvironmentVariable_value = 1;
    //
    static constexpr int N_EthConnector = 9;
    static constexpr int A_EthConnector_shortName = 0;
    //
    static constexpr int N_IREFS = 5;
    //
    static constexpr int N_LITERAL = 4;             // list of literals in ENUM, ref. to literal needs to specif ENUM in processingHints
    static constexpr int A_LITERAL_mappedValue = 1; // provide ENUM value per LITERAL (other data sources)
    static constexpr int A_LITERAL_value = 0;       // provide ENUM index/value per LITERAL (data source = AUTOSAR CompuMethod for ENUM)
    //
    static constexpr int N_Machine = 8;
    static constexpr int A_Machine_defaultEnterTimeoutValue = 1; // type=uint dimension=ms
    static constexpr int A_Machine_defaultExitTimeoutValue = 2;  // type=uint dimension=ms
    static constexpr int A_Machine_shortName = 0;
    static constexpr int A_Machine_vrte_securityPolicy = 3;                     // VRTE specific text attribute
    static constexpr int R_Machine_trustedPlatformExecutableLaunchBehavior = 0; // targetNode[LITERAL]
    static constexpr int C_Machine_osModuleInstantiation = 0;                   // childNode[OsModuleInstantiation]
    //
    static constexpr int N_ModeDeclaration = 7;
    static constexpr int A_ModeDeclaration_modeValue = 0;
    //
    static constexpr int N_ModeGroup = 6;
    static constexpr int A_ModeGroup_initialMode_name = 1;
    static constexpr int A_ModeGroup_initialMode_value = 2;
    static constexpr int A_ModeGroup_shortName = 0;
    static constexpr int C_ModeGroup_modeDeclaration = 0; // childNode[ModeDeclaration] State
    //
    static constexpr int N_OsModuleInstantiation = 21;
    static constexpr int A_OsModuleInstantiation_supportedTimerGranularity = 0; // type=uint dimension=ms
    static constexpr int C_OsModuleInstantiation_resourceGroup = 0;             // childNode[ResourceGroup]
    //
    static constexpr int N_Process2ProcessorCore = 11;
    static constexpr int A_Process2ProcessorCore_coreID = 0; // type=uint
    static constexpr int A_Process2ProcessorCore_role = 1;
    //
    static constexpr int N_ProcessExecutionDependency = 14;
    static constexpr int A_ProcessExecutionDependency_stateMachine_name = 3;
    static constexpr int A_ProcessExecutionDependency_stateMachine_prototypeName = 2;
    static constexpr int A_ProcessExecutionDependency_stateName = 0; // ref.target as text
    static constexpr int A_ProcessExecutionDependency_stateValue = 1;
    static constexpr int R_ProcessExecutionDependency_stateDeclaration = 2; // targetNode[ModeDeclaration]
    static constexpr int R_ProcessExecutionDependency_stateMachine = 1;     // targetNode[ModeGroup]
    static constexpr int R_ProcessExecutionDependency_targetProcess = 0;    // targetNode[Process]
    //
    static constexpr int N_ProcessFunctionGroupStateDependency = 13;
    static constexpr int A_ProcessFunctionGroupStateDependency_machineName = 0;
    static constexpr int A_ProcessFunctionGroupStateDependency_stateMachine_name = 2; // ref.target as text
    static constexpr int A_ProcessFunctionGroupStateDependency_stateMachine_prototypeName = 1;
    static constexpr int A_ProcessFunctionGroupStateDependency_stateName = 3; // ref.target as text
    static constexpr int A_ProcessFunctionGroupStateDependency_stateValue = 4;
    static constexpr int R_ProcessFunctionGroupStateDependency_stateDeclaration = 1; // targetNode[ModeDeclaration]
    static constexpr int R_ProcessFunctionGroupStateDependency_stateMachine = 0;     // targetNode[ModeGroup]
    //
    static constexpr int N_ProcessLogTraceLogMode = 18;                // enum with multiplicity=*
    static constexpr int R_ProcessLogTraceLogMode_logTraceLogMode = 0; // targetNode[LITERAL] enum with multiplicity=*
    //
    static constexpr int N_ProcessResourceNeeds = 23;
    static constexpr int A_ProcessResourceNeeds_hardwarePlatform = 0;
    static constexpr int A_ProcessResourceNeeds_init_numberOfInstructions = 1;        // type=uint dimension=NormalizedInstruction (runtime in sec * clock frequency in Hz)
    static constexpr int A_ProcessResourceNeeds_init_sequentialInstructionsBegin = 2; // type=uint dimension=NormalizedInstruction (runtime in sec * clock frequency in Hz)
    static constexpr int A_ProcessResourceNeeds_init_sequentialInstructionsEnd = 3;   // type=uint dimension=NormalizedInstruction (runtime in sec * clock frequency in Hz)
    static constexpr int A_ProcessResourceNeeds_init_speedup = 4;                     // type=float
    static constexpr int A_ProcessResourceNeeds_run_numberOfInstructions = 5;         // type=uint dimension=NormalizedInstruction (runtime in sec * clock frequency in Hz)
    static constexpr int A_ProcessResourceNeeds_run_sequentialInstructionsBegin = 6;  // type=uint dimension=NormalizedInstruction (runtime in sec * clock frequency in Hz)
    static constexpr int A_ProcessResourceNeeds_run_sequentialInstructionsEnd = 7;    // type=uint dimension=NormalizedInstruction (runtime in sec * clock frequency in Hz)
    static constexpr int A_ProcessResourceNeeds_run_speedup = 8;                      // type=float
    //
    static constexpr int N_ProcessSgid = 17;          // VRTE specific attribute with multiplicity=*
    static constexpr int A_ProcessSgid_vrte_sgid = 0; // type=uint
    //
    static constexpr int N_ProcessStartupConfigHeapUsage = 19;
    static constexpr int A_ProcessStartupConfigHeapUsage_memoryConsumption = 0; // type=uint dimension=Byte
    //
    static constexpr int N_ProcessStartupConfigSysMemUsage = 20;
    static constexpr int A_ProcessStartupConfigSysMemUsage_memoryConsumption = 0; // type=uint
    //
    static constexpr int N_ProcessStartupConfig = 12;
    static constexpr int A_ProcessStartupConfig_enterTimeoutValue = 1; // type=uint dimension=ms
    static constexpr int A_ProcessStartupConfig_exitTimeoutValue = 2;  // type=uint dimension=ms
    static constexpr int A_ProcessStartupConfig_schedulingPriority = 5;
    static constexpr int A_ProcessStartupConfig_shortName = 0;
    static constexpr int A_ProcessStartupConfig_vrte_environmentVariables = 4;    // VRTE specific attribute, derived from StartupConfig.environmentVariable
    static constexpr int A_ProcessStartupConfig_vrte_invocationArguments = 3;     // VRTE specific attribute, derived from StartupConfig.startupOption
    static constexpr int R_ProcessStartupConfig_resourceGroup = 0;                // targetNode[ResourceGroup]
    static constexpr int R_ProcessStartupConfig_schedulingPolicyKind = 1;         // targetNode[LITERAL]
    static constexpr int C_ProcessStartupConfig_environmentVariable = 2;          // childNode[EnvironmentVariable]
    static constexpr int C_ProcessStartupConfig_executionDependency = 0;          // childNode[ProcessExecutionDependency]
    static constexpr int C_ProcessStartupConfig_functionGroupStateDependency = 1; // childNode[ProcessFunctionGroupStateDependency]
    static constexpr int C_ProcessStartupConfig_heapUsage = 4;                    // childNode[ProcessStartupConfigHeapUsage]
    static constexpr int C_ProcessStartupConfig_startupOption = 3;                // childNode[StartupOption]
    static constexpr int C_ProcessStartupConfig_systemMemoryUsage = 5;            // childNode[ProcessStartupConfigSysMemUsage]
    //
    static constexpr int N_Process = 10;
    static constexpr int A_Process_deterministicClient_cycleTimeValue = 6;  // type=uint dimension=ms
    static constexpr int A_Process_deterministicClient_numberOfWorkers = 7; // type=uint
    static constexpr int A_Process_executable_minimumTimerGranularity = 21; // type=uint dimension=ms
    static constexpr int A_Process_executable_name = 2;
    static constexpr int A_Process_executable_version = 22; // syntax: uint.uint.uint[.uint] representing major.minor.patch or major.minor.patch.build
    static constexpr int A_Process_logTraceFilePath = 17;
    static constexpr int A_Process_logTraceProcessDesc = 19;
    static constexpr int A_Process_logTraceProcessId = 20;
    static constexpr int A_Process_numberOfRestartAttempts = 4; // type=uint
    static constexpr int A_Process_preMapping = 5;              // type=boolean value=0|1|true|false
    static constexpr int A_Process_shortName = 0;
    static constexpr int A_Process_stateMachine_name = 1;
    static constexpr int A_Process_stateMachine_prototypeName = 3;
    static constexpr int A_Process_vrte_coremask = 9;                    // VRTE specific attribute, derived from Process2ProcessorCore
    static constexpr int A_Process_vrte_gid = 11;                        // type=uint
    static constexpr int A_Process_vrte_hashAlgorithm = 13;              // VRTE specific text attribute
    static constexpr int A_Process_vrte_hashValue = 12;                  // VRTE specific text attribute
    static constexpr int A_Process_vrte_isOneShot = 18;                  // type=boolean value=0|1|true|false
    static constexpr int A_Process_vrte_linuxOnly = 15;                  // type=boolean value=0|1|true|false
    static constexpr int A_Process_vrte_logTraceMaxFileSize = 23;        // type=uint dimension=kByte
    static constexpr int A_Process_vrte_path = 16;                       // VRTE specific text attribute
    static constexpr int A_Process_vrte_qnxOnly = 14;                    // type=boolean value=0|1|true|false
    static constexpr int A_Process_vrte_role = 8;                        // VRTE specific text attribute
    static constexpr int A_Process_vrte_securityPolicyDetails = 24;      // VRTE specific text attribute
    static constexpr int A_Process_vrte_uid = 10;                        // type=uint
    static constexpr int R_Process_executable_loggingBehavior = 2;       // targetNode[LITERAL]
    static constexpr int R_Process_executable_reportingBehavior = 3;     // targetNode[LITERAL]
    static constexpr int R_Process_logTraceDefaultLogLevel = 1;          // targetNode[LITERAL]
    static constexpr int R_Process_stateMachine = 0;                     // targetNode[ModeGroup]
    static constexpr int C_Process_deterministicClientResourceNeeds = 4; // childNode[ProcessResourceNeeds]
    static constexpr int C_Process_logTraceLogModes = 3;                 // childNode[ProcessLogTraceLogMode] enum with multiplicity=*
    static constexpr int C_Process_process2ProcessorCore = 1;            // childNode[Process2ProcessorCore]
    static constexpr int C_Process_startupConfig = 0;                    // childNode[ProcessStartupConfig]
    static constexpr int C_Process_vrte_sgids = 2;                       // childNode[ProcessSgid] VRTE specific attribute with multiplicity=*
    //
    static constexpr int N_ROOT = 0;              // ROOT Structure NOT TO BE CHANGED !
    static constexpr int A_ROOT_name = 0;         // ROOT Structure NOT TO BE CHANGED !
    static constexpr int C_ROOT_ENUMS = 1;        // childNode[ENUMS] ENUMS container
    static constexpr int C_ROOT_EthConnector = 6; // childNode[EthConnector]
    static constexpr int C_ROOT_IREFS = 2;        // childNode[IREFS] IREFS container
    static constexpr int C_ROOT_Machine = 5;      // childNode[Machine]
    static constexpr int C_ROOT_ModeGroup = 3;    // childNode[ModeGroup] StateMachine for FunctionGroup
    static constexpr int C_ROOT_Process = 4;      // childNode[Process]
    static constexpr int C_ROOT_UNUSED = 0;       // childNode[UNUSED] UNUSED container allows to keep nodeIndex sequence if nodes are disabled.
    //
    static constexpr int N_ResourceGroup = 22;
    static constexpr int A_ResourceGroup_cpuUsage = 0; // type=uint in % of total CPU capacity on the machine
    static constexpr int A_ResourceGroup_memUsage = 1; // type=uint dimension=Byte
    //
    static constexpr int N_StartupOption = 16;
    static constexpr int A_StartupOption_optionArgument = 0;
    static constexpr int A_StartupOption_optionName = 1;
    static constexpr int R_StartupOption_optionKind = 0; // targetNode[LITERAL]
    //
    static constexpr int N_UNUSED = 1; // UNUSED container allows to keep nodeIndex sequence if nodes are disabled.
    //
};
// =========================================================================================================================
// end generated constexpr
// =========================================================================================================================
#endif // ECUCFG_EXM_2_1_METADATA_VARIANT
