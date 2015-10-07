/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "kpmAgent.hpp"

namespace iot
{
	class AgentLangCommand : public kpm::Agent
	{
		KPM_AGENT_BODY(agent_lang_command);
	};
}