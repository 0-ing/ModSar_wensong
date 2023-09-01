//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/counters.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UPD__COUNTERS_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UPD__COUNTERS_H_

#include <string>
#include <iostream>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"
#include "ucm/lib/log/logger.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class Counters final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_upd__Counters, CTor);
    FRIEND_TEST(Test_ucm_lib_upd__Counters, DTor);
    FRIEND_TEST(Test_ucm_lib_upd__Counters, Receive);
    FRIEND_TEST(Test_ucm_lib_upd__Counters, Validate);
    FRIEND_TEST(Test_ucm_lib_upd__Counters, Overflow1);
    FRIEND_TEST(Test_ucm_lib_upd__Counters, Overflow2);
    FRIEND_TEST(Test_ucm_lib_upd__Counters, Overflow3);
    FRIEND_TEST(Test_ucm_lib_upd__Counters, OperatorP);
#endif
public:
    struct Data
    {
        explicit Data(const usize_type&,
                      const usize_type&,
                      const usize_type&) noexcept;

        Data(Data     &&) = default;
        Data(Data const&) = default;

        Data& operator=(Data     &&) = default;
        Data& operator=(Data const&) = default;

        virtual ~Data() = default;

        usize_type items_;
        usize_type bytes_;
        usize_type blocks_;
    };

    struct EData final : public Data
    {
        explicit EData(const usize_type&,
                       const usize_type&,
                       const usize_type&) noexcept;

        EData(EData     &&) = default;
        EData(EData const&) = default;

        EData& operator=(EData     &&) = default;
        EData& operator=(EData const&) = default;

        virtual ~EData() = default;
    };

    struct RData final : public Data
    {
        explicit RData(const usize_type&,
                       const usize_type&,
                       const usize_type&) noexcept;

        RData(RData     &&) = default;
        RData(RData const&) = default;

        RData& operator=(RData     &&) = default;
        RData& operator=(RData const&) = default;

        virtual ~RData() = default;
    };

    struct LogData final
    {
        explicit LogData(const Counters&) noexcept;

        LogData(LogData     &&) = default;
        LogData(LogData const&) = default;

        LogData& operator=(LogData     &&) = delete;
        LogData& operator=(LogData const&) = delete;

        ~LogData() = default;

        const Counters& obj_;
    };

    explicit Counters() = default;

    explicit Counters(Counters*, const EData&, const RData&) noexcept;

    explicit Counters(const EData&, const RData&) noexcept;

    explicit Counters(Counters*, const EData&) noexcept;

    explicit Counters(Counters*, const RData&) noexcept;

    explicit Counters(const EData&) noexcept;

    explicit Counters(const RData&) noexcept;

    explicit Counters(Counters*) noexcept;

    Counters(Counters     &&) noexcept;
    Counters(Counters const&) = delete;

    Counters& operator=(Counters     &&) noexcept;
    Counters& operator=(Counters const&) = delete;

    ~Counters();

    void log_values(const std::string&);

    void confirm(bool) noexcept;

    void receive_pp(const EData&) noexcept;
    void receive_mm(const EData&) noexcept;
    void receive_pp(const RData&) noexcept;
    void receive_mm(const RData&) noexcept;
    void receive_pp(const Counters&) noexcept;
    void receive_mm(const Counters&) noexcept;

    ara_error_type validate_pp() noexcept;
    ara_error_type overflow_pp() noexcept;
    ara_error_type eoverflow_pp() noexcept;
    ara_error_type roverflow_pp() noexcept;

    const auto& edata()           const noexcept;
    const auto& rdata()           const noexcept;
    const auto& items_expected()  const noexcept;
    const auto& items_received()  const noexcept;
    const auto& bytes_expected()  const noexcept;
    const auto& bytes_received()  const noexcept;
    const auto& blocks_expected() const noexcept;
    const auto& blocks_received() const noexcept;

private:
    bool      flag_{false};
    EData     edata_{0, 0, 0};
    RData     rdata_{0, 0, 0};
    Counters* other_{nullptr};

    static bool overflow_pp_check(Data&, const Data&, const Data&) noexcept;
};

Counters operator+(const Counters&, const Counters&) noexcept;

std::ostream& operator<<(std::ostream&, const Counters::LogData&);

inline const auto& Counters::edata() const noexcept
{
    return edata_;
}

inline const auto& Counters::rdata() const noexcept
{
    return rdata_;
}

inline const auto& Counters::items_expected() const noexcept
{
    return edata_.items_;
}

inline const auto& Counters::items_received() const noexcept
{
    return rdata_.items_;
}

inline const auto& Counters::bytes_expected() const noexcept
{
    return edata_.bytes_;
}

inline const auto& Counters::bytes_received() const noexcept
{
    return rdata_.bytes_;
}

inline const auto& Counters::blocks_expected() const noexcept
{
    return edata_.blocks_;
}

inline const auto& Counters::blocks_received() const noexcept
{
    return rdata_.blocks_;
}


}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_UPD__COUNTERS_H_
