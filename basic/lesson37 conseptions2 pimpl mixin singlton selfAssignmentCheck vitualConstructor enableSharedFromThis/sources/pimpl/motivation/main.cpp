// # time g++ -c motivation/main.cpp
// real    0m0.275s
// user    0m0.240s
// sys     0m0.036s

#include "my_class.h"
#include "utils.h"

int main() {

	my::my_class cls{"test_file.txt"};

	do_something_with_my_class(cls);

	return 0;
}