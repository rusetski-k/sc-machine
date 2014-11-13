#pragma once

#include "sc_types.h"
#include <assert.h>

namespace sc
{

#ifdef	NDEBUG

#define ASSERT(__expr, __msg)
#define ASSERT_NOT_NULL(__expr, __msg)

#else

#define ASSERT(__expr, __msg) \
{\
    StringStream ss; \
    ss << "ASSERT(" << #__expr << "): " << __msg; \
    ((__expr)	? static_cast<void>(0) \
    : __assert_fail (ss.str().c_str(), __FILE__, __LINE__, __ASSERT_FUNCTION)); \
}

#define ASSERT_NOT_NULL(__v) ASSERT(__v != nullptr, "Null pointer " << #__v)

#endif

}
