#ifndef ECUCFG_STM_4_3_METADATA_VARIANT
// =========================================================================================================================
// generated for STM at 2022-09-29 04:10:24 
//
// begin generated constexpr:
// =========================================================================================================================
#define ECUCFG_STM_4_3_METADATA_VARIANT "THIS IS THE INCLUDE-GUARD"
#ifndef ECUCFG_STM_METADATA_NAME 
#define ECUCFG_STM_METADATA_NAME "STM"
#endif
//
class STM_constexpr {
public:
static constexpr int majorVersion = 4; // draft
static constexpr int minorVersion = 3;
//
static constexpr int N_AdminDataStorage                       = 35;
static constexpr int A_AdminDataStorage_instanceId            = 3;
static constexpr int A_AdminDataStorage_mappingElementGid     = 2;
static constexpr int A_AdminDataStorage_mappingTypeGid        = 1;
static constexpr int A_AdminDataStorage_moduleNameGid         = 0;
// 
static constexpr int N_DiagnosticAddressSWCL                  = 23;
static constexpr int A_DiagnosticAddressSWCL_category         = 0;
static constexpr int A_DiagnosticAddressSWCL_shortName        = 1;
static constexpr int A_DiagnosticAddressSWCL_version          = 2;
// 
static constexpr int N_DiagnosticAddress                      = 22;
static constexpr int A_DiagnosticAddress_addressSemantics     = 0;
static constexpr int C_DiagnosticAddress_SWCL                 = 0; // childNode[DiagnosticAddressSWCL]
// 
static constexpr int N_FunctionGroupSTateIn                   = 27;
static constexpr int A_FunctionGroupSTateIn_targetModeDeclaration  = 2;
// 
static constexpr int N_FunctionGroupStateTransition           = 18;
static constexpr int A_FunctionGroupStateTransition_enteredState  = 0;
static constexpr int A_FunctionGroupStateTransition_exitedState  = 1;
// 
static constexpr int N_FunctionGroupState                     = 17;
static constexpr int A_FunctionGroupState_value               = 0;
// 
static constexpr int N_FunctionGroup                          = 15;
static constexpr int A_FunctionGroup_onTransitionValue        = 8;
static constexpr int A_FunctionGroup_recoveryActions          = 11;
static constexpr int A_FunctionGroup_shortName                = 0;
static constexpr int A_FunctionGroup_stateMachine_ARPath      = 9;
static constexpr int A_FunctionGroup_stateMachine_shortName   = 10;
static constexpr int A_FunctionGroup_swcl_ARPath              = 1;
static constexpr int A_FunctionGroup_swcl_category            = 2;
static constexpr int A_FunctionGroup_swcl_shortName           = 3;
static constexpr int A_FunctionGroup_swcl_version             = 4;
static constexpr int A_FunctionGroup_vrte_FGStateInterfaceAvailable  = 5;
static constexpr int A_FunctionGroup_vrte_maxRetries          = 6;
static constexpr int A_FunctionGroup_vrte_timeout             = 7;
static constexpr int C_FunctionGroup_state                    = 0; // childNode[FunctionGroupState]
static constexpr int C_FunctionGroup_stateTransition          = 1; // childNode[FunctionGroupStateTransition]
// 
static constexpr int N_Machine                                = 8;
static constexpr int A_Machine_shortName                      = 0;
static constexpr int C_Machine_networkManagement              = 26; // childNode[NmInstantiation]
// 
static constexpr int N_NmConfig                               = 32;
static constexpr int A_NmConfig_shortName                     = 0;
static constexpr int C_NmConfig_udpNmCluster                  = 12; // childNode[UdpNmCluster]
// 
static constexpr int N_NmHandleToFunctionGroupStateMapping    = 33;
static constexpr int A_NmHandleToFunctionGroupStateMapping_nmHandle  = 1;
static constexpr int A_NmHandleToFunctionGroupStateMapping_shortName  = 0;
static constexpr int C_NmHandleToFunctionGroupStateMapping_fgSet  = 7; // childNode[FunctionGroupSTateIn]
// 
static constexpr int N_NmHandle                               = 16;
static constexpr int A_NmHandle_Vlans                         = 12;
static constexpr int A_NmHandle_shortName                     = 11;
// 
static constexpr int N_NmInstantiation                        = 19;
static constexpr int A_NmInstantiation_shortName              = 11;
static constexpr int C_NmInstantiation_aData                  = 34; // childNode[AdminDataStorage]
static constexpr int C_NmInstantiation_networkHandle          = 24; // childNode[NmHandle]
// 
static constexpr int N_ROOT                                   = 0;
static constexpr int C_ROOT_DiagnosticAddress                 = 4; // childNode[DiagnosticAddress]
static constexpr int C_ROOT_FunctionGroup                     = 2; // childNode[FunctionGroup]
static constexpr int C_ROOT_Machine                           = 5; // childNode[Machine]
static constexpr int C_ROOT_NmConfig                          = 8; // childNode[NmConfig]
static constexpr int C_ROOT_NmHandlerToFG                     = 27; // childNode[NmHandleToFunctionGroupStateMapping]
static constexpr int C_ROOT_SubSoftwareCluster                = 3; // childNode[SubSoftwareCluster]
// 
static constexpr int N_SubSoftwareCluster                     = 20;
static constexpr int A_SubSoftwareCluster_category            = 1;
static constexpr int A_SubSoftwareCluster_rootSwcl_ARPath     = 3;
static constexpr int A_SubSoftwareCluster_rootSwcl_category   = 4;
static constexpr int A_SubSoftwareCluster_rootSwcl_shortName  = 5;
static constexpr int A_SubSoftwareCluster_rootSwcl_version    = 6;
static constexpr int A_SubSoftwareCluster_shortName           = 0;
static constexpr int A_SubSoftwareCluster_version             = 2;
// 
static constexpr int N_UdpNmCluster                           = 28;
static constexpr int A_UdpNmCluster_shortName                 = 0;
static constexpr int A_UdpNmCluster_udpPort                   = 1;
static constexpr int C_UdpNmCluster_udpNmNode                 = 13; // childNode[UdpNmNode]
// 
static constexpr int N_UdpNmNode                              = 29;
static constexpr int A_UdpNmNode_shortName                    = 0;
// 
};
// =========================================================================================================================
// end generated constexpr
// =========================================================================================================================
#endif // ECUCFG_STM_4_3_METADATA_VARIANT
