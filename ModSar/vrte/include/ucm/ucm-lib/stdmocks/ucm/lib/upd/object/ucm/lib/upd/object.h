//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/object.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UPD__OBJECT_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UPD__OBJECT_H_

#include <string>


#include "ucm/mock/sequence.h"
#include "ucm/lib/types.h"
#include "ucm/lib/utl/file_io.h"
#include "ucm/lib/upd/counters.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class Object final
      : virtual protected ucm::mock::Sequence
{

public:
    enum class Type : unsigned
    {
        kUndef,
        kPackage,
        kManifest,
        kArtefact
    };

    enum class Method : unsigned
    {
        kUpload,
        kStream,
    };

    explicit Object(const Method&, size_t) {}

    explicit Object(const Method&, size_t, std::string&&) {}

    explicit Object(const Method&, size_t, const std::string&) {}

    Object(Object     &&) = default;
    Object(Object const&) = delete;

    Object& operator=(Object     &&) = default;
    Object& operator=(Object const&) = delete;

    ~Object() = default;

    void seal() noexcept;

    auto& file()     & noexcept;
    auto& counters() & noexcept;

    const auto& type()     const & noexcept;
    const auto& sealed()   const & noexcept;
    const auto& method()   const & noexcept;
    const auto& counters() const & noexcept;
    const auto& filepath() const & noexcept;

    void set_type(const Type&) noexcept;

    void wr_open() {pop<void>();}
    void rd_open() {pop<void>();}
    void rd_close() {pop<void>();}
    void wr_close() {pop<void>();}

};

inline void Object::seal() noexcept
{
   pop<void>();
}

inline auto& Object::file() & noexcept
{
    return pop<utl::FileIO&>();
}

inline auto& Object::counters() & noexcept
{
    return pop<Counters&>();
}

inline const auto& Object::type() const & noexcept
{
    return pop<Type&>();
}

inline const auto& Object::sealed() const & noexcept
{
    return pop<bool const&>();
}

inline const auto& Object::method() const & noexcept
{
    return pop<Method&>();
}

inline const auto& Object::counters() const & noexcept
{
    return pop<Counters const&>();
}

inline const auto& Object::filepath() const & noexcept
{
    return pop<std::string const&>();
}

inline void Object::set_type(const Object::Type&) noexcept
{
   pop<void>();
}

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_UPD__OBJECT_H_
