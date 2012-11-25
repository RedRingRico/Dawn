#ifndef __DAWN_COMPILER_HPP__
#define __DAWN_COMPILER_HPP__

#ifdef _MSC_VER
#include <Compiler_MSVC.hpp>
#endif

#ifdef __GNUC__
#include <Compiler_GNU.hpp>
#endif

#endif
