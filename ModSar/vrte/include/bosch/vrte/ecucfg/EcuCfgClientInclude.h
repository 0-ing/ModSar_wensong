/*********************************************************************
	Rhapsody	: 8.4 
	Login		: mru8si
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: bosch::vrte::ecucfg::IDataNode
//!	Generated Date	: Wed, 18, Mar 2020  
	File Path	: C:\_scratchpad\DefaultConfig\bosch\vrte\ecucfg\EcuCfgClientInclude.h
*********************************************************************/

#ifndef bosch_vrte_ecucfg_EcuCfgClientInclude_H
#define bosch_vrte_ecucfg_EcuCfgClientInclude_H

namespace bosch
{
namespace vrte
{
namespace ecucfg
{
//## operation getTargetNode() const
class IDataNode;

//## operation getAssociation(int) const
class IDataNodeAssociation;

//## operation getDataNodeAssociationStructure() const
class IDataNodeAssociationStructure;

//## operation getAttribute(int) const
class IDataNodeAttribute;

//## operation getDataNodeAttributeStructure() const
class IDataNodeAttributeStructure;

//## operation getContainer(int) const
class IDataNodeContainer;

//## operation getDataNodeContainerStructure() const
class IDataNodeContainerStructure;

//## operation reserveDataNodeCursor()
class IDataNodeCursor;

//## operation getDataNodeStructure() const
class IDataNodeStructure;

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class IDataNode

//#[ ignore
class IEcuCfgEnums;
// class IEcuCfgEnums enum RuleContextKeyEnum;
//#]
//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class IEcuCfgEnums
// EcuCfgEnums provides the enums available for ECUCFG.
// This includes utilities for string conversion of enums.
//
// @version IEcuCfgEnums_MAJOR 1
// @version IEcuCfgEnums_MINOR 0
class IEcuCfgEnums
{
public:
    // ValueIndicatorEnum requests a value handling with a ValueIndicatorEnum-attribute.
    //## type ValueIndicatorEnum
    enum ValueIndicatorEnum
    {
        UNDEF = 0,             // Attribute/Association is not (yet) set.
        ERRONEOUS = 1,         // Attribute/Association has a value that is considered as buggy
        VALID = 2,             // Attribute/Association has a value that is considered as valid
        UNRESOLVED = 3,        // Association has a target-key value that is not yet resolved
        POSITIVE_INFINITE = 4, // real value INF detected
        NEGATIVE_INFINITE = 5, // real value -INF detected
        NOT_A_NUMBER = 6,      // real value NaN or erroneous number format detected
        IS_INT = 7,            // int value detected
        IS_REAL = 8            // real value detected
    };

    // RuleContextKeyEnum specifies the available patterns for context-key handling in data nodes.
    //## type RuleContextKeyEnum
    enum RuleContextKeyEnum
    {
        UNDEFINED = 0, // No rule defined to build the DataNode.contextKey.
        ARPATH = 1,    // DataNode.contextKey is a fully qualified AUTOSAR short name
        STRUCTURE = 5, // DataNode.contextKey is the container name from structural description
        SHORTNAME = 4, // DataNode.contextKey is the Identifiable.shortName (unambiguous in parent context)
        INDEX = 2,     // DataNode.contextKey represents an entry in an array
        IREF = 3,      // DataNode.contextKey is the short-key of an AUTOSAR instance reference representing the (optionally process specific) path from IREF base to target
        ENUM = 6,      // DataNode.contextKey is an ENUM name. Associations to an ENUM have ENUM=<ENUM name> in  processingHints
        ATTRIBUTE = 7  // DataNode.contextKey is an attribute name (in an non-Identifiable) which is specified with ATTRIBUTE=<Attribute-Name> in processingHints.
    };

    // RuleValueKindEnum specifies the base types applicable for attribute values
    //## type RuleValueKindEnum
    enum RuleValueKindEnum
    {
        TEXT = 0,     // any textual value (matching type is TString)
        BOOL = 1,     // any boolean value
        INT = 2,      // any whole number (matchin type is Tint)
        NUMERICAL = 3 // any number
    };

