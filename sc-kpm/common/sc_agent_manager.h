#pragma once

namespace sc
{

    class AgentManager
    {
    public:
        static AgentManager& Instance();

        void initialize();
        void shutdown();
    };

}
