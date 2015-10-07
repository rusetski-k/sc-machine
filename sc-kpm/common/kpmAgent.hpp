/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "kpmTypes.hpp"

namespace kpm
{
	/* Class that controls agent class
	 */
	class Agent
	{
	public:

		//! Returns system identifier of node that designate this agent class
		virtual String const & getSystemIdentifier() const = 0;

	};

#define KPM_AGENT_BODY(SystemIdentifier) \
	private: \
	virtual String const & getSystemIdentifier() const \
	{ \
		static String sysIdtf = #SystemIdentifier; \
		return sysIdtf; \
	}

}
