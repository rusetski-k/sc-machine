/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#ifndef _merge_set_h_
#define _merge_set_h_

#include <sc_memory.h>

/*!
 * Function, that implements sc-agent to cantorize given set
 */
sc_result agent_set_cantorization(const sc_event *event, sc_addr arg);

/*!
 * Function, that implements sc-agent to merge two given elements
 */
sc_result agent_merge_two_sc_elements(const sc_event *event, sc_addr arg);

#endif
