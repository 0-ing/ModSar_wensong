//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/object_store.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UPD__OBJECT_STORE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UPD__OBJECT_STORE_H_

#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/log/logger.h"
#include "ucm/lib/upd/object.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class ObjectStore final
      : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_upd__ObjectStore, Simple);
#endif

public:
    explicit ObjectStore(const std::string& fsroot)
    : fsroot_{fsroot}
    {
    }

    ObjectStore(ObjectStore&&) noexcept = default;
    ObjectStore& operator=(ObjectStore&&) = default;

    ObjectStore(const ObjectStore&) = delete;
    ObjectStore& operator=(const ObjectStore&) = delete;

    ~ObjectStore() = default;

    auto& objects() & noexcept;
    auto& currobj() & noexcept;

    const auto& fsroot()  const & noexcept;
    const auto& objects() const & noexcept;
    const auto& currobj() const & noexcept;

    void currobj_next() noexcept {pop<void>();}

private:
    size_t currobj_{0};
    std::string  fsroot_;     // folder for the files
    std::vector<Object> objects_{};
};

inline auto& ObjectStore::objects() & noexcept
{
    return pop<std::vector<Object>&>();
}

inline auto& ObjectStore::currobj() & noexcept
{
    return pop<Object&>();
}

inline const auto& ObjectStore::fsroot() const & noexcept
{
    return pop<std::string const&>();
}

inline const auto& ObjectStore::objects() const & noexcept
{
    return pop<std::vector<Object> const&>();
}

inline const auto& ObjectStore::currobj() const & noexcept
{
    return pop<Object const&>();
}

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_UPD__OBJECT_STORE_H_
