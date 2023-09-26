#include "my_class.h"

namespace my {

	my_class::my_class(const char *path) {
		std::cout << "my_class::my_class - path: " << path << std::endl;
	}

	std::size_t my_class::do_work() const {
		return 0;
	}

	void my_class::do_other_work(int) {
		
	}

}