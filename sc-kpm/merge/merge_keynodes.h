/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#ifndef _merge_keynodes_h_
#define _merge_keynodes_h_

#include "sc_memory.h"
#include "sc_helper.h"

extern sc_addr keynode_question_set_cantorization;

extern sc_addr keynode_nrel_answer;
extern sc_addr keynode_question_finished;
extern sc_addr keynode_question_initiated;
extern sc_addr keynode_question;
extern sc_addr keynode_system_element;

//! Initialie keynodes that used by merge module
sc_result merge_keynodes_initialize();

sc_result sc_common_resolve_keynode(sc_memory_context const * ctx, char const * sys_idtf, sc_addr * keynode);

#define RESOLVE_KEYNODE(ctx, keynode) if (sc_common_resolve_keynode(ctx, keynode##_str, &keynode) != SC_RESULT_OK) return SC_RESULT_ERROR;

#endif