    // operationMode specifies the mode in which the Ecucfg is accessed by the client
    enum operationMode
    {
        library = 0, // ECUCFG is accessed from a library
        daemon = 1   // ECUCFG is accessed from an executable
    };

    // nodeDataPattern specifies the patterns which are supported for loading ecucfg files
    enum nodeDataPattern
    {
        // ECUCFG is accessed from an executable and the *.ecucfg files have partition information
        daemon_partition_nodeData = 0, 
        // ECUCFG is accessed from an executable
        daemon_nodeData = 1,           
        // ECUCFG is accessed from a library and the *.ecucfg files have partition information
        library_partition_nodeData = 2, 
        // ECUCFG is accessed from a library
        library_nodeData = 3,
        // The file FC_nodeData.ecucfg will be loaded which is currently supported. 
        // This will be depricated in future
        _nodeData = 4
    };
};

// Interface for client access to a concrete data node.
//
// This includes access to the data node details for attributes, associations and (child) containers.
//
// @version IDataNode_MAJOR 1
// @version IDataNode_MINOR 0
class IDataNode
{
    ////    Operations    ////

public:
    // flags existence of an association.
    // for p_associationIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::R_<node name>_<association name>
    //## operation associationExists(int) const
    virtual bool associationExists(int p_associationIndex) const = 0;

    // flags validity of an association.
    // considering not existing associations and undefined or unresolvable targets as invalid.
    // for p_associationIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::R_<node name>_<association name>
    //## operation associationIsValid(int) const
    virtual bool associationIsValid(int p_associationIndex) const = 0;

    // flags existence of an attribute
    // for p_attributeIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::A_<node name>_<attribute name>
    //## operation attributeExists(int) const
    virtual bool attributeExists(int p_attributeIndex) const = 0;

    // flags emptiness of a value.
    // considering not existing attributes and undefined values as empty.
    // for p_attributeIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::A_<node name>_<attribute name>
    //## operation attributeIsEmpty(int) const
    virtual bool attributeIsEmpty(int p_attributeIndex) const = 0;

    // flags integer value.
    // considering not existing attributes and undefined values as non-integer.
    // for p_attributeIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::A_<node name>_<attribute name>
    // deprecated:
    // use getAttributeNumericalValueIndicator(p_attributeIndex) instead.
    //## operation attributeIsInt(int) const
    virtual bool attributeIsInt(int p_attributeIndex) const = 0;

    // flags validity of a value.
    // considering not existing attributes and undefined values as invalid.
    // for p_attributeIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::A_<node name>_<attribute name>
    //## operation attributeIsValid(int) const
    virtual bool attributeIsValid(int p_attributeIndex) const = 0;

    // returns the number of child nodes currently hosted by the indicated container.
    // returns 0 if indicated container does not exist.
    // for p_containerIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::C_<node name>_<container name>
    //## operation containerChildCount(int) const
    virtual int containerChildCount(int p_containerIndex) const = 0;

    // flags existence of a container
    // for p_containerIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::C_<node name>_<container name>
    //## operation containerExists(int) const
    virtual bool containerExists(int p_containerIndex) const = 0;

    // return the pointer to the indicated association.
    // return 0 if the association itself does not exist.
    // for p_associationIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::R_<node name>_<association name>
    //## operation getAssociation(int) const
    virtual const IDataNodeAssociation* getAssociation(int p_associationIndex) const = 0;

    // get the C-string value of the target key of the indicated association.
    // returns 0 if association not existing or undefined.
    // for p_associationIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::R_<node name>_<association name>
    //## operation getAssociationTargetKey(int) const
    virtual const char* getAssociationTargetKey(int p_associationIndex) const = 0;

    // get the target data node of the indicated association.
    // Returns 0 if association is not existing or not resolvable.
    // for p_associationIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::R_<node name>_<association name>
    //## operation getAssociationTargetNode(int) const
    virtual const IDataNode* getAssociationTargetNode(int p_associationIndex) const = 0;

