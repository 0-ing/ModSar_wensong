#ifndef ECUCFG_COM_4_1_METADATA_VARIANT
// =========================================================================================================================
// generated for COM at 2022-09-29 04:10:24 
//
// begin generated constexpr:
// =========================================================================================================================
#define ECUCFG_COM_4_1_METADATA_VARIANT "THIS IS THE INCLUDE-GUARD"
#ifndef ECUCFG_COM_METADATA_NAME 
#define ECUCFG_COM_METADATA_NAME "COM"
#endif
//
class COM_constexpr {
public:
static constexpr int majorVersion = 4; // unspecified
static constexpr int minorVersion = 1;
//
static constexpr int N_ComSecOcToCryptoKeySlotMapping         = 60;
static constexpr int A_ComSecOcToCryptoKeySlotMapping_crypto_provider  = 4;
static constexpr int A_ComSecOcToCryptoKeySlotMapping_key_slot  = 5;
static constexpr int R_ComSecOcToCryptoKeySlotMapping_serviceElementSecureComConfig  = 0;
// 
static constexpr int N_EventGroupId                           = 79;
static constexpr int A_EventGroupId_eventId                   = 0;
// 
static constexpr int N_EventGroup                             = 78;
static constexpr int A_EventGroup_groupId                     = 0;
static constexpr int C_EventGroup_eventIds                    = 1; // childNode[EventGroupId]
// 
static constexpr int N_ProvidedServiceRef                     = 76;
static constexpr int R_ProvidedServiceRef_providedServiceInstance  = 0;
// 
static constexpr int N_ProvidedSomeipServiceInstance          = 50;
static constexpr int A_ProvidedSomeipServiceInstance_serviceInstanceId  = 1;
static constexpr int R_ProvidedSomeipServiceInstance_serviceInterfaceDeployment  = 0;
static constexpr int C_ProvidedSomeipServiceInstance_elementSecOcConfig  = 2; // childNode[ServiceInterfaceElementSecureComConfig]
// 
static constexpr int N_ROOT                                   = 0;
static constexpr int C_ROOT_ComSecOcToCryptoKeySlotMapping    = 11; // childNode[ComSecOcToCryptoKeySlotMapping]
static constexpr int C_ROOT_ProvidedSomeipServiceInstance     = 9; // childNode[ProvidedSomeipServiceInstance]
static constexpr int C_ROOT_RequiredSomeipServiceInstance     = 10; // childNode[RequiredSomeipServiceInstance]
static constexpr int C_ROOT_SecOcSecureComProps               = 12; // childNode[SecOcSecureComProps]
static constexpr int C_ROOT_ServiceInterface                  = 7; // childNode[ServiceInterface]
static constexpr int C_ROOT_SomeipServiceInstanceToMachineMapping  = 13; // childNode[SomeipServiceInstanceToMachineMapping]
static constexpr int C_ROOT_SomeipServiceInterfaceDeployment  = 8; // childNode[SomeipServiceInterfaceDeployment]
// 
static constexpr int N_RequiredServiceRef                     = 77;
static constexpr int R_RequiredServiceRef_requiredServiceInstance  = 0;
// 
static constexpr int N_RequiredSomeipServiceInstance          = 55;
static constexpr int A_RequiredSomeipServiceInstance_serviceInstanceId  = 1;
static constexpr int R_RequiredSomeipServiceInstance_serviceInterfaceDeployment  = 0;
static constexpr int C_RequiredSomeipServiceInstance_elementSecOcConfig  = 2; // childNode[ServiceInterfaceElementSecureComConfig]
// 
static constexpr int N_SecOcSecureComProps                    = 70;
static constexpr int A_SecOcSecureComProps_authAlgorithm      = 0;
static constexpr int A_SecOcSecureComProps_authInfoTxLength   = 1;
static constexpr int A_SecOcSecureComProps_freshnessValueLength  = 2;
static constexpr int A_SecOcSecureComProps_freshnessValueTxLength  = 3;
// 
static constexpr int N_ServiceInterfaceElementSecureComConfig  = 65;
static constexpr int A_ServiceInterfaceElementSecureComConfig_dataId  = 1;
static constexpr int A_ServiceInterfaceElementSecureComConfig_freshnessValueId  = 0;
static constexpr int R_ServiceInterfaceElementSecureComConfig_event  = 0;
static constexpr int R_ServiceInterfaceElementSecureComConfig_fieldNotifier  = 1;
static constexpr int R_ServiceInterfaceElementSecureComConfig_getterCall  = 2;
static constexpr int R_ServiceInterfaceElementSecureComConfig_getterReturn  = 3;
static constexpr int R_ServiceInterfaceElementSecureComConfig_methodCall  = 4;
static constexpr int R_ServiceInterfaceElementSecureComConfig_methodReturn  = 5;
static constexpr int R_ServiceInterfaceElementSecureComConfig_setterCall  = 6;
static constexpr int R_ServiceInterfaceElementSecureComConfig_setterReturn  = 7;
// 
static constexpr int N_ServiceInterfaceField                  = 33;
static constexpr int A_ServiceInterfaceField_hasGetter        = 1;
static constexpr int A_ServiceInterfaceField_hasNotifier      = 2;
static constexpr int A_ServiceInterfaceField_hasSetter        = 3;
// 
static constexpr int N_ServiceInterface                       = 30;
static constexpr int A_ServiceInterface_majorVersion          = 1;
static constexpr int A_ServiceInterface_minorVersion          = 2;
static constexpr int C_ServiceInterface_field                 = 0; // childNode[ServiceInterfaceField]
// 
static constexpr int N_SomeipEventDeployment                  = 41;
static constexpr int A_SomeipEventDeployment_eventId          = 1;
static constexpr int A_SomeipEventDeployment_serializationSize  = 2;
static constexpr int A_SomeipEventDeployment_shortName        = 0;
static constexpr int A_SomeipEventDeployment_signalBased      = 3;
// 
static constexpr int N_SomeipFieldDeployment                  = 43;
static constexpr int A_SomeipFieldDeployment_get_methodId     = 1;
static constexpr int A_SomeipFieldDeployment_notifier_eventId  = 3;
static constexpr int A_SomeipFieldDeployment_serializationSize  = 4;
static constexpr int A_SomeipFieldDeployment_set_methodId     = 2;
static constexpr int A_SomeipFieldDeployment_shortName        = 0;
static constexpr int R_SomeipFieldDeployment_field            = 0;
// 
static constexpr int N_SomeipMethodDeployment                 = 42;
static constexpr int A_SomeipMethodDeployment_isFireAndForget  = 3;
static constexpr int A_SomeipMethodDeployment_methodId        = 1;
static constexpr int A_SomeipMethodDeployment_serializationSize  = 2;
static constexpr int A_SomeipMethodDeployment_shortName       = 0;
// 
static constexpr int N_SomeipServiceInstanceToMachineMapping  = 75;
static constexpr int R_SomeipServiceInstanceToMachineMapping_secureMulticast  = 2;
static constexpr int R_SomeipServiceInstanceToMachineMapping_secureTcp  = 3;
static constexpr int R_SomeipServiceInstanceToMachineMapping_secureUdp  = 4;
static constexpr int C_SomeipServiceInstanceToMachineMapping_providedServices  = 0; // childNode[ProvidedServiceRef]
static constexpr int C_SomeipServiceInstanceToMachineMapping_requiredServices  = 1; // childNode[RequiredServiceRef]
// 
static constexpr int N_SomeipServiceInterfaceDeployment       = 40;
static constexpr int A_SomeipServiceInterfaceDeployment_serviceInterfaceId  = 1;
static constexpr int A_SomeipServiceInterfaceDeployment_shortName  = 0;
static constexpr int R_SomeipServiceInterfaceDeployment_serviceInterface  = 0;
static constexpr int C_SomeipServiceInterfaceDeployment_eventDeployment  = 0; // childNode[SomeipEventDeployment]
static constexpr int C_SomeipServiceInterfaceDeployment_eventGroups  = 3; // childNode[EventGroup]
static constexpr int C_SomeipServiceInterfaceDeployment_fieldDeployment  = 2; // childNode[SomeipFieldDeployment]
static constexpr int C_SomeipServiceInterfaceDeployment_methodDeployment  = 1; // childNode[SomeipMethodDeployment]
// 
};
// =========================================================================================================================
// end generated constexpr
// =========================================================================================================================
#endif // ECUCFG_COM_4_1_METADATA_VARIANT
