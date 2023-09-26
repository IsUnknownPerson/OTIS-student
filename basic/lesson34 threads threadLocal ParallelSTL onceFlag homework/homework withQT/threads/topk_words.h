#pragma once

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>

using Counter = std::map<std::string, std::size_t>;
const size_t TOPK = 10;

class topk_words
{
public:
    topk_words(int, char**);

//private:


    void print_topk(std::ostream& stream, const Counter&, const size_t k);
    void count_words(std::istream& stream, Counter&);
    std::string tolower(const std::string &str);

    int argc;
    char **argv;
};

