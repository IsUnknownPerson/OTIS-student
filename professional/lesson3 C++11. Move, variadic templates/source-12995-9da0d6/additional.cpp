#include <iostream>
#include <vector>


int main() {
	std::vector<int> values = {0, 1, 2, 3, 4, 5, 6};

	for(auto iter = values.begin(); iter != values.end(); ++iter) {
		if (iter != values.begin()) 
			std::cout << ", ";
		std::cout << *iter;
	}
	std::cout << std::endl;

	for(auto& v : values) {
		std::cout << v << ", "; // TODO , ?
	}
	std::cout << std::endl;


	for(auto iter = values.cbegin(); iter != values.cend(); ++iter) {
		std::cout << *iter << ' ';
	}
	std::cout << std::endl;

	for (const auto& v : values) {
		std::cout << v << ' ';
	}
	std::cout << std::endl;

	for (auto v : values) { // copy here!
		std::cout << v << ' ';
	}
	std::cout << std::endl;

	return 0;
}