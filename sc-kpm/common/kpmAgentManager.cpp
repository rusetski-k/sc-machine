/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "kpmAgentManager.hpp"
#include "kpmAgent.hpp"

namespace kpm
{

	AgentManager * AgentManager::msInstance = 0;

	AgentManager & AgentManager::getInstance()
	{
		if (!msInstance)
			msInstance = new AgentManager();

		return *msInstance;
	}

	AgentManager::AgentManager()
	{
	}

	AgentManager::~AgentManager()
	{
	}

	void AgentManager::registerAgent(Agent * inAgent)
	{
		check_expr(inAgent);
		check_expr(mAgents.find(inAgent->getSystemIdentifier()) == mAgents.end());
		mAgents[inAgent->getSystemIdentifier()] = inAgent;
	}

	void AgentManager::unregisterAgent(Agent * inAgent)
	{
		check_expr(inAgent);
		tAgentsMap::iterator found = mAgents.find(inAgent->getSystemIdentifier());
		check_expr(found != mAgents.end());
		mAgents.erase(found);
	}

}