/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#define SC_COMBINE_INTERNAL(v1, v2, v3, v4) v1##v2##v3##v4
#define SC_COMBINE(v1, v2, v3, v4) SC_COMBINE_INTERNAL(v1, v2, v3, v4)

#ifdef __SC_REFLECTION_PARSER__

#define SC_BODY_INTERNAL(...) __attribute__((annotate(#__VA_ARGS__))) void __null_body() {}

#define SC_CLASS(...) 
#define SC_GENERATED_BODY(...) SC_BODY_INTERNAL(GenBody())
#define SC_PROPERTY(...) __attribute__((annotate(#__VA_ARGS__)))

#else

#define SC_GENERATED_BODY_ITEMS(v) SC_COMBINE(ScFileID, _, __LINE__, v)
#define SC_GENERATED_BODY_INIT() \
    public: \
    static bool initGlobal() { return _initStaticInternal(); } \
    private: \
    SC_GENERATED_BODY_ITEMS(_init) \
    SC_GENERATED_BODY_ITEMS(_initStatic)
    


#define SC_CLASS(...)
#define SC_GENERATED_BODY(...)  SC_GENERATED_BODY_INIT() /// TODO: depend on class name or line
#define SC_PROPERTY(...)

#endif