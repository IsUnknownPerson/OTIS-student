#include <iostream>
#include <map>
#include <string>
#include "line_separator.h"

void unique() {
    LineSeparator::out(" Example 1: testUnique");

    std::map<int, std::string> values;

    // access by key
    // maybe rewrite or insert
    values[24] = "Who is it?";
    std::cout << values[5] << std::endl;

    // maybe rewrite
    /*std::pair<
        std::map<int,std::string>::iterator,
        bool
    > ret;*/
    auto result = values.insert(std::make_pair(42, "Petia"));

    std::cout << result.first->first << " <-> ";
    std::cout << result.first->second << ". inserted: " << result.second << std::endl;

    result = values.insert(std::make_pair(42, "Vasia"));
    std::cout << result.first->first << " <-> ";
    std::cout << result.first->second << ". inserted: " << result.second << std::endl;
}

void order() {
    LineSeparator::out(" Example 2: order");

    std::map<std::string, int> values = {
        {"Vasia",  10},
        {"Petia",  42},
        {"Marina", 17},
        {"Mike",   22},
        {"Alex",   1}
    };

    for (const auto& v: values) {
        std::cout << v.first << std::endl;
    }
}

void iterator() {
    LineSeparator::out(" Example 3: iterator");

    std::map<std::string, int> values = {
        {"Alpha",   1},
        {"Bravo",   2},
        {"Charlie", 3},
        {"Delta",   4},
        {"Echo",    5}
    };

    auto iter = values.begin();
    std::cout << iter->first << " " << iter->second << std::endl;

    // Bidirectional
    ++iter;
    --iter;

    // But not random-access
    // iter += 3;

    std::advance(iter, 2);
    std::cout << iter->first << " " << iter->second << std::endl;
}

void find() {
    std::map<std::string, int> values = {
            {"Vasia",  10},
            {"Petia",  42}
    };

    auto a = values.find("Vasia");
    std::cout << "Found: " << a->first << " : " << a->second << std::endl;

    auto b = values.find("Ann");

    if (b == values.end()) {
        std::cout <<  "Not found: Ann" << std::endl;
    }
}


int main(int, char* []) {
    unique();
    order();
    iterator();
    find();
    return 0;
}
