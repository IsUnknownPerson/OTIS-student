#include "config.h"
#include <lib.h>
#include <dynamic_lib.h>

#include <iostream>

int main(int, char**) {
    std::cout << "Hello from main!" << std::endl;
    lib::makeSomeSuperJob();
    std::cout << "Lib verion:" << lib::getVersion() << std::endl;
    dynamic_lib::makeSomeSuperJob();

    std::cout << "Main version: " << (PROJECT_VERSION) << std::endl;

    return 0;
}
