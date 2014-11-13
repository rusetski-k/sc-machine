#include "sc_agent_manager.h"

namespace sc
{

    AgentManager& AgentManager::Instance()
    {
        static AgentManager inst;
        return inst;
    }

    void AgentManager::initialize()
    {

    }

    void AgentManager::shutdown()
    {

    }

}