    // return the pointer to the indicated attribute.
    // return 0 if the attribute itself does not exist.
    // for p_attributeIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::A_<node name>_<attribute name>
    //## operation getAttribute(int) const
    virtual const IDataNodeAttribute* getAttribute(int p_attributeIndex) const = 0;

    // Get the value for the indicated integer-typed attribute.
    // Returns 0 if attribute is not available or non-integer.
    // for p_attributeIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::A_<node name>_<attribute name>
    //## operation getAttributeIntValue(int) const
    virtual int getAttributeIntValue(int p_attributeIndex) const = 0;

    // Analyze a (hopefully) numerical value  for the indicated attribute.
    // result is one of the (applicable) literals defined for ValueIndicatorEnum:
    // IS_INT
    // IS_REAL
    // POSITIVE_INFINITE
    // NEGATIVE_INFINITE
    // NOT_A_NUMBER
    // or UNDEF.
    // for p_attributeIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::A_<node name>_<attribute name>
    //## operation getAttributeNumericalValueIndicator(int) const
    virtual IEcuCfgEnums::ValueIndicatorEnum getAttributeNumericalValueIndicator(int p_attributeIndex) const = 0;

    // get the value for an attribute typed or handled as real (aka double or numerical)
    // Returns 0.0 if attribute is not a number (check for details via getNumericalValueIndicator())
    // for p_attributeIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::A_<node name>_<attribute name>
    //## operation getAttributeRealValue(int) const
    virtual double getAttributeRealValue(int p_attributeIndex) const = 0;

    // Get the C-string value of the indicated attribute.
    // Returns "" if attribute is undefined or invalid.
    // for p_attributeIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::A_<node name>_<attribute name>
    //## operation getAttributeValue(int) const
    virtual const char* getAttributeValue(int p_attributeIndex) const = 0;

    // return the pointer to the indicated container.
    // return 0 if the container itself does not exist.
    // for p_containerIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::C_<node name>_<container name>
    //## operation getContainer(int) const
    virtual const IDataNodeContainer* getContainer(int p_containerIndex) const = 0;

    // get the indicated child node available in the indicated container (search by matching contextKey).
    // returns 0 if container or child node are not available.
    // for p_containerIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::C_<node name>_<container name>
    //## operation getContainerChildNode(int,char*) const
    virtual const IDataNode* getContainerChildNode(int p_containerIndex, const char* p_contextKey) const = 0;

    // get the indicated child node available in the indicated container (access by index).
    // returns 0 if container or child node are not available.
    // for p_containerIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::C_<node name>_<container name>
    //## operation getContainerChildNode(int,int) const
    virtual const IDataNode* getContainerChildNode(int p_containerIndex, int p_rowIndex) const = 0;

    // get the C-string value of the context key.
    // returns 0 if association is undefined.
    //## operation getContextKey() const
    virtual const char* getContextKey() const = 0;

    //## operation getDataNodeStructure() const
    virtual const IDataNodeStructure* getDataNodeStructure() const = 0;
};

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class IDataNodeAssociation
// Interface for client access to a concrete data node association
//
// @version IDataNodeAssociation_MAJOR 1
// @version IDataNodeAssociation_MINOR 0
class IDataNodeAssociation
{
    ////    Operations    ////

public:
    //## operation getDataNodeAssociationStructure() const
    virtual const IDataNodeAssociationStructure* getDataNodeAssociationStructure() const = 0;

    // get the C-string value of the association target key.
    // returns 0 if association is undefined.
    //## operation getTargetKey() const
    virtual const char* getTargetKey() const = 0;

    // get the association target data node.
    // Try to resolve the association if not yet done.
    // Returns 0 if association is undefined or invalid or unresolved.
    //## operation getTargetNode() const
    virtual const IDataNode* getTargetNode() const = 0;

