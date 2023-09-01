#ifndef ECUCFG_STR_2_1_METADATA_VARIANT
// =========================================================================================================================
// generated for STR at 2020-08-28 13:03:52
//
// begin generated constexpr:
// =========================================================================================================================
#define ECUCFG_STR_2_1_METADATA_VARIANT "THIS IS THE INCLUDE-GUARD"
#ifndef ECUCFG_STR_METADATA_NAME
#define ECUCFG_STR_METADATA_NAME "STR"
#endif
//
class STR_constexpr
{
public:
    static constexpr int majorVersion = 2; // consolidated
    static constexpr int minorVersion = 1;
    //
    static constexpr int N_ENUMS = 2;       // ENUMS are defined in AUTOSAR Meta Model. / To be decided: how are ENUMs handled. Directly use the literal or refer to it ?
    static constexpr int A_ENUMS_dummy = 0; // no specific attributes for ENUMS container
    static constexpr int C_ENUMS_ENUM = 0;
    //
    static constexpr int N_ENUM = 3;       // e.g. CommandlinOptionKindEnum, SchedulingPolicyKindEnum
    static constexpr int A_ENUM_dummy = 0; // no specific attributes for the invidual ENUM container
    static constexpr int C_ENUM_LITERAL = 0;
    //
    static constexpr int N_IREF4FileProxyPortPrototypeOWNERS = 57;
    static constexpr int R_IREF4FileProxyPortPrototypeOWNERS_irefOwner = 0; // targetNode[PersistencyPortPrototypeToFileArrayMapping]
    //
    static constexpr int N_IREF4FileProxyPortPrototype = 56;
    static constexpr int A_IREF4FileProxyPortPrototype_base = 1;                            // this is the ARPath of the Executable
    static constexpr int A_IREF4FileProxyPortPrototype_contextRootSwComponentPrototype = 3; // this is the shortName of the root SWC prototype
    static constexpr int A_IREF4FileProxyPortPrototype_fileArray_shortName = 5;
    static constexpr int A_IREF4FileProxyPortPrototype_fileArray_uri = 6;
    static constexpr int A_IREF4FileProxyPortPrototype_interface_kind = 2; // supported values: PersistencyFileProxyInterface
    static constexpr int A_IREF4FileProxyPortPrototype_port_shortName = 4;
    static constexpr int A_IREF4FileProxyPortPrototype_processShortName = 0;
    static constexpr int A_IREF4FileProxyPortPrototype_vrte_portIdentifier = 7;       // VRTE manifest extension: attribute 'portIdentifier'
    static constexpr int R_IREF4FileProxyPortPrototype_process = 0;                   // targetNode[Process]
    static constexpr int R_IREF4FileProxyPortPrototype_providedInterface = 1;         // targetNode[PersistencyFileProxyInterface] either provided, required or providedRequired reference is set
    static constexpr int R_IREF4FileProxyPortPrototype_providedRequiredInterface = 2; // targetNode[PersistencyFileProxyInterface] either provided, required or providedRequired reference is set
    static constexpr int R_IREF4FileProxyPortPrototype_requiredInterface = 3;         // targetNode[PersistencyFileProxyInterface] either provided, required or providedRequired reference is set
    static constexpr int C_IREF4FileProxyPortPrototype_OWNERS = 0;
    //
    static constexpr int N_IREF4KeyValueDatabasePortPrototypeOWNERS = 47;
    static constexpr int R_IREF4KeyValueDatabasePortPrototypeOWNERS_irefOwner = 0; // targetNode[PersistencyPortPrototypeToKeyValueDatabaseMapping]
    //
    static constexpr int N_IREF4KeyValueDatabasePortPrototype = 46;
    static constexpr int A_IREF4KeyValueDatabasePortPrototype_base = 1;                            // this is the ARPath of the Executable
    static constexpr int A_IREF4KeyValueDatabasePortPrototype_contextRootSwComponentPrototype = 3; // this is the shortName of the root SWC prototype
    static constexpr int A_IREF4KeyValueDatabasePortPrototype_interface_kind = 2;                  // supported values: PersistencyKeyValueDatabaseInterface
    static constexpr int A_IREF4KeyValueDatabasePortPrototype_interface_name = 9;
    static constexpr int A_IREF4KeyValueDatabasePortPrototype_keyValueStorage_shortName = 5;
    static constexpr int A_IREF4KeyValueDatabasePortPrototype_keyValueStorage_uri = 6;
    static constexpr int A_IREF4KeyValueDatabasePortPrototype_port_kind = 8; // possible values: PPortPrototype, PRPortPrototype, RPortPrototype
    static constexpr int A_IREF4KeyValueDatabasePortPrototype_port_shortName = 4;
    static constexpr int A_IREF4KeyValueDatabasePortPrototype_processShortName = 0;
    static constexpr int A_IREF4KeyValueDatabasePortPrototype_vrte_portIdentifier = 7;       // VRTE manifest extension: attribute 'portIdentifier'
    static constexpr int R_IREF4KeyValueDatabasePortPrototype_interface = 5;                 // targetNode[PersistencyKeyValueDatabaseInterface] replaces references providedInterface + providedRequiredInterface + requiredInterface
    static constexpr int R_IREF4KeyValueDatabasePortPrototype_port = 4;                      // targetNode[PersistencyPortPrototype]
    static constexpr int R_IREF4KeyValueDatabasePortPrototype_process = 0;                   // targetNode[Process]
    static constexpr int R_IREF4KeyValueDatabasePortPrototype_providedInterface = 1;         // targetNode[PersistencyKeyValueDatabaseInterface] either provided, required or providedRequired reference is set
    static constexpr int R_IREF4KeyValueDatabasePortPrototype_providedRequiredInterface = 2; // targetNode[PersistencyKeyValueDatabaseInterface] either provided, required or providedRequired reference is set
    static constexpr int R_IREF4KeyValueDatabasePortPrototype_requiredInterface = 3;         // targetNode[PersistencyKeyValueDatabaseInterface] either provided, required or providedRequired reference is set
    static constexpr int C_IREF4KeyValueDatabasePortPrototype_OWNERS = 0;
    //
    static constexpr int N_IREFS = 5;
    static constexpr int A_IREFS_dummy = 0; // no specific attributes for IREFS container
    static constexpr int C_IREFS_IREF4FileProxyPortPrototype = 1;
    static constexpr int C_IREFS_IREF4KeyValueDatabasePortPrototype = 0;
    //
    static constexpr int N_LITERAL = 4;       // list of literals in ENUM
    static constexpr int A_LITERAL_value = 0; // provide ENUM value per LITERAL
    //
    static constexpr int N_PersistencyDataElement = 31;
    static constexpr int A_PersistencyDataElement_shortName = 0;
    static constexpr int A_PersistencyDataElement_typeKind = 2;
    static constexpr int A_PersistencyDataElement_typeName = 3;
    static constexpr int A_PersistencyDataElement_updateStrategy = 1; // literal as string
    //
    static constexpr int N_PersistencyDataProvidedComSpec = 62;
    static constexpr int A_PersistencyDataProvidedComSpec_initValue_kind = 1; // supported values: ArrayValueSpecification, NumericalValueSpecification, TextValueSpecification
    static constexpr int A_PersistencyDataProvidedComSpec_initValue_name = 0;
    static constexpr int A_PersistencyDataProvidedComSpec_initValue_numerical = 2;
    static constexpr int A_PersistencyDataProvidedComSpec_initValue_text = 3;
    static constexpr int R_PersistencyDataProvidedComSpec_dataElement = 0; // targetNode[PersistencyDataElement]
    static constexpr int C_PersistencyDataProvidedComSpec_initValue_array = 0;
    //
    static constexpr int N_PersistencyDataProvidedInitValueElement = 63;
    static constexpr int A_PersistencyDataProvidedInitValueElement_value_kind = 1; // supported values: NumericalValueSpecification, TextValueSpecification
    static constexpr int A_PersistencyDataProvidedInitValueElement_value_name = 0;
    static constexpr int A_PersistencyDataProvidedInitValueElement_value_numerical = 2;
    static constexpr int A_PersistencyDataProvidedInitValueElement_value_text = 3;
    //
    static constexpr int N_PersistencyDataRequiredComSpec = 64;
    static constexpr int A_PersistencyDataRequiredComSpec_initValue_kind = 1; // supported values: ArrayValueSpecification, NumericalValueSpecification, TextValueSpecification
    static constexpr int A_PersistencyDataRequiredComSpec_initValue_name = 0;
    static constexpr int A_PersistencyDataRequiredComSpec_initValue_numerical = 2;
    static constexpr int A_PersistencyDataRequiredComSpec_initValue_text = 3;
    static constexpr int R_PersistencyDataRequiredComSpec_dataElement = 0; // targetNode[PersistencyDataElement]
    static constexpr int C_PersistencyDataRequiredComSpec_initValue_array = 0;
    //
    static constexpr int N_PersistencyDataRequiredInitValueElement = 65;
    static constexpr int A_PersistencyDataRequiredInitValueElement_value_kind = 1; // supported values: NumericalValueSpecification, TextValueSpecification
    static constexpr int A_PersistencyDataRequiredInitValueElement_value_name = 0;
    static constexpr int A_PersistencyDataRequiredInitValueElement_value_numerical = 2;
    static constexpr int A_PersistencyDataRequiredInitValueElement_value_text = 3;
    //
    static constexpr int N_PersistencyFileArrayRedundancyHandling = 52;
    static constexpr int A_PersistencyFileArrayRedundancyHandling_crc_algorithmFamily = 0;
    static constexpr int A_PersistencyFileArrayRedundancyHandling_crc_length = 1;
    static constexpr int A_PersistencyFileArrayRedundancyHandling_kind = 4; // type is one of PersistencyRedundancyCrc, PersistencyRedundancyMOutOfN
    static constexpr int A_PersistencyFileArrayRedundancyHandling_mn_m = 2;
    static constexpr int A_PersistencyFileArrayRedundancyHandling_mn_n = 3;
    static constexpr int A_PersistencyFileArrayRedundancyHandling_scope = 5; // literal as string
    //
    static constexpr int N_PersistencyFileArray = 50;
    static constexpr int A_PersistencyFileArray_maximumAllowedSize = 1;
    static constexpr int A_PersistencyFileArray_minimumSustainedSize = 2;
    static constexpr int A_PersistencyFileArray_shortName = 0;
    static constexpr int A_PersistencyFileArray_updateStrategy = 3; // literal as string
    static constexpr int A_PersistencyFileArray_uri = 4;
    static constexpr int C_PersistencyFileArray_file = 0;
    static constexpr int C_PersistencyFileArray_redundancyHandling = 1; // envelope: PersistencyRedundancyCrc + PersistencyRedundancyMOutOfN
    //
    static constexpr int N_PersistencyFileProxyInterface = 35;
    static constexpr int A_PersistencyFileProxyInterface_encoding = 4;
    static constexpr int A_PersistencyFileProxyInterface_maxNumberOfFiles = 5;
    static constexpr int A_PersistencyFileProxyInterface_minimumSustainedSize = 1;
    static constexpr int A_PersistencyFileProxyInterface_redundancy = 2; // literal as string
    static constexpr int A_PersistencyFileProxyInterface_shortName = 0;
    static constexpr int A_PersistencyFileProxyInterface_updateStrategy = 3; // literal as string
    static constexpr int C_PersistencyFileProxyInterface_fileProxy = 0;
    //
    static constexpr int N_PersistencyFileProxy = 36;
    static constexpr int A_PersistencyFileProxy_contentUri = 1;
    static constexpr int A_PersistencyFileProxy_fileName = 2;
    static constexpr int A_PersistencyFileProxy_shortName = 0;
    static constexpr int A_PersistencyFileProxy_updateStrategy = 3; // literal as string
    //
    static constexpr int N_PersistencyFile = 51;
    static constexpr int A_PersistencyFile_contentUri = 1;
    static constexpr int A_PersistencyFile_fileName = 2;
    static constexpr int A_PersistencyFile_shortName = 0;
    static constexpr int A_PersistencyFile_updateStrategy = 3; // literal as string
    //
    static constexpr int N_PersistencyKeyInitValueElement = 44;
    static constexpr int A_PersistencyKeyInitValueElement_value_kind = 1; // supported values: NumericalValueSpecification, TextValueSpecification
    static constexpr int A_PersistencyKeyInitValueElement_value_name = 0;
    static constexpr int A_PersistencyKeyInitValueElement_value_numerical = 2;
    static constexpr int A_PersistencyKeyInitValueElement_value_text = 3;
    //
    static constexpr int N_PersistencyKeyValueDatabaseInterface = 30;
    static constexpr int A_PersistencyKeyValueDatabaseInterface_minimumSustainedSize = 1;
    static constexpr int A_PersistencyKeyValueDatabaseInterface_redundancy = 2; // literal as string
    static constexpr int A_PersistencyKeyValueDatabaseInterface_shortName = 0;
    static constexpr int A_PersistencyKeyValueDatabaseInterface_updateStrategy = 3; // literal as string
    static constexpr int C_PersistencyKeyValueDatabaseInterface_dataElement = 0;
    //
    static constexpr int N_PersistencyKeyValueDatabase = 40;
    static constexpr int A_PersistencyKeyValueDatabase_maximumAllowedSize = 1;
    static constexpr int A_PersistencyKeyValueDatabase_minimumSustainedSize = 2;
    static constexpr int A_PersistencyKeyValueDatabase_shortName = 0;
    static constexpr int A_PersistencyKeyValueDatabase_updateStrategy = 3; // literal as string
    static constexpr int A_PersistencyKeyValueDatabase_uri = 4;
    static constexpr int A_PersistencyKeyValueDatabase_vrte_kvsMemSize = 5; // VRTE manifest extension: attribute 'kvsMemSize'
    static constexpr int C_PersistencyKeyValueDatabase_keyValuePair = 0;
    static constexpr int C_PersistencyKeyValueDatabase_redundancyHandling = 1; // envelope: PersistencyRedundancyCrc + PersistencyRedundancyMOutOfN
    //
    static constexpr int N_PersistencyKeyValuePairRedundancyHandling = 42;
    static constexpr int A_PersistencyKeyValuePairRedundancyHandling_crc_algorithmFamily = 0;
    static constexpr int A_PersistencyKeyValuePairRedundancyHandling_crc_length = 1;
    static constexpr int A_PersistencyKeyValuePairRedundancyHandling_kind = 4; // possible values: PersistencyRedundancyCrc, PersistencyRedundancyMOutOfN
    static constexpr int A_PersistencyKeyValuePairRedundancyHandling_mn_m = 2;
    static constexpr int A_PersistencyKeyValuePairRedundancyHandling_mn_n = 3;
    static constexpr int A_PersistencyKeyValuePairRedundancyHandling_scope = 5; // literal as string
    //
    static constexpr int N_PersistencyKeyValuePair = 41;
    static constexpr int A_PersistencyKeyValuePair_initValue_kind = 5; // supported values: ArrayValueSpecification, NumericalValueSpecification, TextValueSpecification
    static constexpr int A_PersistencyKeyValuePair_initValue_name = 4;
    static constexpr int A_PersistencyKeyValuePair_initValue_numerical = 6;
    static constexpr int A_PersistencyKeyValuePair_initValue_text = 7;
    static constexpr int A_PersistencyKeyValuePair_initValue_typeKind = 3;
    static constexpr int A_PersistencyKeyValuePair_initValue_typeName = 2;
    static constexpr int A_PersistencyKeyValuePair_shortName = 0;
    static constexpr int A_PersistencyKeyValuePair_updateStrategy = 1; // literal as string
    static constexpr int C_PersistencyKeyValuePair_initValue_array = 0;
    //
    static constexpr int N_PersistencyPortPrototypeToFileArrayMapping = 55;
    static constexpr int A_PersistencyPortPrototypeToFileArrayMapping_shortName = 0;
    static constexpr int R_PersistencyPortPrototypeToFileArrayMapping_iref = 2;                 // targetNode[IREF4FileProxyPortPrototype]
    static constexpr int R_PersistencyPortPrototypeToFileArrayMapping_persistencyFileArray = 0; // targetNode[PersistencyFileArray]
    static constexpr int R_PersistencyPortPrototypeToFileArrayMapping_process = 1;              // targetNode[Process]
    //
    static constexpr int N_PersistencyPortPrototypeToKeyValueDatabaseMapping = 45;
    static constexpr int A_PersistencyPortPrototypeToKeyValueDatabaseMapping_shortName = 0;
    static constexpr int R_PersistencyPortPrototypeToKeyValueDatabaseMapping_iref = 2;            // targetNode[IREF4KeyValueDatabasePortPrototype]
    static constexpr int R_PersistencyPortPrototypeToKeyValueDatabaseMapping_keyValueStorage = 0; // targetNode[PersistencyKeyValueDatabase]
    static constexpr int R_PersistencyPortPrototypeToKeyValueDatabaseMapping_process = 1;         // targetNode[Process]
    //
    static constexpr int N_PersistencyPortPrototype = 61; // restricted to SWC.ports in scope
    static constexpr int A_PersistencyPortPrototype_interface_name = 2;
    static constexpr int A_PersistencyPortPrototype_kind = 0; // possible values: PPortPrototype, PRPortPrototype, RPortPrototype
    static constexpr int A_PersistencyPortPrototype_shortName = 1;
    static constexpr int R_PersistencyPortPrototype_interface_keyValue = 0; // targetNode[PersistencyKeyValueDatabaseInterface]
    static constexpr int C_PersistencyPortPrototype_providedComSpec = 0;
    static constexpr int C_PersistencyPortPrototype_requiredComSpec = 1;
    //
    static constexpr int N_Process = 10;
    static constexpr int A_Process_shortName = 0;
    //
    static constexpr int N_ROOT = 0;       // ROOT Structure NOT TO BE CHANGED !
    static constexpr int A_ROOT_name = 0;  // ROOT Structure NOT TO BE CHANGED !
    static constexpr int C_ROOT_ENUMS = 1; // ENUMS container
    static constexpr int C_ROOT_IREFS = 2; // IREFS container
    static constexpr int C_ROOT_PersistencyFileArray = 8;
    static constexpr int C_ROOT_PersistencyFileProxyInterface = 5;
    static constexpr int C_ROOT_PersistencyKeyValueDatabase = 6;
    static constexpr int C_ROOT_PersistencyKeyValueDatabaseInterface = 4;
    static constexpr int C_ROOT_PersistencyPortPrototype = 10; // All SWC.ports in scope for STR
    static constexpr int C_ROOT_PersistencyPortPrototypeToFileArrayMapping = 9;
    static constexpr int C_ROOT_PersistencyPortPrototypeToKeyValueDatabaseMapping = 7;
    static constexpr int C_ROOT_Process = 3;
    static constexpr int C_ROOT_UNUSED = 0; // UNUSED container allows to keep nodeIndex sequence if nodes are disabled.
    //
    static constexpr int N_UNUSED = 1;       // UNUSED container allows to keep nodeIndex sequence if nodes are disabled.
    static constexpr int A_UNUSED_dummy = 0; // no specific attributes for UNUSED container
    //
};
// =========================================================================================================================
// end generated constexpr
// =========================================================================================================================
#endif // ECUCFG_STR_2_1_METADATA_VARIANT
