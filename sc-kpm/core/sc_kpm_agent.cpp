/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "sc_kpm_agent.hpp"

namespace kpm
{

AgentClass::AgentClass(sc::Addr const & addr)
    : mNodeAddr(addr)
    , mMemoryContext(0)
{

}

AgentClass::~AgentClass()
{

}

bool AgentClass::initialize()
{


    return false;
}

void AgentClass::shutdown()
{

}

}
