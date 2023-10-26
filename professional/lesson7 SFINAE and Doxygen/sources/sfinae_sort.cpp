#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
int main() {

}
/*
namespace details {
    template <typename T>
    struct is_container: std::false_type {};

    // partial specializations for vector
    template <typename T, typename Alloc>
    struct is_container<std::vector<T, Alloc>>: std::true_type {};

    // partial specializations for list
    template <typename T, typename Alloc>
    struct is_container<std::list<T, Alloc>>: std::true_type {};
} // details

template <class Container, class = std::enable_if_t<details::is_container<Container>::value>>
std::ostream& operator<<(std::ostream& os, const Container& container) {

    if (!container.empty()) {
        std::cout << *container.begin();
        std::for_each(std::next(container.begin()), container.end(), [] (auto& value) {
            std::cout << ", " << value;
        });
    }
    return os;
}

namespace motivation {

	void example() {
		std::cout << "*****   motivation::example   *****" << std::endl;

		std::vector vector{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
		// Compile time error - std::vector does not have method sort
		// vector.sort()

		// Works good
		std::sort(vector.begin(), vector.end());
		std::cout << "vector after sort: \n\t" << vector << std::endl;

		std::list list{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
		// Compile time error - std::list::iterator is not random access!
		// std::sort(list.begin(), list.end());

		// Works good - std::list has method sort
		list.sort();
		std::cout << "list after sort: \n\t" << list << std::endl;
	}

} // motivation

namespace first_attempt {

	template <typename T>
	auto sort_container(T& container) -> decltype(container.sort()) {
		container.sort();
	}

	template <typename T>
    void sort_container(T& container) {
		std::sort(container.begin(), container.end());
	}

	void example() {
		std::cout << "*****   first_attempt::example   *****" << std::endl;

		std::vector vector{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
		// Works good
		sort_container(vector);
		std::cout << "vector after sort: \n\t" << vector << std::endl;

		std::list list{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
		// Compile time error!
		// ambiguous call
		// sort_container(list);
	}
} // first_attempt

namespace solution {
    namespace impl {
        template <typename T>
        auto sort_container(T& container, int) -> decltype(container.sort()) {
            container.sort();
        }

        template <typename T>
        void sort_container(T& container, long) {
            std::sort(container.begin(), container.end());
        }
    }

    template <typename T>
    auto sort_container(T &container) {
        impl::sort_container(container, int{});
    }

    void example() {
        std::cout << "*****   solution::example   *****" << std::endl;

        std::vector vector{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        // Works good
        sort_container(vector);
        std::cout << "vector after sort: \n\t" << vector << std::endl;

        std::list list{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        // Works now
        sort_container(list);
        std::cout << "list after sort: \n\t" << list << std::endl;
    }
}

int main() {
	motivation::example();
	first_attempt::example();
    solution::example();
}
*/
