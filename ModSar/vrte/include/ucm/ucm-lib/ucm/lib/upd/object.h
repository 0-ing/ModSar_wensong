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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"
#include "ucm/lib/utl/file_io.h"
#include "ucm/lib/upd/counters.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class Object final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_upd_Object, CTor);
    FRIEND_TEST(Test_ucm_lib_upd_Object, CTor2);
    FRIEND_TEST(Test_ucm_lib_upd_Object, FileOp);
#endif

public:
    enum class Method : unsigned
    {
        kUpload,
        kStream,
    };

    explicit Object(const Method&, size_t size);

    explicit Object(const Method&, size_t size, std::string&&);

    explicit Object(const Method&, size_t size, const std::string&);

    Object(Object     &&) = default;
    Object(Object const&) = delete;

    Object& operator=(Object     &&) = default;
    Object& operator=(Object const&) = delete;

    ~Object() = default;

    void seal() noexcept;

    auto& file()     & noexcept;
    auto& counters() & noexcept;

    const auto& sealed()   const & noexcept;
    const auto& method()   const & noexcept;
    const auto& counters() const & noexcept;
    const auto& filepath() const & noexcept;

    void wr_open();
    void rd_open();
    void rd_close();
    void wr_close();

private:
    bool        sealed_;
    Method      method_;
    Counters    counters_;
    std::string filepath_{};
    utl::FileIO filedesc_{};

    void file_create();
};

inline void Object::seal() noexcept
{
    sealed_ = true;
}

inline auto& Object::file() & noexcept
{
    return filedesc_;
}

inline auto& Object::counters() & noexcept
{
    return counters_;
}

inline const auto& Object::sealed() const & noexcept
{
    return sealed_;
}

inline const auto& Object::method() const & noexcept
{
    return method_;
}

inline const auto& Object::counters() const & noexcept
{
    return counters_;
}

inline const auto& Object::filepath() const & noexcept
{
    return filepath_;
}

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_UPD__OBJECT_H_
