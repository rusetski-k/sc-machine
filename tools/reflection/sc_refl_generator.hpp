/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "sc_refl_types.hpp"

#include <clang-c/Index.h>

namespace reflection
{

struct GeneratorParams
{
    String mInputFile;

    GeneratorParams()
    {
    }
};

class Generator
{
public:
    Generator();
    ~Generator();

    bool process(GeneratorParams const & params);

private:
    CXIndex mIndex;
    CXTranslationUnit mTranslationUnit;
};

}
