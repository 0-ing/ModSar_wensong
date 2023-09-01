#ifndef ECUCFG_CRYPTO_1_0_METADATA_VARIANT
// =========================================================================================================================
// generated for CRYPTO at 2022-09-29 04:10:24 
//
// begin generated constexpr:
// =========================================================================================================================
#define ECUCFG_CRYPTO_1_0_METADATA_VARIANT "THIS IS THE INCLUDE-GUARD"
#ifndef ECUCFG_CRYPTO_METADATA_NAME 
#define ECUCFG_CRYPTO_METADATA_NAME "CRYPTO"
#endif
//
class CRYPTO_constexpr {
public:
static constexpr int majorVersion = 1; // draft
static constexpr int minorVersion = 0;
//
static constexpr int N_CryptoCertificateInterface             = 15;
static constexpr int A_CryptoCertificateInterface_isPrivate   = 0;
static constexpr int A_CryptoCertificateInterface_writeAccess  = 1;
// 
static constexpr int N_CryptoCertificateRefs                  = 32;
static constexpr int R_CryptoCertificateRefs_cryptoCertificate  = 0;
// 
static constexpr int N_CryptoCertificateToCryptoKeySlotMapping  = 39;
static constexpr int R_CryptoCertificateToCryptoKeySlotMapping_cryptoCertificate  = 0;
static constexpr int R_CryptoCertificateToCryptoKeySlotMapping_cryptoKeySlot  = 1;
// 
static constexpr int N_CryptoCertificateToPortPrototypeIrefOWNERS  = 52;
static constexpr int R_CryptoCertificateToPortPrototypeIrefOWNERS_irefOwner  = 0;
// 
static constexpr int N_CryptoCertificateToPortPrototypeIref   = 51;
static constexpr int A_CryptoCertificateToPortPrototypeIref_executable_shortName  = 0;
static constexpr int A_CryptoCertificateToPortPrototypeIref_process_shortName  = 2;
static constexpr int A_CryptoCertificateToPortPrototypeIref_rootCPT_shortName  = 1;
static constexpr int R_CryptoCertificateToPortPrototypeIref_process  = 1;
static constexpr int R_CryptoCertificateToPortPrototypeIref_targetPortPrototype  = 0;
static constexpr int C_CryptoCertificateToPortPrototypeIref_OWNERS  = 0; // childNode[CryptoCertificateToPortPrototypeIrefOWNERS]
// 
static constexpr int N_CryptoCertificateToPortPrototypeMapping  = 50;
static constexpr int A_CryptoCertificateToPortPrototypeMapping_shortName  = 0;
static constexpr int R_CryptoCertificateToPortPrototypeMapping_cryptoCertificate  = 2;
static constexpr int R_CryptoCertificateToPortPrototypeMapping_iref  = 1;
static constexpr int R_CryptoCertificateToPortPrototypeMapping_process  = 0;
// 
static constexpr int N_CryptoCertificate                      = 33;
static constexpr int A_CryptoCertificate_cryptoCertificateIsPrivate  = 0;
// 
static constexpr int N_CryptoKeySlotContentAllowedUsage       = 38;
static constexpr int A_CryptoKeySlotContentAllowedUsage_cryptoAllowedKeyslotUsage  = 0;
// 
static constexpr int N_CryptoKeySlotInterfaceAllowedUsage     = 14;
static constexpr int A_CryptoKeySlotInterfaceAllowedUsage_allowedKeyslotUsage  = 0;
// 
static constexpr int N_CryptoKeySlotInterface                 = 13;
static constexpr int A_CryptoKeySlotInterface_allocateShadowCopy  = 1;
static constexpr int A_CryptoKeySlotInterface_allowedModification_allowContentTypeChange  = 6;
static constexpr int A_CryptoKeySlotInterface_allowedModification_exportability  = 7;
static constexpr int A_CryptoKeySlotInterface_allowedModification_maxNumberOfAllowedUpdates  = 8;
static constexpr int A_CryptoKeySlotInterface_allowedModification_restrictUpdate  = 9;
static constexpr int A_CryptoKeySlotInterface_cryptoAlgId     = 2;
static constexpr int A_CryptoKeySlotInterface_cryptoObjectType  = 3;
static constexpr int A_CryptoKeySlotInterface_shortName       = 0;
static constexpr int A_CryptoKeySlotInterface_slotCapacity    = 4;
static constexpr int A_CryptoKeySlotInterface_slotType        = 5;
static constexpr int C_CryptoKeySlotInterface_keySlotInterfaceAllowedUsage  = 0; // childNode[CryptoKeySlotInterfaceAllowedUsage]
// 
static constexpr int N_CryptoKeySlotRefs                      = 36;
static constexpr int R_CryptoKeySlotRefs_cryptoKeySlot        = 0;
static constexpr int C_CryptoKeySlotRefs_keySlotContentAllowedUsage  = 0; // childNode[CryptoKeySlotContentAllowedUsage]
// 
static constexpr int N_CryptoKeySlotToPortPrototypeIrefOWNERS  = 42;
static constexpr int R_CryptoKeySlotToPortPrototypeIrefOWNERS_irefOwner  = 0;
// 
static constexpr int N_CryptoKeySlotToPortPrototypeIref       = 41;
static constexpr int A_CryptoKeySlotToPortPrototypeIref_executable_shortName  = 0;
static constexpr int A_CryptoKeySlotToPortPrototypeIref_process_shortName  = 2;
static constexpr int A_CryptoKeySlotToPortPrototypeIref_rootCPT_shortName  = 1;
static constexpr int R_CryptoKeySlotToPortPrototypeIref_process  = 1;
static constexpr int R_CryptoKeySlotToPortPrototypeIref_targetPortPrototype  = 0;
static constexpr int C_CryptoKeySlotToPortPrototypeIref_OWNERS  = 0; // childNode[CryptoKeySlotToPortPrototypeIrefOWNERS]
// 
static constexpr int N_CryptoKeySlotToPortPrototypeMapping    = 40;
static constexpr int A_CryptoKeySlotToPortPrototypeMapping_shortName  = 0;
static constexpr int R_CryptoKeySlotToPortPrototypeMapping_cryptoKeySlot  = 2;
static constexpr int R_CryptoKeySlotToPortPrototypeMapping_iref  = 1;
static constexpr int R_CryptoKeySlotToPortPrototypeMapping_process  = 0;
// 
static constexpr int N_CryptoKeySlot                          = 37;
static constexpr int A_CryptoKeySlot_allocateShadowCopy       = 1;
static constexpr int A_CryptoKeySlot_allowedModification_allowContentTypeChange  = 6;
static constexpr int A_CryptoKeySlot_allowedModification_exportability  = 7;
static constexpr int A_CryptoKeySlot_allowedModification_maxNumberOfAllowedUpdates  = 8;
static constexpr int A_CryptoKeySlot_allowedModification_restrictUpdate  = 9;
static constexpr int A_CryptoKeySlot_cryptoAlgId              = 2;
static constexpr int A_CryptoKeySlot_cryptoObjectType         = 3;
static constexpr int A_CryptoKeySlot_shortName                = 0;
static constexpr int A_CryptoKeySlot_slotCapacity             = 4;
static constexpr int A_CryptoKeySlot_slotType                 = 5;
static constexpr int A_CryptoKeySlot_vrte_deploymentDetails   = 11;
static constexpr int A_CryptoKeySlot_vrte_deploymentType      = 10;
static constexpr int A_CryptoKeySlot_vrte_keySlotNum          = 12;
// 
static constexpr int N_CryptoModuleInstantiation              = 30;
static constexpr int A_CryptoModuleInstantiation_vrte_ipcBufferSize  = 2;
static constexpr int A_CryptoModuleInstantiation_vrte_maxKeySlotNum  = 0;
static constexpr int A_CryptoModuleInstantiation_vrte_maxNumberOfThreads  = 1;
static constexpr int C_CryptoModuleInstantiation_certificateToKeySlotMapping  = 2; // childNode[CryptoCertificateToCryptoKeySlotMapping]
static constexpr int C_CryptoModuleInstantiation_cryptoCertificateRefs  = 0; // childNode[CryptoCertificateRefs]
static constexpr int C_CryptoModuleInstantiation_cryptoProviderRefs  = 1; // childNode[CryptoProviderRefs]
// 
static constexpr int N_CryptoPortPrototype                    = 20;
static constexpr int A_CryptoPortPrototype_shortName          = 0;
static constexpr int R_CryptoPortPrototype_cryptoCertificateInterface  = 0;
static constexpr int R_CryptoPortPrototype_cryptoKeySlotInterface  = 1;
static constexpr int R_CryptoPortPrototype_cryptoProviderInterfac  = 2;
// 
static constexpr int N_CryptoProviderInterface                = 17;
// 
static constexpr int N_CryptoProviderRefs                     = 34;
static constexpr int R_CryptoProviderRefs_cryptoProvider      = 0;
static constexpr int C_CryptoProviderRefs_keySlotRefs         = 0; // childNode[CryptoKeySlotRefs]
// 
static constexpr int N_CryptoProviderToPortPrototypeIrefOWNERS  = 47;
static constexpr int R_CryptoProviderToPortPrototypeIrefOWNERS_irefOwner  = 0;
// 
static constexpr int N_CryptoProviderToPortPrototypeIref      = 46;
static constexpr int A_CryptoProviderToPortPrototypeIref_executable_shortName  = 0;
static constexpr int A_CryptoProviderToPortPrototypeIref_process_shortName  = 2;
static constexpr int A_CryptoProviderToPortPrototypeIref_rootCPT_shortName  = 1;
static constexpr int R_CryptoProviderToPortPrototypeIref_process  = 1;
static constexpr int R_CryptoProviderToPortPrototypeIref_targetPortPrototype  = 0;
static constexpr int C_CryptoProviderToPortPrototypeIref_OWNERS  = 0; // childNode[CryptoProviderToPortPrototypeIrefOWNERS]
// 
static constexpr int N_CryptoProviderToPortPrototypeMapping   = 45;
static constexpr int A_CryptoProviderToPortPrototypeMapping_shortName  = 0;
static constexpr int R_CryptoProviderToPortPrototypeMapping_cryptoProvider  = 2;
static constexpr int R_CryptoProviderToPortPrototypeMapping_iref  = 1;
static constexpr int R_CryptoProviderToPortPrototypeMapping_process  = 0;
// 
static constexpr int N_CryptoProvider                         = 35;
// 
static constexpr int N_ENUMS                                  = 2;
static constexpr int C_ENUMS_ENUM                             = 0; // childNode[ENUM]
// 
static constexpr int N_ENUM                                   = 3;
static constexpr int C_ENUM_LITERAL                           = 0; // childNode[LITERAL]
// 
static constexpr int N_IREFS                                  = 5;
static constexpr int C_IREFS_irefCryptoCertificateToPortPrototype  = 2; // childNode[CryptoCertificateToPortPrototypeIref]
static constexpr int C_IREFS_irefCryptoKeySlotToPortPrototype  = 0; // childNode[CryptoKeySlotToPortPrototypeIref]
static constexpr int C_IREFS_irefCryptoProviderToPortPrototype  = 1; // childNode[CryptoProviderToPortPrototypeIref]
// 
static constexpr int N_LITERAL                                = 4;
static constexpr int A_LITERAL_mappedValue                    = 1;
static constexpr int A_LITERAL_value                          = 0;
// 
static constexpr int N_Process                                = 10;
static constexpr int A_Process_shortName                      = 0;
static constexpr int A_Process_swcl_ARPath                    = 1;
// 
static constexpr int N_ROOT                                   = 0;
static constexpr int C_ROOT_CryptoCertificate                 = 8; // childNode[CryptoCertificate]
static constexpr int C_ROOT_CryptoCertificateInterface        = 4; // childNode[CryptoCertificateInterface]
static constexpr int C_ROOT_CryptoCertificateToPortPrototypeMapping  = 13; // childNode[CryptoCertificateToPortPrototypeMapping]
static constexpr int C_ROOT_CryptoKeySlot                     = 10; // childNode[CryptoKeySlot]
static constexpr int C_ROOT_CryptoKeySlotInterface            = 3; // childNode[CryptoKeySlotInterface]
static constexpr int C_ROOT_CryptoKeySlotToPortPrototypeMapping  = 11; // childNode[CryptoKeySlotToPortPrototypeMapping]
static constexpr int C_ROOT_CryptoModuleInstantiation         = 7; // childNode[CryptoModuleInstantiation]
static constexpr int C_ROOT_CryptoPortPrototype               = 6; // childNode[CryptoPortPrototype]
static constexpr int C_ROOT_CryptoProvider                    = 9; // childNode[CryptoProvider]
static constexpr int C_ROOT_CryptoProviderInterface           = 5; // childNode[CryptoProviderInterface]
static constexpr int C_ROOT_CryptoProviderToPortPrototypeMapping  = 12; // childNode[CryptoProviderToPortPrototypeMapping]
static constexpr int C_ROOT_ENUMS                             = 0; // childNode[ENUMS]
static constexpr int C_ROOT_IREFS                             = 1; // childNode[IREFS]
static constexpr int C_ROOT_Process                           = 2; // childNode[Process]
// 
};
// =========================================================================================================================
// end generated constexpr
// =========================================================================================================================
#endif // ECUCFG_CRYPTO_1_0_METADATA_VARIANT
