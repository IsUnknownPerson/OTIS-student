#include "initgame.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using std::cout;
using std::cin;

initgame::initgame()
{
    cout << R"Wunderwaffe(guess_the_number
Hi! Enter your name, please:
)Wunderwaffe";

    cin >> name;
    cout << name << ", enter your guess:\n";
}

void initgame::generate_random(int value)
{
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    rand_value = std::rand() % value;

    read_file();
}

void initgame::read_file()
{
    std::ifstream in_file{filename};
    if (!in_file.is_open()) {
        std::fstream in_file{filename, std::ios_base::in |
                    std::ios_base::out | std::fstream::app};
        std::cout << "No file. I'll create it: " << filename  << std::endl;
        //return;
    }

    std::string number, name;
    while (getline(in_file, number))
    {
        getline(in_file, name);
        base[number].push_back(name);
    }

    in_file.close();
}


void initgame::save_and_print_record(std::string attempts)
{
    std::ofstream in_file{filename};
    if (!in_file.is_open()) {
        std::ofstream in_file{filename, std::ios_base::in |
                    std::ios_base::out | std::fstream::app};
        std::cout << "Failed to open file: " << filename << "!" << std::endl;
        return;
    }
    base[attempts].push_back(name);
    //in_file << attempts << "\n" << name;
    //in_file.flush();

    cout << "\n\nHigh scores table:\n";
    for (auto it = base.begin(); it != base.end(); it++)
    {
        for (unsigned int i=0; i<it->second.size(); ++i)
        {
            cout << it->second[i] << " " << it->first << "\n";
            in_file << it->first << "\n" << it->second[i] << "\n";
        }
    }
    in_file.close();
}

