#include <iostream>
#include <new>
#include <string>
#include <vector>

#include <cstdlib>
#include <cstring>

#define VERY_STRANGE_IMPLEMENTATION 0

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

struct CustomString {
public:
	CustomString() {}
	explicit CustomString(const char* str) {
		m_size = std::strlen(str);
		m_data = new char[m_size + 1]; // +1 for zero-termination
		std::memcpy(m_data, str, m_size * sizeof(char));
		m_data[m_size] = '\0';
	}

	CustomString(const CustomString& rhs)
		: m_size(rhs.m_size) {
		m_data = new char[m_size + 1]; // +1 for zero-termination
		std::memcpy(m_data, rhs.m_data, m_size * sizeof(char));
		m_data[m_size] = '\0';
	}

#ifdef VERY_STRANGE_IMPLEMENTATION

	// Non-const copy constructor?? Possible. But strange.
	CustomString(CustomString& rhs) {
		m_data = rhs.m_data;
		m_size = rhs.m_size;
		rhs.m_data = 0;
		rhs.m_size = 0;
	}

#endif

	~CustomString() {
		delete [] m_data;
	}

	const char * data() const { return m_data; }
	size_t size() const { return m_size; }

private:
	char * m_data;
	size_t m_size;
};

void test_function() {
	std::vector<CustomString> values1;
	values1.push_back(
		CustomString("Very-very-very looooong string! It's size is 500 symbols! 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111")
	);
	std::vector<CustomString> values2;

	CustomString temp = values1.back();
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
