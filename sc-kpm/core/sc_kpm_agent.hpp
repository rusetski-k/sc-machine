/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "sc_kpm_prerequest.hpp"
#include "sc_kpm_keynodes.hpp"

#include <sc-memory/wrap/sc_addr.hpp>

namespace kpm
{

//! Base class for agent class
class AgentClass
{

protected:
    explicit AgentClass(sc::Addr const & addr);
    virtual ~AgentClass();


    bool initialize();
    void shutdown();

private:
    //! Address of node that designate agents class
    sc::Addr mNodeAddr;
    //! Keynodes holder that used by this class of agents
    Keynodes mKeynodes;
    //! Pointer to used memory context
    sc::MemoryContext * mMemoryContext;
};

//! Base class for agent instance
class Agent
{
public:
    //! Runs agent implementation
    virtual void run() = 0;
};



}
