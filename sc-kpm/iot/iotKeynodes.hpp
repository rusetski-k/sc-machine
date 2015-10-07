/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#ifndef _iotKeynodes_h_
#define _iotKeynodes_h_

extern "C"
{
#include "sc_memory_headers.h"
}


//! Initialize all keynodes, that will be used in extension
sc_bool initialize_keynodes();

#endif
