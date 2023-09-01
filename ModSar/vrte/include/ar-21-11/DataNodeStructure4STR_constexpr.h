#ifndef ECUCFG_STR_4_0_METADATA_VARIANT
// =========================================================================================================================
// generated for STR at 2022-09-29 04:10:32 
//
// begin generated constexpr:
// =========================================================================================================================
#define ECUCFG_STR_4_0_METADATA_VARIANT "THIS IS THE INCLUDE-GUARD"
#ifndef ECUCFG_STR_METADATA_NAME 
#define ECUCFG_STR_METADATA_NAME "STR"
#endif
//
class STR_constexpr {
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
static constexpr int N_IREF4FileStoragePortPrototypeOWNERS    = 57;
static constexpr int R_IREF4FileStoragePortPrototypeOWNERS_irefOwner  = 0;
// 
static constexpr int N_IREF4FileStoragePortPrototype          = 56;
static constexpr int A_IREF4FileStoragePortPrototype_base     = 1;
static constexpr int A_IREF4FileStoragePortPrototype_contextRootSwComponentPrototype  = 3;
static constexpr int A_IREF4FileStoragePortPrototype_fileStorage_shortName  = 5;
static constexpr int A_IREF4FileStoragePortPrototype_fileStorage_uri  = 6;
static constexpr int A_IREF4FileStoragePortPrototype_interface_kind  = 2;
static constexpr int A_IREF4FileStoragePortPrototype_port_shortName  = 4;
static constexpr int A_IREF4FileStoragePortPrototype_processShortName  = 0;
static constexpr int A_IREF4FileStoragePortPrototype_vrte_portIdentifier  = 7;
static constexpr int R_IREF4FileStoragePortPrototype_process  = 0;
static constexpr int R_IREF4FileStoragePortPrototype_providedInterface  = 1;
static constexpr int R_IREF4FileStoragePortPrototype_providedRequiredInterface  = 2;
static constexpr int R_IREF4FileStoragePortPrototype_requiredInterface  = 3;
static constexpr int C_IREF4FileStoragePortPrototype_OWNERS   = 0; // childNode[IREF4FileStoragePortPrototypeOWNERS]
// 
static constexpr int N_IREF4KeyValueStoragePortPrototypeOWNERS  = 47;
static constexpr int R_IREF4KeyValueStoragePortPrototypeOWNERS_irefOwner  = 0;
// 
static constexpr int N_IREF4KeyValueStoragePortPrototype      = 46;
static constexpr int A_IREF4KeyValueStoragePortPrototype_base  = 1;
static constexpr int A_IREF4KeyValueStoragePortPrototype_contextRootSwComponentPrototype  = 3;
static constexpr int A_IREF4KeyValueStoragePortPrototype_interface_kind  = 2;
static constexpr int A_IREF4KeyValueStoragePortPrototype_interface_name  = 9;
static constexpr int A_IREF4KeyValueStoragePortPrototype_keyValueStorage_shortName  = 5;
static constexpr int A_IREF4KeyValueStoragePortPrototype_keyValueStorage_uri  = 6;
static constexpr int A_IREF4KeyValueStoragePortPrototype_port_kind  = 8;
static constexpr int A_IREF4KeyValueStoragePortPrototype_port_shortName  = 4;
static constexpr int A_IREF4KeyValueStoragePortPrototype_processShortName  = 0;
static constexpr int A_IREF4KeyValueStoragePortPrototype_vrte_portIdentifier  = 7;
static constexpr int R_IREF4KeyValueStoragePortPrototype_interface  = 5;
static constexpr int R_IREF4KeyValueStoragePortPrototype_port  = 4;
static constexpr int R_IREF4KeyValueStoragePortPrototype_process  = 0;
static constexpr int R_IREF4KeyValueStoragePortPrototype_providedInterface  = 1;
static constexpr int R_IREF4KeyValueStoragePortPrototype_providedRequiredInterface  = 2;
static constexpr int R_IREF4KeyValueStoragePortPrototype_requiredInterface  = 3;
static constexpr int C_IREF4KeyValueStoragePortPrototype_OWNERS  = 0; // childNode[IREF4KeyValueStoragePortPrototypeOWNERS]
// 
static constexpr int N_IREFS                                  = 5;
static constexpr int C_IREFS_IREF4FileStoragePortPrototype    = 1; // childNode[IREF4FileStoragePortPrototype]
static constexpr int C_IREFS_IREF4KeyValueStoragePortPrototype  = 0; // childNode[IREF4KeyValueStoragePortPrototype]
// 
static constexpr int N_LITERAL                                = 4;
static constexpr int A_LITERAL_mappedValue                    = 1;
static constexpr int A_LITERAL_value                          = 0;
// 
static constexpr int N_PersistencyDataElement                 = 31;
static constexpr int A_PersistencyDataElement_shortName       = 0;
static constexpr int A_PersistencyDataElement_typeKind        = 2;
static constexpr int A_PersistencyDataElement_typeName        = 3;
static constexpr int A_PersistencyDataElement_updateStrategy  = 1;
// 
static constexpr int N_PersistencyDataRequiredComSpec         = 64;
static constexpr int A_PersistencyDataRequiredComSpec_initValue_kind  = 1;
static constexpr int A_PersistencyDataRequiredComSpec_initValue_name  = 0;
static constexpr int A_PersistencyDataRequiredComSpec_initValue_numerical  = 2;
static constexpr int A_PersistencyDataRequiredComSpec_initValue_text  = 3;
static constexpr int R_PersistencyDataRequiredComSpec_dataElement  = 0;
static constexpr int C_PersistencyDataRequiredComSpec_initValue_array  = 0; // childNode[PersistencyDataRequiredInitValueElement]
// 
static constexpr int N_PersistencyDataRequiredInitValueElement  = 65;
static constexpr int A_PersistencyDataRequiredInitValueElement_value_kind  = 1;
static constexpr int A_PersistencyDataRequiredInitValueElement_value_name  = 0;
static constexpr int A_PersistencyDataRequiredInitValueElement_value_numerical  = 2;
static constexpr int A_PersistencyDataRequiredInitValueElement_value_text  = 3;
// 
static constexpr int N_PersistencyFileElement                 = 36;
static constexpr int A_PersistencyFileElement_contentUri      = 1;
static constexpr int A_PersistencyFileElement_fileName        = 2;
static constexpr int A_PersistencyFileElement_shortName       = 0;
static constexpr int A_PersistencyFileElement_updateStrategy  = 3;
// 
static constexpr int N_PersistencyFileStorageInterface        = 35;
static constexpr int A_PersistencyFileStorageInterface_maxNumberOfFiles  = 4;
static constexpr int A_PersistencyFileStorageInterface_minimumSustainedSize  = 1;
static constexpr int A_PersistencyFileStorageInterface_redundancy  = 2;
static constexpr int A_PersistencyFileStorageInterface_shortName  = 0;
static constexpr int A_PersistencyFileStorageInterface_updateStrategy  = 3;
static constexpr int C_PersistencyFileStorageInterface_fileElement  = 0; // childNode[PersistencyFileElement]
// 
static constexpr int N_PersistencyFileStorageRedundancyHandling  = 52;
static constexpr int A_PersistencyFileStorageRedundancyHandling_crc_algorithmFamily  = 0;
static constexpr int A_PersistencyFileStorageRedundancyHandling_crc_length  = 1;
static constexpr int A_PersistencyFileStorageRedundancyHandling_kind  = 4;
static constexpr int A_PersistencyFileStorageRedundancyHandling_mn_m  = 2;
static constexpr int A_PersistencyFileStorageRedundancyHandling_mn_n  = 3;
static constexpr int A_PersistencyFileStorageRedundancyHandling_scope  = 5;
// 
static constexpr int N_PersistencyFileStorage                 = 50;
static constexpr int A_PersistencyFileStorage_maximumAllowedSize  = 1;
static constexpr int A_PersistencyFileStorage_minimumSustainedSize  = 2;
static constexpr int A_PersistencyFileStorage_shortName       = 0;
static constexpr int A_PersistencyFileStorage_swcl_version    = 5;
static constexpr int A_PersistencyFileStorage_updateStrategy  = 3;
static constexpr int A_PersistencyFileStorage_uri             = 4;
static constexpr int C_PersistencyFileStorage_file            = 0; // childNode[PersistencyFile]
static constexpr int C_PersistencyFileStorage_redundancyHandling  = 1; // childNode[PersistencyFileStorageRedundancyHandling]
// 
static constexpr int N_PersistencyFile                        = 51;
static constexpr int A_PersistencyFile_contentUri             = 1;
static constexpr int A_PersistencyFile_fileName               = 2;
static constexpr int A_PersistencyFile_shortName              = 0;
static constexpr int A_PersistencyFile_updateStrategy         = 3;
// 
static constexpr int N_PersistencyKeyInitValueElement         = 44;
static constexpr int A_PersistencyKeyInitValueElement_value_kind  = 1;
static constexpr int A_PersistencyKeyInitValueElement_value_name  = 0;
static constexpr int A_PersistencyKeyInitValueElement_value_numerical  = 2;
static constexpr int A_PersistencyKeyInitValueElement_value_text  = 3;
// 
static constexpr int N_PersistencyKeyValuePairRedundancyHandling  = 42;
static constexpr int A_PersistencyKeyValuePairRedundancyHandling_crc_algorithmFamily  = 0;
static constexpr int A_PersistencyKeyValuePairRedundancyHandling_crc_length  = 1;
static constexpr int A_PersistencyKeyValuePairRedundancyHandling_kind  = 4;
static constexpr int A_PersistencyKeyValuePairRedundancyHandling_mn_m  = 2;
static constexpr int A_PersistencyKeyValuePairRedundancyHandling_mn_n  = 3;
static constexpr int A_PersistencyKeyValuePairRedundancyHandling_scope  = 5;
// 
static constexpr int N_PersistencyKeyValuePair                = 41;
static constexpr int A_PersistencyKeyValuePair_initValue_kind  = 5;
static constexpr int A_PersistencyKeyValuePair_initValue_name  = 4;
static constexpr int A_PersistencyKeyValuePair_initValue_numerical  = 6;
static constexpr int A_PersistencyKeyValuePair_initValue_text  = 7;
static constexpr int A_PersistencyKeyValuePair_initValue_typeKind  = 3;
static constexpr int A_PersistencyKeyValuePair_initValue_typeName  = 2;
static constexpr int A_PersistencyKeyValuePair_shortName      = 0;
static constexpr int A_PersistencyKeyValuePair_updateStrategy  = 1;
static constexpr int C_PersistencyKeyValuePair_initValue_array  = 0; // childNode[PersistencyKeyInitValueElement]
// 
static constexpr int N_PersistencyKeyValueStorageInterface    = 30;
static constexpr int A_PersistencyKeyValueStorageInterface_minimumSustainedSize  = 1;
static constexpr int A_PersistencyKeyValueStorageInterface_redundancy  = 2;
static constexpr int A_PersistencyKeyValueStorageInterface_shortName  = 0;
static constexpr int A_PersistencyKeyValueStorageInterface_updateStrategy  = 3;
static constexpr int C_PersistencyKeyValueStorageInterface_dataElement  = 0; // childNode[PersistencyDataElement]
// 
static constexpr int N_PersistencyKeyValueStorage             = 40;
static constexpr int A_PersistencyKeyValueStorage_maximumAllowedSize  = 1;
static constexpr int A_PersistencyKeyValueStorage_minimumSustainedSize  = 2;
static constexpr int A_PersistencyKeyValueStorage_shortName   = 0;
static constexpr int A_PersistencyKeyValueStorage_swcl_version  = 6;
static constexpr int A_PersistencyKeyValueStorage_updateStrategy  = 3;
static constexpr int A_PersistencyKeyValueStorage_uri         = 4;
static constexpr int A_PersistencyKeyValueStorage_vrte_kvsMemSize  = 5;
static constexpr int C_PersistencyKeyValueStorage_keyValuePair  = 0; // childNode[PersistencyKeyValuePair]
static constexpr int C_PersistencyKeyValueStorage_redundancyHandling  = 1; // childNode[PersistencyKeyValuePairRedundancyHandling]
// 
static constexpr int N_PersistencyPortPrototypeToFileStorageMapping  = 55;
static constexpr int A_PersistencyPortPrototypeToFileStorageMapping_shortName  = 0;
static constexpr int R_PersistencyPortPrototypeToFileStorageMapping_fileStorage  = 0;
static constexpr int R_PersistencyPortPrototypeToFileStorageMapping_iref  = 2;
static constexpr int R_PersistencyPortPrototypeToFileStorageMapping_process  = 1;
// 
static constexpr int N_PersistencyPortPrototypeToKeyValueStorageMapping  = 45;
static constexpr int A_PersistencyPortPrototypeToKeyValueStorageMapping_shortName  = 0;
static constexpr int R_PersistencyPortPrototypeToKeyValueStorageMapping_iref  = 2;
static constexpr int R_PersistencyPortPrototypeToKeyValueStorageMapping_keyValueStorage  = 0;
static constexpr int R_PersistencyPortPrototypeToKeyValueStorageMapping_process  = 1;
// 
static constexpr int N_PersistencyPortPrototype               = 61;
static constexpr int A_PersistencyPortPrototype_interface_name  = 2;
static constexpr int A_PersistencyPortPrototype_kind          = 0;
static constexpr int A_PersistencyPortPrototype_shortName     = 1;
static constexpr int R_PersistencyPortPrototype_interface_keyValue  = 0;
static constexpr int C_PersistencyPortPrototype_requiredComSpec  = 0; // childNode[PersistencyDataRequiredComSpec]
// 
static constexpr int N_Process                                = 10;
static constexpr int A_Process_shortName                      = 0;
// 
static constexpr int N_ROOT                                   = 0;
static constexpr int C_ROOT_ENUMS                             = 0; // childNode[ENUMS]
static constexpr int C_ROOT_IREFS                             = 1; // childNode[IREFS]
static constexpr int C_ROOT_PersistencyFileStorage            = 8; // childNode[PersistencyFileStorage]
static constexpr int C_ROOT_PersistencyFileStorageInterface   = 5; // childNode[PersistencyFileStorageInterface]
static constexpr int C_ROOT_PersistencyKeyValueStorage        = 6; // childNode[PersistencyKeyValueStorage]
static constexpr int C_ROOT_PersistencyKeyValueStorageInterface  = 4; // childNode[PersistencyKeyValueStorageInterface]
static constexpr int C_ROOT_PersistencyPortPrototype          = 10; // childNode[PersistencyPortPrototype]
static constexpr int C_ROOT_PersistencyPortPrototypeToFileStorageMapping  = 9; // childNode[PersistencyPortPrototypeToFileStorageMapping]
static constexpr int C_ROOT_PersistencyPortPrototypeToKeyValueStorageMapping  = 7; // childNode[PersistencyPortPrototypeToKeyValueStorageMapping]
static constexpr int C_ROOT_Process                           = 3; // childNode[Process]
// 
};
// =========================================================================================================================
// end generated constexpr
// =========================================================================================================================
#endif // ECUCFG_STR_4_0_METADATA_VARIANT
