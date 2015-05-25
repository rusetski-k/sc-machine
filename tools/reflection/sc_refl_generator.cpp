/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "sc_refl_generator.hpp"

#include <stdio.h>

namespace reflection
{

std::string GetClangString(CXString str)
{
    const char* tmp = clang_getCString(str);
    if (tmp != NULL)
    {
        std::string translated = std::string(tmp);
        clang_disposeString(str);
        return translated;
    }
    else
    {
        return "";
    }
}

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData clientData)
{
    GeneratorParams const * params = static_cast<GeneratorParams*>(clientData);
    assert(params);

    CXFile file;
    unsigned int line;
    unsigned int column;
    unsigned int offset;

    CXSourceLocation loc = clang_getCursorLocation(cursor);
    clang_getFileLocation(loc, &file, &line, &column, &offset);

    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);

    CXToken* tokens;
    unsigned int numTokens;
    clang_tokenize(tu, range, &tokens, &numTokens);

    if ( numTokens > 0 )
    {
        for (unsigned int i = 0; i < numTokens - 1; i++)
        {
            std::string token = GetClangString(clang_getTokenSpelling(tu,
                tokens[i]));
            CXSourceLocation tl = clang_getTokenLocation(tu, tokens[i]);

            clang_getFileLocation(tl, &file, &line, &column, &offset);

            printf("%s\n", token.c_str());
        }
    }

    return CXChildVisit_Continue;
}

Generator::Generator()
{
    mIndex = clang_createIndex(0, 0);
}

Generator::~Generator()
{
    clang_disposeTranslationUnit(mTranslationUnit);
    clang_disposeIndex(mIndex);
}

bool Generator::process(GeneratorParams const & params)
{
    const char* args[] = { "-c", "-x", "c++" };

    mTranslationUnit = clang_parseTranslationUnit(mIndex, params.mInputFile.c_str(), args, 3, 0, 0, CXTranslationUnit_None);
    CXCursor startCursor = clang_getTranslationUnitCursor(mTranslationUnit);
    clang_visitChildren(startCursor, visitor, (void*)&params);

    return true;
}

}
