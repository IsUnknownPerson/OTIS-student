#pragma once

// __PRETTY_FUNCTION__ macro, which inserts a function declaration in please
// where the macro is placed.
//
// "__PRETTY_FUNCTION__" - gcc and clang supported name, for MS VC - needs
// small definition

#ifdef _MSC_VER
    #define __PRETTY_FUNCTION__ __FUNCSIG__
#endif