#pragma once
#include <string_view>
#include <iostream>

struct LineSeparator
{
    static void out(const std::string_view& msg)
    {
        std::cout << "\n---------------------------------";
        std::cout << msg;
        std::cout << "---------------------------------" << std::endl;;
    } 
};