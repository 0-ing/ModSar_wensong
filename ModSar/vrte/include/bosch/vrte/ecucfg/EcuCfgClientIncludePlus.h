/*********************************************************************
	Rhapsody	: 8.4 
	Login		: mru8si
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: bosch::vrte::ecucfg::IDataNodeModelProxyFactory
//!	Generated Date	: Wed, 18, Mar 2020  
	File Path	: C:\_scratchpad\DefaultConfig\bosch\vrte\ecucfg\EcuCfgClientIncludePlus.h
*********************************************************************/

#ifndef bosch_vrte_ecucfg_EcuCfgClientIncludePlus_H
#define bosch_vrte_ecucfg_EcuCfgClientIncludePlus_H

#include "bosch/vrte/ecucfg/EcuCfgClientInclude.h"
#include <cstddef>

namespace bosch
{
namespace vrte
{
namespace ecucfg
{
//## operation reserveDataNodeModel(char*)
class IDataNodeModel;

//## operation reserveDataNodeModelProxyFactory(char*)
class IDataNodeModelProxyFactory;

//## operation reserveEmptyDataNodeModel(char*)
class LDataNodeCursor;

//## operation reserveEmptyDataNodeStructureModel(char*)
class LDataNodeStructureModel;

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class IDataNodeModelProxyFactory
// DataNodeModelProxyFactory is the entry point for any client-access to ECUCFG data.
//
// @version IDataNodeModelProxyFactory_MAJOR 1
// @version IDataNodeModelProxyFactory_MINOR 0
class IDataNodeModelProxyFactory
{
    ////    Operations    ////

public:
    //## operation getInstanceName() const
    virtual const char* getInstanceName() const = 0;

    // first release all (eventually) contained items,
    // then release current item.
    //
    // This replaces the usage of delete operation (the destructor will be used implicitly at  - and only at - destroy objectRepository)
    //
    // return value false indicates that something went wrong at release. In this case some memory leaks happened.
    // No further problems to be expected (in any case, after ptr->release...(); the ptr shall not be used anymore).
    //## operation releaseDataNodeModelProxyFactory()
    virtual bool releaseDataNodeModelProxyFactory() = 0;

    // DataNodeModelProxyFactory.reserveDataNodeModel() is the entry point for a concrete client-access to ECUCFG data.
    // Return value is a pointer to IDataNodeModel as entry point to the related ECUCFG data.
    // Returns 0 in case of errors.
    //
    // Currently the client has to identify itself via argument p_functionClusterName.
    // The ECUCFG instance is specified in the calling DataNodeModelProxyFactory object
    //## operation reserveDataNodeModel(char*)
    // In this case, the default usecase is the daemon 
    virtual IDataNodeModel* reserveDataNodeModel(const char* p_functionClusterName) = 0;

    // DataNodeModelProxyFactory.reserveDataNodeModel() is the entry point for a concrete client-access to ECUCFG data.
    // Return value is a pointer to IDataNodeModel as entry point to the related ECUCFG data.
    // Returns 0 in case of errors.
    //
    // Currently the client has to identify itself via argument p_functionClusterName.
    // The ECUCFG instance is specified in the calling DataNodeModelProxyFactory object
    //## operation reserveDataNodeModel(char*, IEcuCfgEnums::operationMode)
    //  Valid and Invalid usages:
    //      FC -> argument given as daemon (called in Executable A) -> proper usage
    //      FC -> argument given as library (called in Executable A) -> improper usage
    //      FC -> argument given as daemon (called in Library A) -> improper usage
    //      FC -> argument given as library (called in Library B) -> (In process space of Executable B) -> proper usage
    virtual IDataNodeModel* reserveDataNodeModel(const char* p_functionClusterName, IEcuCfgEnums::operationMode opMode) = 0;
    
    // DataNodeModelProxyFactory.reserveEmptyDataNodeModel() is the entry point for loaders.
    // Return value is a pointer to LDataNodeCursor that can be used to fill the model..
    // Returns 0 in case of errors.
    //
    // Currently the client has to identify itself via argument p_functionClusterName.
    // The ECUCFG instance is specified in the calling DataNodeModelProxyFactory object
    //
    // scope: use cases that do not load ecufg files
    //## operation reserveEmptyDataNodeModel(char*)
    virtual LDataNodeCursor* reserveEmptyDataNodeModel(const char* p_functionClusterName) = 0;

    // DataNodeModelProxyFactory.reserveEmptyDataNodeStructureModel() supports DataNodeModelProxyFactory.reserveEmptyDataNodeModel()
    //
    // scope: use cases that do not load ecufg files
    //
    //## operation reserveEmptyDataNodeStructureModel(char*)
    virtual LDataNodeStructureModel* reserveEmptyDataNodeStructureModel(const char* p_functionClusterName) = 0;

