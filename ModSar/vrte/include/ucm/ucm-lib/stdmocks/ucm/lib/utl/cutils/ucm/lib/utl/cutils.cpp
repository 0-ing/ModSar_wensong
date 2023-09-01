//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/cutils.cpp
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#include "ucm/lib/utl/cutils.h"

#include <stdlib.h>
#include <string.h>

#if defined(__QNX__) || defined(__QNXNTO__) || defined(HAVE_PROGNAME)
extern char* __progname;
#endif

const char* progname(const char*)
{
    return bosch::vrte::ucm::mock::Sequence::pop<char*>();
}
