/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "merge.h"
#include "sc_memory_headers.h"
#include "merge_keynodes.h"
#include "merge_agents.h"

sc_memory_context *s_default_ctx = 0;

sc_event *event_question_set_cantorization;
sc_event *event_question_merge_two_sc_elements;

_SC_EXT_EXTERN sc_result initialize()
{
    s_default_ctx = sc_memory_context_new(sc_access_lvl_make_min);

    if (merge_keynodes_initialize() != SC_RESULT_OK)
        return SC_RESULT_ERROR;

    event_question_set_cantorization = sc_event_new(s_default_ctx, keynode_question_initiated, SC_EVENT_ADD_OUTPUT_ARC, 0, agent_set_cantorization, 0);
    if (event_question_set_cantorization == null_ptr)
        return SC_RESULT_ERROR;

    event_question_merge_two_sc_elements = sc_event_new(s_default_ctx, keynode_question_initiated, SC_EVENT_ADD_OUTPUT_ARC, 0, agent_merge_two_sc_elements, 0);
    if (event_question_merge_two_sc_elements == null_ptr)
        return SC_RESULT_ERROR;


    return SC_RESULT_OK;
}

_SC_EXT_EXTERN sc_result shutdown()
{
    sc_event_destroy(event_question_set_cantorization);
    sc_event_destroy(event_question_merge_two_sc_elements);
    sc_memory_context_free(s_default_ctx);

    return SC_RESULT_OK;
}
