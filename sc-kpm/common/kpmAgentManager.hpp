/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "kpmTypes.hpp"

namespace kpm
{
	class Agent;

	class AgentManager
	{
	private:
		explicit AgentManager();
		~AgentManager();

		static AgentManager * msInstance;

	public:
		_SC_KPM_EXTERN static AgentManager & getInstance();

		_SC_KPM_EXTERN void registerAgent(Agent * inAgent);
		_SC_KPM_EXTERN void unregisterAgent(Agent * inAgent);

	private:
		typedef std::map<String, Agent *> tAgentsMap;
		tAgentsMap mAgents;

		sc::MemoryContext mMemoryCtx;
	};

}