#include "dynamic_lib.h"
#include <iostream>

namespace dynamic_lib {

int makeSomeSuperJob() {
  std::cout << "Hello from lib!" << std::endl;
  return 42;
}


}  // namespace lib
