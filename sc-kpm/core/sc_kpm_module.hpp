/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "sc_kpm_prerequest.hpp"
#include "sc_kpm_keynodes.hpp"
#include "sc_kpm_agent.hpp"

#include <sc-memory/wrap/sc_addr.hpp>

namespace kpm
{

class Module
{

public:
    Module(String const & keynodeIdentifier);

    bool initialize();
    bool shutdown();

    template<typename AgentClassT> bool registerAgentClass()
    {
        sc::Addr addr = mKeynodes.createKeynode(AgentClassT::msSysIdtf);
    }

private:
    //! System identifier of node that designate this module
    String mKeynodeIdentifier;

    //! Addr of node that designate this module
    sc::Addr mKeynodeAddr;

    //! Class that contorls keynodes
    Keynodes mKeynodes;

    //! Memory context, that used by this module
    sc::MemoryContext * mContext;

    //! List of registered agent classes
    tAgentClassList mAgentClasses;
};

}


#define _KPM_MAKE_MODULE_CLASS_NAME(ModuleName)  ModuleName##Module
#define _KPM_MAKE_MODULE_INST_NAME(ModuleName) ModuleName##Inst

#define KPM_MODULE_DEFINE(ModuleName) \
class _KPM_MAKE_MODULE_CLASS_NAME(ModuleName) : public kpm::Module \
{ \
public: \
    _KPM_MAKE_MODULE_CLASS_NAME(ModuleName)(String const & keynodeIdentifier) : Module(keynodeIdentifier) {} \
}

#define KPM_MODULE_IMPLEMNTATION(ModuleName, LoadPriority) \
_KPM_MAKE_MODULE_CLASS_NAME(ModuleName) _KPM_MAKE_MODULE_INST_NAME(ModuleName)(String("sc_kpm_module_" #ModuleName)); \
extern "C" { \
    sc_result initialize() \
    { \
        return _KPM_MAKE_MODULE_INST_NAME(ModuleName).initialize() ? SC_RESULT_OK : SC_RESULT_ERROR; \
    } \
      \
    sc_result shutdown() \
    { \
        return _KPM_MAKE_MODULE_INST_NAME(ModuleName).shutdown() ? SC_RESULT_OK : SC_RESULT_ERROR; \
    } \
    sc_uint32 load_priority() \
    { \
        return LoadPriority; \
    } \
}


#define KPM_MODULE(ModuleName, LoadPriority) KPM_MODULE_DEFINE(ModuleName); KPM_MODULE_IMPLEMNTATION(ModuleName, LoadPriority);
