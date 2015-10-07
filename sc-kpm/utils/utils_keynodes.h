/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#ifndef _utils_keynodes_h_
#define _utils_keynodes_h_

#include "sc_memory.h"

extern sc_addr keynode_nrel_idtf;
extern sc_addr keynode_nrel_main_idtf;
extern sc_addr keynode_nrel_system_identifier;
extern sc_addr keynode_system_element;

extern sc_addr keynode_sc_garbage;

sc_result utils_collect_keynodes_initialize();

sc_result utils_keynodes_initialize();

sc_result sc_common_resolve_keynode(sc_memory_context const * ctx, char const * sys_idtf, sc_addr * keynode);

#define RESOLVE_KEYNODE(ctx, keynode) if (sc_common_resolve_keynode(ctx, keynode##_str, &keynode) != SC_RESULT_OK) return SC_RESULT_ERROR;

#endif