    // flags validity of an association.
    // try to resolve the association if not yet done.
    // considering undefined or unresolvable targets as invalid.
    //## operation isValid() const
    virtual bool isValid() const = 0;
};

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class IDataNodeAssociationStructure
// DataNodeAssociationStructure specifies an associations available for the parent DataNodeStructure.
//
// DataNodeAssociationStructure.associatedDataNodeStructure specifies the kind of  data for the association target.
//
// @version IDataNodeAssociationStructure_MAJOR 1
// @version IDataNodeAssociationStructure_MINOR 0
class IDataNodeAssociationStructure
{
    ////    Operations    ////

public:
    // standard getter for attribute get<AttributeName>
    //## operation getAssociatedDataNodeStructure() const
    virtual const IDataNodeStructure* getAssociatedDataNodeStructure() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getIndex() const
    virtual int getIndex() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getName() const
    virtual const char* getName() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getProcessingHints() const
    virtual const char* getProcessingHints() const = 0;
};

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class IDataNodeAttribute
// IDataNodeAttribute is the interface for client access to a concrete data node attribute
//
// @version IDataNodeAttribute_MAJOR 1
// @version IDataNodeAttribute_MINOR 0
class IDataNodeAttribute
{
    ////    Operations    ////

public:
    // returns the pointer to the related attribute structure.
    // nullPtr as return value indicates an error (this should never happen, the attribute value is undefined in this case).
    //## operation getDataNodeAttributeStructure() const
    virtual const IDataNodeAttributeStructure* getDataNodeAttributeStructure() const = 0;

    // get the value for an attribute typed or handled as integer.
    // Returns 0 if attribute is non-integer (check for details via getNumericalValueIndicator())
    //## operation getIntValue() const
    virtual int getIntValue() const = 0;

    // Analyze a (hopefully) numerical value.
    // result is one of the (applicable) literals defined for ValueIndicatorEnum:
    // IS_INT
    // IS_REAL
    // POSITIVE_INFINITE
    // NEGATIVE_INFINITE
    // NOT_A_NUMBER
    // or UNDEF
    //## operation getNumericalValueIndicator() const
    virtual IEcuCfgEnums::ValueIndicatorEnum getNumericalValueIndicator() const = 0;

    // get the value for an attribute typed or handled as real (aka double or numerical)
    // Returns 0.0 if attribute is not a number (check for details via getNumericalValueIndicator())
    //## operation getRealValue() const
    virtual double getRealValue() const = 0;

    // get the C-string value of the attribute.
    // Returns "" if the attribute is undefined or invalid.
    //## operation getValue() const
    virtual const char* getValue() const = 0;

    // flags emptiness of a value.
    // considering undefined values as empty.
    //## operation isEmpty() const
    virtual bool isEmpty() const = 0;

    // flags integer value.
    // considering not existing attributes and undefined values as non-integer.
    // deprecated:
    // use getNumericalValueIndicator() instead.
    //## operation isInt() const
    virtual bool isInt() const = 0;

    // flags validity of a value.
    // considering undefined values as invalid.
    //## operation isValid() const
    virtual bool isValid() const = 0;
};

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class IDataNodeAttributeStructure
// DataNodeAttributeStructure specifies an attributes available for parent DataNodeStructure
//
// @version IDataNodeAttributeStructure_MAJOR 1
// @version IDataNodeAttributeStructure_MINOR 0
class IDataNodeAttributeStructure
{
    ////    Operations    ////

public:
    // standard getter for attribute get<AttributeName>
    //## operation getIndex() const
    virtual int getIndex() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getName() const
    virtual const char* getName() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getProcessingHints() const
    virtual const char* getProcessingHints() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getRuleValueKind() const
    virtual IEcuCfgEnums::RuleValueKindEnum getRuleValueKind() const = 0;
};

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class IDataNodeContainer
// Interface for client access to a concrete data node container
//
// @version IDataNodeContainer_MAJOR 1
// @version IDataNodeContainer_MINOR 0
class IDataNodeContainer
{
    ////    Operations    ////

public:
    // returns the number of child nodes currently hosted by the container
    //## operation childCount() const
    virtual int childCount() const = 0;

    // get the indicated child node available in the container (access by index).
    // returns 0 if not available.
    //## operation getChildNode(int) const
    virtual const IDataNode* getChildNode(int p_rowIndex) const = 0;

