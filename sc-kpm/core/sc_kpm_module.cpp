/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "sc_kpm_module.hpp"

#include <sc-memory/wrap/sc_memory_headers.hpp>

#include <stdio.h>

namespace kpm
{

Module::Module(String const & keynodeIdentifier)
    : mKeynodeIdentifier(keynodeIdentifier)
    , mContext(0)
{
}

bool Module::initialize()
{
    mContext = new sc::MemoryContext(sc_access_lvl_make_max);
    mKeynodes.setMemoryContext(mContext);

    mKeynodeAddr = mKeynodes.createKeynode(mKeynodeIdentifier,
                                           sc_type_node_class,
                                           sc_access_lvl_make(KPM_CORE_KEYNODE_READ_ACCESSLEVEL, KPM_CORE_KEYNODE_WRITE_ACCESSLEVEL));

    if (!mKeynodeAddr.isValid())
        return false;

    /// TODO: write error to output

    return true;
}

bool Module::shutdown()
{
    delete mContext;
    mContext = 0;

    return true;
}

}