    // change the sub folder name.
    //
    // Naming of ecucfg files for content type "Data" is
    // <applicableRootFolder><applicableDataFolder><function cluster name><applicableDataSuffix>
    //## operation setApplicableDataFolder(char*)
    virtual void setApplicableDataFolder(const char* p_folder) = 0;

    // change the suffix.
    //
    // Naming of ecucfg files for content type "Data" is
    // <applicableRootFolder><applicableDataFolder><function cluster name><applicableDataSuffix>
    //## operation setApplicableDataSuffix(char*)
    virtual void setApplicableDataSuffix(const char* p_suffix) = 0;

    // change the root folder name.
    //
    //Root folder path can be changed in two ways. One is setting an environment variable. Other is using setApplicableRootFolder
    // Addtional hints for setting environment variable mentioned in below comments.
    // command to set the variable is ex:  export ECUCFG_ENV_VAR_ROOTFOLDER="/opt/vrte/share/test/ecucfg-aap-ecu-configuration/"
    // command to unset the variable is ex: unset ECUCFG_ENV_VAR_ROOTFOLDER
    // command to see all environment variables is :  env
    //
    // Naming of ecucfg files for content type "Data" is
    // <applicableRootFolder><applicableDataFolder><function cluster name><applicableDataSuffix>
    //
    // Naming of ecucfg files for content type "Structure" is
    // <applicableRootFolder><applicableStructureFolder><function cluster name><applicableStructureSuffix>
    //## operation setApplicableRootFolder(char*)

    virtual void setApplicableRootFolder(const char* p_folder) = 0;

    // change the sub folder name.
    //
    // Naming of ecucfg files for content type "Structure" is
    // <applicableRootFolder><applicableStructureFolder><function cluster name><applicableStructureSuffix>
    //## operation setApplicableStructureFolder(char*)
    virtual void setApplicableStructureFolder(const char* p_folder) = 0;

    // change the suffix.
    //
    // Naming of ecucfg files for content type "Structure" is
    // <applicableRootFolder><applicableStructureFolder><function cluster name><applicableStructureSuffix>
    //## operation setApplicableStructureSuffix(char*)
    virtual void setApplicableStructureSuffix(const char* p_suffix) = 0;
};

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class LDataNodeCursor
// API available for cursors in load data node content use cases
//
// @version LDataNodeCursor_MAJOR 1
// @version LDataNodeCursor_MINOR 0
class LDataNodeCursor
{
    ////    Operations    ////

public:
    // Move cursor to a child node.
    // Create the child node if not yet existing.
    // Returns true  in case of success.
    //
    // for p_indexNodeContainer
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::C_<node name>_<container name>
    //## operation addOrResumeChildNode(int,char*)
    virtual bool addOrResumeChildNode(int p_indexNodeContainer, const char* p_contextKey) = 0;

    // get the data node model hosting the cursor
    //## operation getDataNodeModel() const
    virtual IDataNodeModel* getDataNodeModel() const = 0;

    // move cursor to the parent node (if root is reached cursor stays at root).
    // Returns true in case of succes.
    //## operation leaveNodeInLoader()
    virtual bool leaveNodeInLoader() = 0;

    // delete a cursor.
    // if this is not done the cursor will be deleted later along with the model.
    //## operation releaseDataNodeCursorInLoader()
    virtual bool releaseDataNodeCursorInLoader() = 0;

    // create a copy of current cursor.
    // Returns
    // - pointer to the newly created cursor in case of success.
    // - 0 if something went wrong.
    //## operation reserveDataNodeCursorInLoader()
    virtual LDataNodeCursor* reserveDataNodeCursorInLoader() = 0;

    // set/update the value for an association.
    // Returns true in case of success.
    // for p_indexAssociation
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::R_<node name>_<association name>
    //## operation setAssociationTarget(int,char*)
    virtual bool setAssociationTarget(int p_indexAssociation, const char* p_targetKey) = 0;

    // set/update the value for an attribute
    // Returns true in case of success.
    // for p_indexAttribute
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::A_<node name>_<attribute name>
    //## operation setAttributeValue(int,char*)
    virtual bool setAttributeValue(int p_indexAttribute, const char* p_value) = 0;