    // get the indicated child node available in the container (search by matching contextKey).
    // returns 0 if not available.
    //## operation getChildNode(char*) const
    virtual const IDataNode* getChildNode(const char* p_contextKey) const = 0;

    //## operation getDataNodeContainerStructure() const
    virtual const IDataNodeContainerStructure* getDataNodeContainerStructure() const = 0;
};

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class IDataNodeContainerStructure
// DataNodeContainerStructure specifies a child container available for parent DataNodeStructure.
//
// DataNodeContainerStructure.childDataNodeStructure specifies the kind of contained data.
//
// @version IDataNodeContainerStructure_MAJOR 1
// @version IDataNodeContainerStructure_MINOR 0
class IDataNodeContainerStructure
{
    ////    Operations    ////

public:
    // standard getter for attribute get<AttributeName>
    //## operation getChildDataNodeStructure() const
    virtual const IDataNodeStructure* getChildDataNodeStructure() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getIndex() const
    virtual int getIndex() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getName() const
    virtual const char* getName() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getProcessingHints() const
    virtual const char* getProcessingHints() const = 0;
};

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class IDataNodeCursor
// Interface for client access to a cursor on a data node model.
//
// This interface offers operations to traverse the data node model and to visit individual nodes.
//
// @version IDataNodeCursor_MAJOR 1
// @version IDataNodeCursor_MINOR 0
class IDataNodeCursor
{
    ////    Operations    ////

public:
    // Move cursor to a child node.
    // Returns
    // - pointer to current node in case of success.
    // - 0 if something went wrong.
    // for _containerIndex
    // refer to DataNodeStructure4XXX_constexpr.hpp, XXX_constepr::C_<node name>_<container name>
    //## operation enterChildNode(int,char*)
    virtual const IDataNode* enterChildNode(int p_containerIndex, const char* p_contextKey) = 0;

    // returns the current nesting level
    // (for convenience, the nesting level is automatically adjusted as enter/leave node)
    //## operation getCurrentDepth() const
    virtual int getCurrentDepth() const = 0;

    // get the current position of the cursor
    //## operation getCurrentNode() const
    virtual const IDataNode* getCurrentNode() const = 0;

    // for convenience the root node may be fetched also from a cursor
    //## operation getRootNode() const
    virtual const IDataNode* getRootNode() const = 0;

    // move cursor to the parent node (if root is reached cursor stays at root).
    // Returns
    // - pointer to current node in case of success.
    // - 0 if something went wrong.
    //## operation leaveNode()
    virtual const IDataNode* leaveNode() = 0;

    // delete a cursor.
    // if this is not done the cursor will be deleted later along with the model.
    //
    // return value false indicates that something went wrong at release. In this case some memory leaks happened.
    // No further problems to be expected (in any case, after ptr->release...(); the ptr shall not be used anymore).
    //## operation releaseDataNodeCursor()
    virtual bool releaseDataNodeCursor() = 0;

    // create a copy of current cursor.
    // Returns
    // - pointer to the newly created cursor in case of success.
    // - 0 if something went wrong.
    //## operation reserveDataNodeCursor()
    virtual IDataNodeCursor* reserveDataNodeCursor() = 0;

    // create a cursor for the indicated association target.
    // Returns
    // - pointer to the newly created cursor in case of success.
    // - 0 if something went wrong.
    //## operation reserveDataNodeCursor4AssociationTarget(int)
    virtual IDataNodeCursor* reserveDataNodeCursor4AssociationTarget(int p_indexAssociation) = 0;
};

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class IDataNodeModel
// DataNodeModel is the root for the configuration data of a specific function cluster
// (identified via relatedDataNodeStructureModel-->GlobalID)
//
// The structure... properties hold the corresponding property values of the related DataNodeStructureModel
// - at serialize the current values from  DataNodeStructureModel need to be effective
// - at load any mismatch needs to be detected
//   incompatibilities result in an error case: structure and data do not match)
//
// @version IDataNodeModel_MAJOR 1
// @version IDataNodeModel_MINOR 0
class IDataNodeModel
{
    ////    Operations    ////

public:
    // get the fully qualified file name for model data (as per model manager settings at reserve data node model)
    //## operation getFilePath() const
    virtual const char* getFilePath() const = 0;

