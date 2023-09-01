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

#include "ucm/mock/sequence.h"
#include "ucm/lib/types.h"
#include "ucm/lib/log/logger.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class Counters final
      : virtual protected ucm::mock::Sequence
{
public:
    struct Data
    {
        explicit Data(const usize_type& items,
                      const usize_type& bytes,
                      const usize_type& blocks) noexcept
        : items_{items}
        , bytes_{bytes}
        , blocks_{blocks}
        {
        }

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
        explicit EData(const usize_type& items,
                       const usize_type& bytes,
                       const usize_type& blocks) noexcept
        : Data(items, bytes, blocks)
        {
        }

        EData(EData     &&) = default;
        EData(EData const&) = default;

        EData& operator=(EData     &&) = default;
        EData& operator=(EData const&) = default;

        virtual ~EData() = default;
    };

    struct RData final : public Data
    {
        explicit RData(const usize_type& items,
                       const usize_type& bytes,
                       const usize_type& blocks) noexcept
        : Data(items, bytes, blocks)
        {
        }

        RData(RData     &&) = default;
        RData(RData const&) = default;

        RData& operator=(RData     &&) = default;
        RData& operator=(RData const&) = default;

        virtual ~RData() = default;
    };

    struct LogData final
    {
        explicit LogData(const Counters& obj) noexcept
                 : obj_{obj}
        {
        }

        LogData(LogData     &&) = default;
        LogData(LogData const&) = default;

        LogData& operator=(LogData     &&) = default;
        LogData& operator=(LogData const&) = default;

        ~LogData() = default;

        const Counters& obj_;
    };

    explicit Counters() = default;

    explicit Counters(Counters* other, const EData&, const RData&) noexcept
    {
        (void)(other);
    }

    explicit Counters(const EData&, const RData&) noexcept
    {
    }

    explicit Counters(Counters* other, const EData& edata ) noexcept
    : Counters(other, edata, RData(0, 0, 0))
    {
    }

    explicit Counters(Counters* other, const RData& rdata) noexcept
    : Counters(other, EData(0, 0, 0), rdata)
    {
    }

    explicit Counters(const EData& edata) noexcept
    : Counters(nullptr, edata, RData(0, 0, 0))
    {
    }

    explicit Counters(const RData& rdata) noexcept
    : Counters(nullptr, EData(0, 0, 0), rdata)
    {
    }

    explicit Counters(Counters* other) noexcept
    : Counters(other, EData(0, 0, 0), RData(0, 0, 0))
    {
    }

    Counters(Counters     &&) noexcept {};
    Counters(Counters const&) = delete;

    Counters& operator=(Counters     &&) noexcept;
    Counters& operator=(Counters const&) = delete;

    ~Counters() {}

    void log_values(const std::string&) { pop<void>(); }

    void confirm(bool) noexcept {pop<void>();}

    void receive_pp(const EData&) noexcept {pop<void>();}
    void receive_mm(const EData&) noexcept {pop<void>();}
    void receive_pp(const RData&) noexcept {pop<void>();}
    void receive_mm(const RData&) noexcept {pop<void>();}
    void receive_pp(const Counters&) noexcept {pop<void>();}
    void receive_mm(const Counters&) noexcept {pop<void>();}

    ara_error_type validate_pp() noexcept {return pop<ara_error_type>();}
    ara_error_type overflow_pp() noexcept {return pop<ara_error_type>();}
    ara_error_type eoverflow_pp() noexcept {return pop<ara_error_type>();}
    ara_error_type roverflow_pp() noexcept {return pop<ara_error_type>();}

    const auto& edata()           const noexcept;
    const auto& rdata()           const noexcept;
    const auto& items_expected()  const noexcept;
    const auto& items_received()  const noexcept;
    const auto& bytes_expected()  const noexcept;
    const auto& bytes_received()  const noexcept;
    const auto& blocks_expected() const noexcept;
    const auto& blocks_received() const noexcept;

};

inline Counters operator+(const Counters&, const Counters&) noexcept {return ucm::mock::Sequence::pop<Counters&&>();}

inline std::ostream& operator<<(std::ostream& os, const Counters::LogData&) {return os;}

inline const auto& Counters::edata() const noexcept
{
    return pop<EData const&>();
}

inline const auto& Counters::rdata() const noexcept
{
    return pop<RData const&>();
}

inline const auto& Counters::items_expected() const noexcept
{
    return pop<usize_type const&>();
}

inline const auto& Counters::items_received() const noexcept
{
    return pop<usize_type const&>();
}

inline const auto& Counters::bytes_expected() const noexcept
{
    return pop<usize_type const&>();
}

inline const auto& Counters::bytes_received() const noexcept
{
    return pop<usize_type const&>();
}

inline const auto& Counters::blocks_expected() const noexcept
{
    return pop<usize_type const&>();
}

inline const auto& Counters::blocks_received() const noexcept
{
    return pop<usize_type const&>();
}


}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_UPD__COUNTERS_H_
