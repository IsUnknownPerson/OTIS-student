#include "pretty.h"

#include <cstdarg>

#include <iostream>

namespace ellipsis {

	void print(int n, ...) {
		va_list va;
		va_start(va, n);
		for (int i = 0; i < n; ++i) {
			std::cout << va_arg(va, int) << std::endl;
		}
		va_end(va);
	}

}

//   iterate1(1, 2.0, "tri");
template <typename... Args>
void iterate1(Args... values) {
	printf("iterate1 = \nsizeof = %llu\nvalues = %d %f %s\n", sizeof...(values), values...);

	// printf("iterate1 = \nsizeof = %lu\nvalues = %d %f %s\n", sizeof...(values)==3, 1, 2.0, "tri");
}

void iterate2() {
	std::cout << std::endl;
}

// iterate2(1, 2.0, "tri");
template <typename T, typename... Args>
void iterate2(T t, Args... args) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::cout << t << " ";
	iterate2(args...);
}

template <typename... Args>
void iterate3(Args... args) {

	int a[sizeof...(args)] = {(std::cout << args, 0)...};

	// ((std::cout << 1, 0), (std::cout << 2.0, 0), (std::cout << "tri", 0));
	// int a[sizeof...(args)] = {(std::cout << args << ", ", 0)...};

	std::cout << std::endl;
}

int main(int, char *[]) {
	std::cout << "\n\n=====" << std::endl;

	ellipsis::print(10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

	iterate1(1, 2.0, "tri");
	iterate2(1, 2.0, "tri");
	iterate3(1, 2.0, "tri");

	return 0;
}
