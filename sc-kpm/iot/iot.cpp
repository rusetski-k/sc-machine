/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "iot.hpp"
#include "iotAgentLangCommand.hpp"

#include "kpmAgentManager.hpp"

sc_memory_context * s_default_ctx = 0;

kpm::Agent * agentLangCommand = 0;

// ------------------- Module ------------------------------
_SC_EXT_EXTERN sc_result initialize()
{
    s_default_ctx = sc_memory_context_new(sc_access_lvl_make_min); 
    
	kpm::AgentManager & manager = kpm::AgentManager::getInstance();

	agentLangCommand = new iot::AgentLangCommand();

	manager.registerAgent(agentLangCommand);

    return SC_RESULT_OK;
}

_SC_EXT_EXTERN sc_result shutdown()
{
	kpm::AgentManager & manager = kpm::AgentManager::getInstance();
	
	manager.unregisterAgent(agentLangCommand);

	delete agentLangCommand;

    sc_memory_context_free(s_default_ctx);

    return SC_RESULT_OK;
}
