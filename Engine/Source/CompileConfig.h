#pragma once

#ifdef RAGE3D_IS_BUILDING
#include "Rage3D.h"
#else
#include <Rage3D/Rage3D.h>
#endif

// Macros with identifiers of c++ version.
#define ENGINE_CPP11_STANDARD (201103L)
#define ENGINE_CPP14_STANDARD (201402L)
#define ENGINE_CPP17_STANDARD (201703L)
#define ENGINE_CPP20_STANDARD (202000L) // speculative

// Macro that can be used to identify c++ version.
#ifndef ENGINE_CPLUSPLUS
#if defined(_MSVC_LANG) && !defined(__clang__)
    // Note: VC14.0/1900 (VS2015) lacks too much from C++14
#if (_MSC_VER == 1900)
#define ENGINE_CPLUSPLUS ENGINE_CPP11_STANDARD
#else
#define ENGINE_CPLUSPLUS _MSVC_LANG
#endif
#else
#define ENGINE_CPLUSPLUS __cplusplus
#endif
#endif

// Macros with a strong guarantee of what c++ version is available.
#define ENGINE_CPP11_SUPPORT_OR_LATER (ENGINE_CPLUSPLUS >= ENGINE_CPP11_STANDARD)
#define ENGINE_CPP14_SUPPORT_OR_LATER (ENGINE_CPLUSPLUS >= ENGINE_CPP14_STANDARD)
#define ENGINE_CPP17_SUPPORT_OR_LATER (ENGINE_CPLUSPLUS >= ENGINE_CPP17_STANDARD)

// Macros for specific c++ versions
#if ENGINE_CPP17_SUPPORT_OR_LATER
    // Least match
#define ENGINE_CPP11(x) x
#define ENGINE_CPP14(x) x
#define ENGINE_CPP17(x) x
// Exact match
#define ENGINE_CPP11_ONLY(x)
#define ENGINE_CPP14_ONLY(x)
#define ENGINE_CPP17_ONLY(x) x
#elif ENGINE_CPP14_SUPPORT_OR_LATER
    // Least match
#define ENGINE_CPP11(x) x
#define ENGINE_CPP14(x) x
#define ENGINE_CPP17(x)
// Exact match
#define ENGINE_CPP11_ONLY(x)
#define ENGINE_CPP14_ONLY(x) x
#define ENGINE_CPP17_ONLY(x)
#elif ENGINE_CPP11_SUPPORT_OR_LATER
    // Least match
#define ENGINE_CPP11(x) x
#define ENGINE_CPP14(x)
#define ENGINE_CPP17(x)
// Exact match
#define ENGINE_CPP11_ONLY(x) x
#define ENGINE_CPP14_ONLY(x)
#define ENGINE_CPP17_ONLY(x)
#else
#error Compiler does not support required c++ standard. How did you get here?
#endif

// Case insensitive string comparison.
#ifdef _WIN32
#define ENGINE_STRICMP(a,b) stricmp(a,b)
#define ENGINE_STRNICMP(a,b,n) strnicmp(a,b,n)
#else
#define ENGINE_STRICMP(a,b) strcasecmp(a,b)
#define ENGINE_STRNICMP(a,b,n) strncasecmp(a,b,n)
#endif
