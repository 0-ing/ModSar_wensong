//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

//******************************************************************************
//* @file        json_storer_interface.h
//* @brief       json storer header
//*
//* @swcomponent json_parser
//*******************************************************************************/

#ifndef JSON_STORER_INTERFACE_H_23849784978432
#define JSON_STORER_INTERFACE_H_23849784978432

#include <cstdint>

namespace bosch
{
namespace vrte
{
namespace json
{

/**
 * @brief interface for a storer that must be implemented by each application that
 *        wants to use this parser.
 */

class JsonStorerInterface
{
public:
    /**
     * @brief make destructor virtual
     */
    virtual ~JsonStorerInterface() = default;
    /**
     * @brief create and enter a subnode of type "array" to current object.
     * @param[in] name : name of the array
     * @return false -> some error occurred while storing
     */
    virtual bool CreateAndEnterSubnodeArrayToObject(const char* name) noexcept = 0;
    /**
     * @brief create and enter a subnode of type "array" to current array.
     * @return false -> some error occurred while storing
     */
    virtual bool CreateAndEnterSubnodeArrayToArray() noexcept = 0;
    /**
     * @brief create and enter a subnode of type "object" to current object.
     * @param[in] name : name of the object
     * @return false -> some error occurred while storing
     */
    virtual bool CreateAndEnterSubnodeObjectToObject(const char* name) noexcept = 0;
    /**
     * @brief create and enter a subnode of type "object" to current array.
     * @return false -> some error occurred while storing
     */
    virtual bool CreateAndEnterSubnodeObjectToArray() noexcept = 0;
    /**
     * @brief add string item to current array
     * @return false -> some error occurred while storing
     */
    virtual bool AddStringToArray(const char* value) noexcept = 0;
    /**
     * @brief add bool item to current array
     * @param[in] value : value to store
     * @return false -> some error occurred while storing
     */
    virtual bool AddBoolToArray(const bool value) noexcept = 0;
    /**
     * @brief add double item to current array
     * @param[in] value : value to store
     * @return false -> some error occurred while storing
     */
    virtual bool AddDoubleToArray(const double value) noexcept = 0;
    /**
     * @brief add "int32_t" item to current array
     * @param[in] value : value to store
     * @return false -> some error occurred while storing
     */
    virtual bool AddInt32ToArray(const int32_t value) noexcept = 0;
    /**
     * @brief add "null" item to current array
     * @param[in] value : value to store
     * @return false -> some error occurred while storing
     */
    virtual bool AddNullToArray() noexcept = 0;
    /**
     * @brief add string item to current object with the given name
     * @param[in] name : name of the item to store
     * @param[in] value : value to store
     * @return false -> some error occurred while storing
     */
    virtual bool AddStringToObject(const char* name, const char* value) noexcept = 0;
    /**
     * @brief add bool item to current object with the given name
     * @param[in] name : name of the item to store
     * @param[in] value : value to store
     * @return false -> some error occurred while storing
     */
    virtual bool AddBoolToObject(const char* name, const bool value) noexcept = 0;
    /**
     * @brief add double item to current object with the given name
     * @param[in] name : name of the item to store
     * @param[in] value : value to store
     * @return false -> some error occurred while storing
     */
    virtual bool AddDoubleToObject(const char* name, const double value) noexcept = 0;
    /**
     * @brief add "int32_t" item to current object with the given name
     * @param[in] name : name of the item to store
     * @param[in] value : value to store
     * @return false -> some error occurred while storing
     */
    virtual bool AddInt32ToObject(const char* name, const int32_t value) noexcept = 0;
    /**
     * @brief  add "null" item  to current object with the given name
     * @param[in] name : name of the item to store
     * @param[in] value : value to store
     * @return false -> some error occurred while storing
     */
    virtual bool AddNullToObject(const char* name) noexcept = 0;
    /**
     * @brief close and leave the current subnode of type "array".
     * @return false -> some error occurred while calling
     */
    virtual bool CloseArrayAndLeaveSubnode() noexcept = 0;
    /**
     * @brief close and leave the current subnode of type "object".
     * @return false -> some error occurred while calling
     */
    virtual bool CloseObjectAndLeaveSubnode() noexcept = 0;
};

}
}
}

#endif
