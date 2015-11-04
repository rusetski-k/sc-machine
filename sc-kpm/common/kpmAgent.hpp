/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "kpmTypes.hpp"
#include "kpmKeynodes.hpp"

namespace kpm
{

	/* Class that controls agent class
	 */
	class Agent
	{
		friend class AgentManager;

	public:
		//! Returns system identifier of node that designate this agent class
		virtual String const & getSystemIdentifier() const = 0;

	protected:
		//! Calls after agent initialize
		_SC_KPM_EXTERN virtual void onPostInitialize();
		//! Calls before agent shutdown
		_SC_KPM_EXTERN virtual void onPreShutdown();

		// Calls by agent manager
		void initialize(sc::Addr const & addr, KeynodesPtr const & keynodes);
		// Calls by agent manager
		void shutdown();

		_SC_KPM_EXTERN KeynodesPtr const & getKeynodes() const { return mKeynodes; }
		_SC_KPM_EXTERN sc::Addr const & getAddr() const { return mAddr; }

	private:
		sc::Addr mAddr;
		KeynodesPtr mKeynodes;
	};

#define KPM_AGENT_BODY(SystemIdentifier) \
	private: \
	virtual String const & getSystemIdentifier() const \
	{ \
		static String sysIdtf = #SystemIdentifier; \
		return sysIdtf; \
	}

}
