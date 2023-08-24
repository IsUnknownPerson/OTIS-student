// # time g++ -c solution/main.cpp
// real    0m0.020s
// user    0m0.012s
// sys     0m0.008s

#include "my_class.h"
#include "utils.h"

int main() {

	my::my_class cls{"test_file.txt"};

	do_something_with_my_class(cls);

	return 0;
}