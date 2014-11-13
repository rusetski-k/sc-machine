#include "sc_common.h"

#include "sc_agent_manager.h"

sc_result initialize()
{
    sc::AgentManager::Instance().initialize();
    return SC_RESULT_OK;
}

sc_result shutdown()
{
    sc::AgentManager::Instance().shutdown();
    return SC_RESULT_OK;
}
