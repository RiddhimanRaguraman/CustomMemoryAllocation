// Framework.h
#ifndef FRAMEWORK_H
#define FRAMEWORK_H

// Default warning settings
#ifndef WINDOWS_TARGET_PLATFORM
#error  WINDOWS_TARGET_PLATFORM --- MISSING ---
#endif

#ifndef TOOLS_VERSION
#error  TOOLS_VERSION --- MISSING ---
#endif

#ifndef SOLUTION_DIR
#error SOLUTION_DIR --- MISSING ---
#endif

#ifndef LOCAL_WORKING_DIR
#error LOCAL_WORKING_DIR --- MISSING ---
#endif

// Build Mode
#ifdef _DEBUG
#ifdef _M_X64
#define BUILD_CONFIG_MODE "x64 Debug  "
#else
#define BUILD_CONFIG_MODE "x86 Debug  "
#endif
#else
#ifdef _M_X64
#define BUILD_CONFIG_MODE "x64 Release"
#else
#ifdef MR_FAST   // Only used in optimized class
#define BUILD_CONFIG_MODE "MR_FAST    "
#else
#define BUILD_CONFIG_MODE "x86 Release"
#endif
#endif
#endif

// ----------------------------------------------------------------------------
// Warning suppression settings
// ----------------------------------------------------------------------------

#pragma warning( disable : 4100 ) // 'identifier' : unreferenced formal parameter
#pragma warning( disable : 4127 ) // conditional expression is constant
#pragma warning( disable : 4201 ) // nonstandard extension used: nameless struct/union
#pragma warning( disable : 4251 ) // class needs to have dll-interface
#pragma warning( disable : 4355 ) // 'this' : used in base member initializer list
#pragma warning( disable : 4514 ) // unreferenced inline function has been removed
#pragma warning( disable : 4571 ) // catch(...) semantics changed
#pragma warning( disable : 4625 ) // copy constructor was implicitly defined as deleted
#pragma warning( disable : 4626 ) // assignment operator was implicitly defined as deleted
#pragma warning( disable : 4668 ) // symbol is not defined as a preprocessor macro
#pragma warning( disable : 4587 ) // behavior change: constructor is no longer implicitly called
#pragma warning( disable : 4588 ) // behavior change: destructor is no longer implicitly called
#pragma warning( disable : 4710 ) // function not inlined
#pragma warning( disable : 4711 ) // function selected for automatic inline expansion
#pragma warning( disable : 4820 ) // bytes padding added after construct
#pragma warning( disable : 4291 ) // no matching operator delete found
#pragma warning( disable : 5025 ) // move assignment operator was implicitly defined as deleted
#pragma warning( disable : 5026 ) // move constructor was implicitly defined as deleted
#pragma warning( disable : 5027 ) // move assignment operator was implicitly defined as deleted
#pragma warning( disable : 5039 ) // pointer or reference to potentially throwing function
#pragma warning( disable : 5045 ) // Compiler will insert Spectre mitigation
#pragma warning( disable : 6011 ) // dereferencing NULL pointer
#pragma warning( disable : 5204 ) // class has virtual functions, but its trivial destructor is not virtual
#pragma warning( disable : 5220 ) // a non-static data member with a volatile qualified type
#pragma warning( disable : 26812 ) // Prefer 'enum class' over 'enum'
#pragma warning( disable : 4296 ) // expression always true
#pragma warning( disable : 5205 ) // delete of an abstract class
#pragma warning( disable : 4738 ) // storing 32-bit float result in memory
#pragma warning( disable : 4619 ) // there is no warning number
#pragma warning( disable : 5264 ) // 'const' variable is not used
#pragma warning( disable : 4200 ) // zero-sized array in struct/union
#pragma warning( disable : 5246 ) // initialization of a subobject should be wrapped in braces

// General includes
#include <assert.h>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <crtdbg.h>

// -----------------------------------------------------
// Include platform-specific headers with suppression
// -----------------------------------------------------
#pragma warning( push )
#pragma warning( disable : 4820 )
#define NOMINMAX
#include <Windows.h>
#pragma warning( pop )

#pragma warning( push )
#pragma warning( disable : 4365 )
#pragma warning( disable : 4774 )
#include <string>
#pragma warning( pop )

#pragma warning( push )
#pragma warning( disable : 4365 )
#pragma warning( disable : 4625 )
#pragma warning( disable : 4626 )
#pragma warning( disable : 5026 )
#pragma warning( disable : 5027 )
#include <mutex>
#pragma warning( pop )

#pragma warning( push )
#pragma warning( disable : 4365 )
#pragma warning( disable : 4625 )
#pragma warning( disable : 4626 )
#pragma warning( disable : 5026 )
#pragma warning( disable : 5027 )
#include <atomic>
#pragma warning( pop )

#endif // FRAMEWORK_H
