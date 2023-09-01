#ifndef ECUCFG_EXM_4_0_METADATA_VARIANT
// =========================================================================================================================
// generated for EXM at 2022-09-29 04:10:24 
//
// begin generated constexpr:
// =========================================================================================================================
#define ECUCFG_EXM_4_0_METADATA_VARIANT "THIS IS THE INCLUDE-GUARD"
#ifndef ECUCFG_EXM_METADATA_NAME 
#define ECUCFG_EXM_METADATA_NAME "EXM"
#endif
//
class EXM_constexpr {
public:
static constexpr int majorVersion = 4; // draft
static constexpr int minorVersion = 0;
//
static constexpr int N_ENUMS                                  = 2;
static constexpr int C_ENUMS_ENUM                             = 0; // childNode[ENUM]
// 
static constexpr int N_ENUM                                   = 3;
static constexpr int C_ENUM_LITERAL                           = 0; // childNode[LITERAL]
// 
static constexpr int N_EnvironmentVariable                    = 15;
static constexpr int A_EnvironmentVariable_key                = 0;
static constexpr int A_EnvironmentVariable_value              = 1;
// 
static constexpr int N_LITERAL                                = 4;
static constexpr int A_LITERAL_mappedValue                    = 1;
static constexpr int A_LITERAL_value                          = 0;
// 
static constexpr int N_Machine                                = 8;
static constexpr int A_Machine_defaultEnterTimeoutValue       = 1;
static constexpr int A_Machine_defaultExitTimeoutValue        = 2;
static constexpr int A_Machine_shortName                      = 0;
static constexpr int A_Machine_vrte_securityPolicy            = 3;
static constexpr int R_Machine_trustedPlatformExecutableLaunchBehavior  = 0;
static constexpr int C_Machine_environmentVariable            = 2; // childNode[EnvironmentVariable]
static constexpr int C_Machine_osModuleInstantiation          = 0; // childNode[OsModuleInstantiation]
// 
static constexpr int N_ModeDeclaration                        = 7;
static constexpr int A_ModeDeclaration_modeValue              = 0;
// 
static constexpr int N_ModeGroup                              = 6;
static constexpr int A_ModeGroup_initialMode_name             = 1;
static constexpr int A_ModeGroup_initialMode_value            = 2;
static constexpr int A_ModeGroup_shortName                    = 0;
static constexpr int C_ModeGroup_modeDeclaration              = 0; // childNode[ModeDeclaration]
// 
static constexpr int N_OsModuleInstantiation                  = 21;
static constexpr int A_OsModuleInstantiation_supportedTimerGranularity  = 0;
static constexpr int C_OsModuleInstantiation_resourceGroup    = 0; // childNode[ResourceGroup]
// 
static constexpr int N_ProcessArgument                        = 16;
static constexpr int A_ProcessArgument_argument               = 0;
// 
static constexpr int N_ProcessExecutionDependency             = 14;
static constexpr int A_ProcessExecutionDependency_stateMachine_name  = 3;
static constexpr int A_ProcessExecutionDependency_stateMachine_prototypeName  = 2;
static constexpr int A_ProcessExecutionDependency_stateName   = 0;
static constexpr int A_ProcessExecutionDependency_stateValue  = 1;
static constexpr int R_ProcessExecutionDependency_stateDeclaration  = 2;
static constexpr int R_ProcessExecutionDependency_stateMachine  = 1;
static constexpr int R_ProcessExecutionDependency_targetProcess  = 0;
// 
static constexpr int N_ProcessFunctionGroupStateDependency    = 13;
static constexpr int A_ProcessFunctionGroupStateDependency_functionGroupSetName  = 0;
static constexpr int A_ProcessFunctionGroupStateDependency_stateMachine_name  = 2;
static constexpr int A_ProcessFunctionGroupStateDependency_stateMachine_prototypeName  = 1;
static constexpr int A_ProcessFunctionGroupStateDependency_stateName  = 3;
static constexpr int A_ProcessFunctionGroupStateDependency_stateValue  = 4;
static constexpr int R_ProcessFunctionGroupStateDependency_stateDeclaration  = 1;
static constexpr int R_ProcessFunctionGroupStateDependency_stateMachine  = 0;
// 
static constexpr int N_ProcessResourceNeeds                   = 23;
static constexpr int A_ProcessResourceNeeds_hardwarePlatform  = 0;
static constexpr int A_ProcessResourceNeeds_init_numberOfInstructions  = 1;
static constexpr int A_ProcessResourceNeeds_init_sequentialInstructionsBegin  = 2;
static constexpr int A_ProcessResourceNeeds_init_sequentialInstructionsEnd  = 3;
static constexpr int A_ProcessResourceNeeds_init_speedup      = 4;
static constexpr int A_ProcessResourceNeeds_run_numberOfInstructions  = 5;
static constexpr int A_ProcessResourceNeeds_run_sequentialInstructionsBegin  = 6;
static constexpr int A_ProcessResourceNeeds_run_sequentialInstructionsEnd  = 7;
static constexpr int A_ProcessResourceNeeds_run_speedup       = 8;
// 
static constexpr int N_ProcessSgid                            = 17;
static constexpr int A_ProcessSgid_vrte_sgid                  = 0;
// 
static constexpr int N_ProcessStartupConfigHeapUsage          = 19;
static constexpr int A_ProcessStartupConfigHeapUsage_memoryConsumption  = 0;
// 
static constexpr int N_ProcessStartupConfigSysMemUsage        = 20;
static constexpr int A_ProcessStartupConfigSysMemUsage_memoryConsumption  = 0;
// 
static constexpr int N_ProcessStartupConfig                   = 12;
static constexpr int A_ProcessStartupConfig_enterTimeoutValue  = 1;
static constexpr int A_ProcessStartupConfig_executionError    = 5;
static constexpr int A_ProcessStartupConfig_exitTimeoutValue  = 2;
static constexpr int A_ProcessStartupConfig_schedulingPolicy  = 4;
static constexpr int A_ProcessStartupConfig_schedulingPriority  = 3;
static constexpr int A_ProcessStartupConfig_shortName         = 0;
static constexpr int R_ProcessStartupConfig_resourceGroup     = 0;
static constexpr int R_ProcessStartupConfig_terminationBehavior  = 1;
static constexpr int C_ProcessStartupConfig_environmentVariable  = 2; // childNode[EnvironmentVariable]
static constexpr int C_ProcessStartupConfig_executionDependency  = 0; // childNode[ProcessExecutionDependency]
static constexpr int C_ProcessStartupConfig_functionGroupStateDependency  = 1; // childNode[ProcessFunctionGroupStateDependency]
static constexpr int C_ProcessStartupConfig_heapUsage         = 4; // childNode[ProcessStartupConfigHeapUsage]
static constexpr int C_ProcessStartupConfig_processArgument   = 3; // childNode[ProcessArgument]
static constexpr int C_ProcessStartupConfig_systemMemoryUsage  = 5; // childNode[ProcessStartupConfigSysMemUsage]
// 
static constexpr int N_Process                                = 10;
static constexpr int A_Process_deterministicClient_cycleTimeValue  = 6;
static constexpr int A_Process_deterministicClient_numberOfWorkers  = 7;
static constexpr int A_Process_executable_minimumTimerGranularity  = 18;
static constexpr int A_Process_executable_name                = 2;
static constexpr int A_Process_executable_version             = 19;
static constexpr int A_Process_functionClusterAffiliation     = 8;
static constexpr int A_Process_numberOfRestartAttempts        = 4;
static constexpr int A_Process_preMapping                     = 5;
static constexpr int A_Process_shortName                      = 0;
static constexpr int A_Process_stateMachine_name              = 1;
static constexpr int A_Process_stateMachine_prototypeName     = 3;
static constexpr int A_Process_vrte_coremask                  = 9;
static constexpr int A_Process_vrte_gid                       = 11;
static constexpr int A_Process_vrte_hashAlgorithm             = 13;
static constexpr int A_Process_vrte_hashValue                 = 12;
static constexpr int A_Process_vrte_isOneShot                 = 17;
static constexpr int A_Process_vrte_linuxOnly                 = 15;
static constexpr int A_Process_vrte_logTraceMaxFileSize       = 20;
static constexpr int A_Process_vrte_path                      = 16;
static constexpr int A_Process_vrte_qnxOnly                   = 14;
static constexpr int A_Process_vrte_securityPolicyDetails     = 21;
static constexpr int A_Process_vrte_uid                       = 10;
static constexpr int R_Process_executable_loggingBehavior     = 1;
static constexpr int R_Process_executable_reportingBehavior   = 2;
static constexpr int R_Process_stateMachine                   = 0;
static constexpr int C_Process_deterministicClientResourceNeeds  = 3; // childNode[ProcessResourceNeeds]
static constexpr int C_Process_startupConfig                  = 0; // childNode[ProcessStartupConfig]
static constexpr int C_Process_vrte_sgids                     = 2; // childNode[ProcessSgid]
// 
static constexpr int N_ROOT                                   = 0;
static constexpr int C_ROOT_ENUMS                             = 0; // childNode[ENUMS]
static constexpr int C_ROOT_Machine                           = 5; // childNode[Machine]
static constexpr int C_ROOT_ModeGroup                         = 3; // childNode[ModeGroup]
static constexpr int C_ROOT_Process                           = 4; // childNode[Process]
// 
static constexpr int N_ResourceGroup                          = 22;
static constexpr int A_ResourceGroup_cpuUsage                 = 0;
static constexpr int A_ResourceGroup_memUsage                 = 1;
// 
};
// =========================================================================================================================
// end generated constexpr
// =========================================================================================================================
#endif // ECUCFG_EXM_4_0_METADATA_VARIANT
