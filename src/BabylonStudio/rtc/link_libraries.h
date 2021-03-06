#ifdef _WIN32 
#ifndef NDEBUG
#define LIB_SUFFIX "_d.lib"
#else
#define LIB_SUFFIX ".lib"
#endif
#else
#ifndef NDEBUG
#define LIB_SUFFIX "_d"
#else
#define LIB_SUFFIX ""
#endif
#endif
#ifdef _WIN32
#define LIB_PREFIX ""
#else
#define LIB_PREFIX "-l "
#endif


#pragma once
#include <RuntimeObjectSystem/RuntimeLinkLibrary.h>
#define RUNTIME_COMPILER_LINKLIBRARY_ADAPTED(lib) RUNTIME_COMPILER_LINKLIBRARY(LIB_PREFIX lib LIB_SUFFIX)
RUNTIME_COMPILER_LINKLIBRARY_ADAPTED("glad")
RUNTIME_COMPILER_LINKLIBRARY_ADAPTED("imgui")
RUNTIME_COMPILER_LINKLIBRARY_ADAPTED("imgui_utils")
RUNTIME_COMPILER_LINKLIBRARY_ADAPTED("babylonimgui")
RUNTIME_COMPILER_LINKLIBRARY_ADAPTED("babyloncpp")
RUNTIME_COMPILER_LINKLIBRARY_ADAPTED("materialslibrary")
RUNTIME_COMPILER_LINKLIBRARY_ADAPTED("babylonimgui")