    // get a pointer to the root node.
    // Since a model is always created with its root node this should always work.
    //## operation getRootDataNode() const
    virtual const IDataNode* getRootDataNode() const = 0;

    // get the fully qualified file name for model structure (as per model manager settings at reserve data node structure model)
    //## operation getStructureFilePath() const
    virtual const char* getStructureFilePath() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getStructureMajorVersion() const
    virtual int getStructureMajorVersion() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getStructureMinorVersion() const
    virtual int getStructureMinorVersion() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getStructureName() const
    virtual const char* getStructureName() const = 0;

    // delete the model with all contained/related objects.
    // Remark:
    // create model on client side needs to be done via DataNodeModelProxy
    //
    // return value false indicates that something went wrong at release. In this case some memory leaks happened.
    // No further problems to be expected (in any case, after ptr->release...(); the ptr shall not be used anymore).
    //## operation releaseDataNodeModel()
    virtual bool releaseDataNodeModel() = 0;

    // create a cursor with root node as initial position
    // Returns
    // - pointer to the newly created cursor in case of success.
    // - 0 if something went wrong.
    //## operation reserveDataNodeCursor()
    virtual IDataNodeCursor* reserveDataNodeCursor() = 0;
};

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class IDataNodeStructure
// DataNodeStructure is the container for the specification of the structure of individual data nodes related to a function cluster (i.e. inside the parent DataNodeStructureModel).
// attribute index is the LocalID inside parent DataNodeStructureModel
// an unambiguous name needs to be provided for usage in symbol-based API use cases
// one of the available patterns for context-key handling in data nodes needs to be specified in ruleContextKey
// optionally the processing of the related data nodes can be influenced via processingHints
// optionally some documentation / explanations may be added in remarks
// further child-details can be aggregated for attributes, associations and containers
//
// Any DataNodeStructureModel has to contain a ROOT data node structure (name=ROOT, index=0, ruleContextKey=STRUCTURE).
//
// Patterns for further top level data node structures shall be unified via templates or other resources,
// e.g.
// Any DataNodeStructureModel including enums has to contain exactly one ENUMS data node structure (name=ENUMS, ruleContextKey=STRUCTURE) as child of the ROOT node.
// Any DataNodeStructureModel including instance references has to contain exactly one IREFS data node structure (name=IREFS, ruleContextKey=STRUCTURE) as child of the ROOT node.
//
// @version IDataNodeStructure_MAJOR 1
// @version IDataNodeStructure_MINOR 0
//
class IDataNodeStructure
{
    ////    Operations    ////

public:
    // standard getter for attribute get<AttributeName>
    //## operation getIndex() const
    virtual int getIndex() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getName() const
    virtual const char* getName() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getProcessingHints() const
    virtual const char* getProcessingHints() const = 0;

    // standard getter for attribute get<AttributeName>
    //## operation getRuleContextKey() const
    virtual IEcuCfgEnums::RuleContextKeyEnum getRuleContextKey() const = 0;
};

//## package EcuConfiguration::02_sw_arc::ECUCFG_AAP::ECUCFG_AAP_EcuConfiguration::bosch::vrte::ecucfg

//## class IDataNodeStructureModel
// DataNodeStructureModel is the container for the structural description of a function cluster (identified by property name) in a specific version (identified by properties majorVersion and minorVersion). Optionally some background information, explanations etc. can be annotated in property remarks.
//
// @version IDataNodeStructureModel_MAJOR 1
// @version IDataNodeStructureModel_MINOR 0
class IDataNodeStructureModel
{
    ////    Operations    ////

public:
    //## operation getMajorVersion() const
    virtual int getMajorVersion() const = 0;

    //## operation getMinorVersion() const
    virtual int getMinorVersion() const = 0;

    //## operation getName() const
    virtual const char* getName() const = 0;
};

}
}
}

#endif
/*********************************************************************
	File Path	: C:\_scratchpad\DefaultConfig\bosch\vrte\ecucfg\EcuCfgClientInclude.h
*********************************************************************/
