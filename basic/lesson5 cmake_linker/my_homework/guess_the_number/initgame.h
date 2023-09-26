#pragma once

#include <iostream>
#include <vector>
#include <map>


class initgame
{
public:
    initgame();

public:
    int rand_value;
    const std::string filename = "high_scores.txt";

    void save_and_print_record(std::string);
    void generate_random(int);

private:
    void read_file();

    int max_ranod_value = 100;
    std::string name;
    std::map<std::string, std::vector<std::string>> base;
};

