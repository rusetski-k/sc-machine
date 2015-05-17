/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "sc_kpm_prerequest.hpp"

#include <sc-memory/wrap/sc_addr.hpp>

namespace kpm
{

class Keynodes
{
    friend class Module;
    friend class AgentClass;

public:
    Keynodes(sc::MemoryContext * ctx = 0);
    ~Keynodes();

public:
    //! Resolve keynode by name
    sc::Addr const & resolveKeynode(String const & identifier);

    /*! Create keynode by name. First of all it tries to find keynode, and if it exists, then returns it.
     * If keynode doesn't exists, then it would be created
     */
    sc::Addr const & createKeynode(String const & identifier, sc_type subtype, sc_access_levels accessLevels);

protected:
    //! Function used to setup current memory context. Just for internal usage
    void setMemoryContext(sc::MemoryContext * ctx);

private:
    typedef std::map<String, sc::Addr> tKeynodesMap;
    //! Map of keynodes by names
    tKeynodesMap mKeynodes;

    //! Pointer to used memory context
    sc::MemoryContext * mMemoryCtx;
};

}
