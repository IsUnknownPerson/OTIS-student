#include <iostream>
#include <new>
#include <string>
#include <vector>

#include <cstdlib>

size_t totalMemoryAllocated = 0;
void *operator new(std::size_t size) {
	std::cout << "operator new called with size: " << size << std::endl;
	totalMemoryAllocated += size;
	return malloc(size);
}
void *operator new(std::size_t size, const std::nothrow_t &) {
	std::cout << "operator new called with size: " << size << std::endl;
	totalMemoryAllocated += size;
	return malloc(size);
}
void operator delete(void *ptr) {
	free(ptr);
}
void operator delete(void *ptr, const std::nothrow_t &) {
	free(ptr);
}

void test_function() {
	std::vector<std::string> values1;
	values1.push_back(
		std::string("Very-very-very looooong string! It's size is 500 symbols! 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111")
	);
	std::vector<std::string> values2;

	std::string temp = values1.back();
	values1.pop_back();
	values2.push_back(
		temp
	);
}

int main() {
	std::cout << "test_function call!" << std::endl;
	size_t startTestMemory = totalMemoryAllocated;
	test_function();

	std::cout << "totalMemoryAllocated = " << totalMemoryAllocated << std::endl;
	std::cout << "totalMemoryAllocated - startTestMemory = " << totalMemoryAllocated - startTestMemory << std::endl;
	return 0;
}

// MSVC output:
/*
test_function call!
operator new called with size: 16
operator new called with size: 16
operator new called with size: 512
operator new called with size: 40
operator new called with size: 16
operator new called with size: 16
operator new called with size: 16
operator new called with size: 512
operator new called with size: 40
operator new called with size: 16
operator new called with size: 512
totalMemoryAllocated = 1712
totalMemoryAllocated - startTestMemory = 1712
*/
