/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "sc_kpm_keynodes.hpp"

#include <sc-memory/wrap/sc_memory.hpp>

#include <assert.h>

namespace kpm
{

Keynodes::Keynodes(sc::MemoryContext * ctx /* = 0 */)
    : mMemoryCtx(ctx)
{
}

Keynodes::~Keynodes()
{
}

sc::Addr const & Keynodes::resolveKeynode(String const & identifier)
{
    static sc::Addr const empty;
    tKeynodesMap::const_iterator it = mKeynodes.find(identifier);
    if (it != mKeynodes.end())
        return it->second;

    if (mMemoryCtx)
    {
        sc::Addr addr = mMemoryCtx->findElementBySystemIdentifier(identifier);
        if (addr.isValid())
            return (mKeynodes[identifier] = addr);
    }

    return empty;
}

sc::Addr const & Keynodes::createKeynode(String const & identifier, sc_type subtype, sc_access_levels accessLevels)
{
    static sc::Addr const empty;
    sc::Addr const & found = resolveKeynode(identifier);
    if (found.isValid())
        return found;   /// TODO: possible need to change type and access level

    // create new keynode
    assert(mMemoryCtx);
    if (mMemoryCtx)
    {
        sc::Addr addr = mMemoryCtx->createNode(subtype);
        if (addr.isValid())
        {
            if (!mMemoryCtx->setSystemIdentifier(addr, identifier) || !mMemoryCtx->setElementAccessLevels(addr, accessLevels, 0))
            {
                mMemoryCtx->eraseElement(addr);
                return empty;
            }

            return (mKeynodes[identifier] = addr);
        }
    }

    return empty;
}

void Keynodes::setMemoryContext(sc::MemoryContext * ctx)
{
    mMemoryCtx = ctx;
}

}
