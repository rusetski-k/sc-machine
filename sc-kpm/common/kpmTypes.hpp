/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "wrap/sc_memory.hpp"

#include <string>
#include <map>

#if defined (SC_MEMORY_SELF_BUILD)
	#if defined (SC_PLATFORM_WIN)
        #define _SC_KPM_EXTERN __declspec(dllexport)
	#else
        #define _SC_KPM_EXTERN
	#endif
#else
	#if defined (SC_PLATFORM_WIN)
        #define _SC_KPM_EXTERN __declspec(dllimport)
	#else
        #define _SC_KPM_EXTERN
	#endif
#endif


typedef std::string String;

