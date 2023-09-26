#include <iostream>

#include "config.h"
#include <sumLib.h>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int, char**) {
  po::options_description desc ("Allowed options");

  std::cout << "Hello from main!" << std::endl;
  sumLib::sum(1, 3);
  std::cout << "Lib verion:" << sumLib::getVersion() << std::endl;

  std::cout << "Main version from macro: " << (PROJECT_VERSION) << std::endl;
  std::cout << "Main version from func: " << getVersion() << std::endl;

  return 0;
}