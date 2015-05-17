/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "sc_kpm_defines.hpp"

#include <string>
#include <list>
#include <vector>
#include <set>
#include <map>

namespace sc
{
    class Addr;
    class MemoryContext;
}

namespace kpm
{
    class AgentClass;
    class Agent;

    typedef std::list<AgentClass *> tAgentClassList;
}

typedef std::string String;
