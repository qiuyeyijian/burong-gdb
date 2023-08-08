#ifndef BURONGNET_H
#define BURONGNET_H

// internal macros for string concatenation and anonymous variable name
// The reason for defining a two-layer macro is that it can be expanded normally
// when the parameter is another macro
#define BURONGNET_CAT_IMPL(s1, s2) s1##s2
#define BURONGNET_CAT(s1, s2) BURONGNET_CAT_IMPL(s1, s2)
#define BURONGNET_STR_IMPL(s) #s
#define BURONGNET_STR(s) BURONGNET_STR_IMPL(s)
#define BURONGNET_CAT_STR_IMPL(s1, s2) BURONGNET_STR(BURONGNET_CAT(s1, s2))
#define BURONGNET_CAT_STR(s1, s2) BURONGNET_CAT_STR_IMPL(s1, s2)
#ifdef __COUNTER__  // not standard and may be missing for some compilers
#define BURONGNET_ANONYMOUS(x) BURONGNET_CAT(x, __COUNTER__)
#else  // __COUNTER__
#define BURONGNET_ANONYMOUS(x) BURONGNET_CAT(x, __LINE__)
#endif  // __COUNTER__

#define BURONGNET_VERSION_MAJOR 2
#define BURONGNET_VERSION_MINOR 3
#define BURONGNET_VERSION_PATCH 3

#define BURONGNET_VERSION_STR         \
  BURONGNET_STR(BURONGNET_VERSION_MAJOR) \
  "." BURONGNET_STR(BURONGNET_VERSION_MINOR) "." BURONGNET_STR(BURONGNET_VERSION_PATCH)

// Determines the platform(architecture) on which EMTest is compiled.
#ifdef __CYGWIN__
#define BURONGNET_OS_CYGWIN 1
#elif defined(__MINGW__) || defined(__MINGW32__) || defined(__MINGW64__)
#define BURONGNET_OS_WINDOWS_MINGW 1
#define BURONGNET_OS_WINDOWS 1
#elif defined(WIN32) || defined(_WIN32) || defined(_ON_WIN_)
#define BURONGNET_OS_WINDOWS 1
#elif defined(__linux__) || defined(_ON_LINUX_)
#define BURONGNET_OS_LINUX 1
#if defined __ANDROID__
#define BURONGNET_OS_LINUX_ANDROID 1
#endif
#elif defined(__QNX__) || defined(_ON_QNX_)
#define BURONGNET_OS_QNX 1
#elif defined(__TDA4__) || defined(_ON_TDA4_)
#define BURONGNET_OS_QNX 1
#elif defined __FreeBSD__
#define BURONGNET_OS_FREEBSD 1
#elif defined __APPLE__
#define BURONGNET_OS_MAC 1
#include <TargetConditionals.h>
#include <mach-o/dyld.h>
#endif  // __CYGWIN__

// Declare the API of EMTest
#if BURONGNET_OS_WINDOWS
#define BURONGNET_API_WINDOWS (1)
#elif (BURONGNET_OS_LINUX || BURONGNET_OS_QNX || BURONGNET_OS_TDA4 || BURONGNET_OS_MAC)
#define BURONGNET_API_POSIX (1)
#endif
#if (BURONGNET_OS_MAC)
#define BURONGNET_API_MAC (1)
#endif

#include "cppnet.h"

#endif