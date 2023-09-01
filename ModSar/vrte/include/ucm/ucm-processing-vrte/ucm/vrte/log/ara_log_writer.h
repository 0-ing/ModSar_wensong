//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/log/ara_log_writer.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_log

#ifndef UCM_AAP_PROCESSING_VRTE_LOG_ARA_LOG_WRITER_H_
#define UCM_AAP_PROCESSING_VRTE_LOG_ARA_LOG_WRITER_H_

#include "ucm/lib/log/writer.h"
#include "ucm/vrte/log/ara_log_includes.h"

/// @addtogroup bosch_vrte_ucm_vrte_log
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace log   {

/// @brief ARA log writer implementation.
///

class AraLogWriter final : public lib::log::Writer
{
public:
    explicit AraLogWriter(const level_type&) noexcept;

    // copy semantics
    AraLogWriter(const AraLogWriter&) = delete;
    AraLogWriter& operator=(const AraLogWriter&) = delete;

    // move semantic
    AraLogWriter(AraLogWriter&&) = delete;
    AraLogWriter& operator=(AraLogWriter&&) = delete;

    ~AraLogWriter() = default;

    /// @brief Write the log message based on the selected
    ///        logger and the level
    /// @param [IN] log message of type : lib::log::Message
    /// @return Void
    virtual void output(const lib::log::Message&) noexcept override;
};

}    // namespace log
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_PROCESSING_VRTE_LOG_ARA_LOG_WRITER_H_
