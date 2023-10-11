#include <iostream>
#include <string>
#include <vector>


#define UNUSED(variable) (void)variable

// void testFunc(int i) {
// 	std::cout << "int" << std::endl;
// }

void testFunc(int &i){
    std::cout << "int&. i= " << i  << std::endl;
}

void testFunc(int&& i) {
    std::cout << "int&&. i= " << i << std::endl;
    std::move()
}


template<typename T>
void testUnirefFunc(T&& param) {
	// param
	testFunc(std::forward<T>(param));
}

int main() {

	int i = 42;

	testFunc(i);

	testUnirefFunc(i);            // int&
	testUnirefFunc(std::move(i)); // int&&
    testUnirefFunc(5); // int&& = 5

	return 0;
}
