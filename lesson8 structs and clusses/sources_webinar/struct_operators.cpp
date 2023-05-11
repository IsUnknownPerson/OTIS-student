#include <iostream>

struct Person {
	std::string name;
	std::string surname;
	int age;
};

namespace without_operators {

	void example() {
#if 0
		Person p1{"Ivan", "Petrov", 24};
		Person p2{"Petr", "Ivanov", 42};

		std::cout << std::boolalpha;

		// Will not compile:
		// no match for 'operator<' (operand types are 'Person' and 'Person')
	
		std::cout << "p1  < p2 = " << (p1 <  p2) << std::endl;
		std::cout << "p1 == p2 = " << (p1 == p2) << std::endl;
		std::cout << "p1 <= p2 = " << (p1 <= p2) << std::endl;
		std::cout << "p1  > p2 = " << (p1 >  p2) << std::endl;
		std::cout << "p1 >= p2 = " << (p1 >= p2) << std::endl;
#endif
	}

} // without_operators

// We can overload 	any of the following operators:
//     + - * / % ^ & | ~ ! = < >
//     += -= *= /= %= ^= &= |=
//     << >> >>= <<=
//     == != <= >= 
//     && || ++ --
//     , ->* -> ( ) [ ]

// lhs < rhs
// lhs - left  hand side
// rhs - right hand side
bool operator< (const Person& lhs, const Person& rhs) {

    return lhs.age < rhs.age;
}

bool operator> (const Person& lhs, const Person& rhs) {
    return rhs < lhs;
    //return lhs.age > rhs.age;
}

bool operator== (const Person& lhs, const Person& rhs) {
	return !(lhs < rhs) && !(rhs < lhs);
}

bool operator<= (const Person& lhs, const Person& rhs) {
	return (lhs < rhs) || (lhs == rhs);
}

bool operator>= (const Person& lhs, const Person& rhs) {
	return (lhs > rhs) || (lhs == rhs);
}

namespace with_operators {

	void example() {
		Person p1{"Ivan", "Petrov", 24};
		Person p2{"Petr", "Ivanov", 42};

		// Ask cout to print boolean values as true/false instead of 1/0
		std::cout << std::boolalpha;

		std::cout << "p1 < p2 = " << (p1 < p2) << std::endl;
		std::cout << "p1 == p2 = " << (p1 == p2) << std::endl;
		std::cout << "p1 <= p2 = " << (p1 <= p2) << std::endl;
		std::cout << "p1 > p2 = " << (p1 > p2) << std::endl;
		std::cout << "p1 >= p2 = " << (p1 >= p2) << std::endl;
	}

} // with_operators

int main() {
	without_operators::example();
	with_operators::example();

	return 0;
}
