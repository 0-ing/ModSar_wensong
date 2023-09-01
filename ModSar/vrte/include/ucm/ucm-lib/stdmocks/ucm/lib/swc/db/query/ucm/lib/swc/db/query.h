//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         tests/VRTE_UT/mocks/ucm/lib/swc/db/query/ucm/lib/swc/db/query.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__QUERY_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__QUERY_H_

#include "ucm/mock/sequence.h"

#include "ucm/lib/swc/error.h"
#include "ucm/lib/swc/db/result.h"
#include "ucm/lib/swc/db/predicate.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {


class Query final : virtual protected ucm::mock::Sequence
{
public:
    enum class Type : unsigned
    {
        kCount, kSelect, kUpdate, kInsert, kRemove
    };

    explicit Query(const Type& type)
        : type_{type}
    {}

    explicit Query(const Type& type, Result&& result)
        : type_{type}
        , result_(std::move(result))
    {}

    Query(Query     &&) = default;
    Query(Query const&) = delete;

    Query& operator=(Query     &&) = default;
    Query& operator=(Query const&) = delete;

    ~Query() = default;

    template<class R,
        std::enable_if_t<
            std::is_same<R, IRecord>::value ||
            std::is_same<R, HRecord>::value ||
            std::is_same<R, SRecord>::value ||
            std::is_same<R, FRecord>::value, bool> = true
    >
    bool filter(const R&) const
    {
        if (pop<bool>())
            throw std::runtime_error(__FUNCTION__);

        return pop<bool>();
    }

    template<class R,
        std::enable_if_t<
            std::is_same<R, IRecord>::value ||
            std::is_same<R, HRecord>::value ||
            std::is_same<R, SRecord>::value ||
            std::is_same<R, FRecord>::value, bool> = true
    >
    std::vector<R> filter(const std::vector<R>&) const
    {
        if (pop<bool>())
            throw std::runtime_error(__FUNCTION__);

        return pop<std::vector<R>>();
    }

    template<class R,
        std::enable_if_t<
            std::is_same<R, IRecord>::value ||
            std::is_same<R, HRecord>::value ||
            std::is_same<R, SRecord>::value ||
            std::is_same<R, FRecord>::value, bool> = true
    >
    std::vector<R> filter(std::vector<R>&&) const
    {
        if (pop<bool>())
            throw std::runtime_error(__FUNCTION__);

        return pop<std::vector<R>>();
    }

    template<class R,
        std::enable_if_t<
            std::is_same<R, IRecord>::value ||
            std::is_same<R, HRecord>::value ||
            std::is_same<R, SRecord>::value ||
            std::is_same<R, FRecord>::value, bool> = true
    >
    unique_type count(const std::vector<R>&) const
    {
        if (pop<bool>())
            throw std::runtime_error(__FUNCTION__);

        return pop<unique_type>();
    }


    void add_ruleset(std::vector<Predicate>&&)
    {
        if (pop<bool>())
            throw std::runtime_error(__FUNCTION__);
    }

    void set_uniques(std::vector<unique_type>&&)
    {
        if (pop<bool>())
            throw std::runtime_error(__FUNCTION__);
    }

    void q_irecord(bool) noexcept;
    void q_hrecord(bool) noexcept;
    void q_frecord(bool) noexcept;
    void q_srecord(bool) noexcept;

    bool q_irecord() const noexcept;
    bool q_hrecord() const noexcept;
    bool q_frecord() const noexcept;
    bool q_srecord() const noexcept;

    const auto& rulesets() const noexcept;

    Type&                 type()     & noexcept;
    std::vector<IRecord>& irecords() & noexcept;
    std::vector<HRecord>& hrecords() & noexcept;
    std::vector<FRecord>& frecords() & noexcept;
    std::vector<SRecord>& srecords() & noexcept;
    std::vector<unique_type>& uniques() & noexcept;

    Type                  type()     && noexcept;
    std::vector<IRecord>  irecords() && noexcept;
    std::vector<HRecord>  hrecords() && noexcept;
    std::vector<FRecord>  frecords() && noexcept;
    std::vector<SRecord>  srecords() && noexcept;
    std::vector<unique_type>  uniques() && noexcept;

    const Type&                 type()     const & noexcept;
    const std::vector<IRecord>& irecords() const & noexcept;
    const std::vector<HRecord>& hrecords() const & noexcept;
    const std::vector<FRecord>& frecords() const & noexcept;
    const std::vector<SRecord>& srecords() const & noexcept;
    const std::vector<unique_type>& uniques() const & noexcept;

private:
    Type type_;
    Result result_{};
    bool q_irecord_{false};
    bool q_hrecord_{false};
    bool q_frecord_{false};
    bool q_srecord_{false};
    std::vector<std::vector<Predicate>> rulesets_{};
};

inline void Query::q_irecord(bool flag) noexcept
{
    q_irecord_ = flag;
}

inline void Query::q_hrecord(bool flag) noexcept
{
    q_hrecord_ = flag;
}

inline void Query::q_frecord(bool flag) noexcept
{
    q_frecord_ = flag;
}

inline void Query::q_srecord(bool flag) noexcept
{
    q_srecord_ = flag;
}

inline bool Query::q_irecord() const noexcept
{
    return q_irecord_;
}

inline bool Query::q_hrecord() const noexcept
{
    return q_hrecord_;
}

inline bool Query::q_frecord() const noexcept
{
    return q_frecord_;
}

inline bool Query::q_srecord() const noexcept
{
    return q_srecord_;
}

inline const auto& Query::rulesets() const noexcept
{
    return rulesets_;
}

inline Query::Type& Query::type() & noexcept
{
    return type_;
}

inline std::vector<IRecord>& Query::irecords() & noexcept
{
    return pop<std::vector<IRecord>&>();
}

inline std::vector<HRecord>& Query::hrecords() & noexcept
{
    return pop<std::vector<HRecord>&>();
}

inline std::vector<FRecord>& Query::frecords() & noexcept
{
    return pop<std::vector<FRecord>&>();
}

inline std::vector<SRecord>& Query::srecords() & noexcept
{
    return pop<std::vector<SRecord>&>();
}

inline std::vector<unique_type>& Query::uniques() & noexcept
{
    return pop<std::vector<unique_type>&>();
}

inline Query::Type Query::type() && noexcept
{
    return std::move(type_);
}

inline std::vector<IRecord> Query::irecords() && noexcept
{
    return pop<std::vector<IRecord>&&>();
}

inline std::vector<HRecord> Query::hrecords() && noexcept
{
    return std::move(std::move(result_).hrecords());
}

inline std::vector<FRecord> Query::frecords() && noexcept
{
    return std::move(std::move(result_).frecords());
}

inline std::vector<SRecord> Query::srecords() && noexcept
{
    return std::move(std::move(result_).srecords());
}

inline std::vector<unique_type> Query::uniques() && noexcept
{
    return std::move(std::move(result_).uniques());
}

inline const Query::Type& Query::type() const & noexcept
{
    return type_;
}

inline const std::vector<unique_type>& Query::uniques() const & noexcept
{
    return result_.uniques();
}

inline const std::vector<IRecord>& Query::irecords() const & noexcept
{
    return result_.irecords();
}

inline const std::vector<HRecord>& Query::hrecords() const & noexcept
{
    return result_.hrecords();
}

inline const std::vector<FRecord>& Query::frecords() const & noexcept
{
    return result_.frecords();
}

inline const std::vector<SRecord>& Query::srecords() const & noexcept
{
    return result_.srecords();
}

}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__QUERY_H_