    // currently this has no effect.
    // May be used later to control overwrite behavior at load data,
    //## operation setUpdateBahavior(int)
    virtual bool setUpdateBahavior(int p_updateBehavior) = 0;
};

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class LDataNodeStructureModel
// API available for load data node structure use cases
//
// @version LDataNodeStructureModel_MAJOR 1
// @version LDataNodeStructureModel_MINOR 0
class LDataNodeStructureModel
{
    ////    Operations    ////

public:
    // Add association details as retrieved from serialized data sources (Json).
    // Arguments are typed as serialized.
    //## operation addDataNodeAssociationStructure2CurrentNode(int,char*,int,char*,char*)
    virtual bool addDataNodeAssociationStructure2CurrentNode(int p_index, const char* p_name, int p_associatedNodeIndex, const char* p_processingHints, const char* p_remarks) = 0;

    // Add attribute details as retrieved from serialized data sources (Json).
    // Arguments are typed as serialized.
    // Special case is argument: const char* _ruleValueKind
    // - This argument comes as C-string but will be converted to a literal of RuleValueKindEnum.
    // - if empty default to enum literal TEXT
    //## operation addDataNodeAttributeStructure2CurrentNode(int,char*,char*,char*,char*)
    virtual bool addDataNodeAttributeStructure2CurrentNode(int p_index, const char* p_name, const char* p_ruleValueKind, const char* p_processingHints, const char* p_remarks) = 0;

    // Add (sub) container details as retrieved from serialized data sources (Json).
    // Arguments are typed as serialized.
    //## operation addDataNodeContainerStructure2CurrentNode(int,char*,int,char*,char*)
    virtual bool addDataNodeContainerStructure2CurrentNode(int p_index, const char* p_name, int p_childNodeIndex, const char* p_processingHints, const char* p_remarks) = 0;

    // Add attribute details as retrieved from serialized data sources (Json).
    // Arguments are typed as serialized.
    // Special case is argument const char* _ruleContextKey:
    // - This argument comes as C-string but will be converted to a literal of RuleContextKeyEnum
    // - if empty default to enum literal UNDEFINED
    //## operation addDataNodeStructure(int,char*,char*,char*,char*)
    virtual bool addDataNodeStructure(int p_index, const char* p_name, const char* p_ruleContextKey, const char* p_processingHints, const char* p_remarks) = 0;

    // After loading of data node structure content is completed this operation needs to be called.
    // (finalize = complete the model by resolving all references required to make the model operational)
    //## operation finalizeDataNodeStructureModel()
    virtual bool finalizeDataNodeStructureModel() = 0;

    // Indicates that the DataNodeStructureModel has no content, i.e. is not yet loaded or filled.
    // (for usage in use cases where the standard json loaders are not applicable)
    //## operation isEmpty()
    virtual bool isEmpty() = 0;

    // first release all (eventually) contained items,
    // then release current item.
    //## operation releaseDataNodeStructureModel()
    virtual bool releaseDataNodeStructureModel() = 0;

    // set the DataNodeStructureModel member variables
    // (for usage in use cases where the standard json loaders are not applicable)
    // only allowed if isEmpty()==true,
    // returns false if this is not the case or arguments are empty or name is clashing.
    //## operation setParameters(char*,int,int,char*)
    virtual bool setParameters(const char* p_name, int p_majorVersion, int p_minorVersion, const char* p_remarks) = 0;
};

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class DataNodeModelProxyFactoryProvider
// DataNodeModelProxyFactoryProvider is a wrapper for easy client access to DataNodeModelProxyFactory.reserveDataNodeModelProxyFactory().
//
// Client gets a pointer to IDataNodeModelProxyFactory
// and can use this abstract interface to configure/use the underlying model manager
class DataNodeModelProxyFactoryProvider
{
    ////    Constructors and destructors    ////

protected:
    //## operation DataNodeModelProxyFactoryProvider()
    DataNodeModelProxyFactoryProvider();

    //## operation ~DataNodeModelProxyFactoryProvider()
    virtual ~DataNodeModelProxyFactoryProvider();

    ////    Operations    ////

public:
    // DataNodeModelProxyFactory.reserveDataNodeModelProxyFactory() is the entry point for a concrete client-access to ECUCFG instance.
    // Return value is a pointer to IDataNodeModelProxyFactory as entry point to the related ECUCFG data.
    // Returns 0 in case of errors.
    //
    // Currently the client has to (optionally) identify the ECUCFG instance via p_ecucfgInstanceName.
    // Fallback is the default-EcuCfgModelManager.
    //
    //## operation reserveDataNodeModelProxyFactory(char*)
    static IDataNodeModelProxyFactory* reserveDataNodeModelProxyFactory(const char* p_ecucfgInstanceName = 0, size_t initialSizeInkB = 128);
};
}
}
}

#endif
/*********************************************************************
	File Path	: C:\_scratchpad\DefaultConfig\bosch\vrte\ecucfg\EcuCfgClientIncludePlus.h
*********************************************************************/
