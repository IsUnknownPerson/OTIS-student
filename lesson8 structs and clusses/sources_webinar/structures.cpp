#include <iostream>
#include <string>

namespace motivation {

	// in     - input parameter
	// out    - output parameter 
	// in/out - input/output parameter

    // 0 or 1 parameter can be returned
    void get_user_info(std::string& name, std::string& surname, int& age) {

		std::cout << "Hello!" << std::endl;
		
		std::cout << "Enter your name:" << std::endl;
		std::cin >> name;

		std::cout << "Enter your surname:" << std::endl; 
		std::cin >> surname;

		std::cout << "Enter your age:" << std::endl;
		std::cin >> age;
	}

	void example() {

		std::string name;
		std::string surname;
		int age;

		get_user_info(name, surname, age);

		if (age < 16) {
			std::cout << "Access denied!" << std::endl;
		}
		else if (age < 30) {
			std::cout << "Hello, " << name << std::endl;
		}
		else {
			std::cout << "Hello, " << name << " " << surname << std::endl;
		}
	}

} // motivation


namespace structures {
    // Combine related data in a stand alone abstraction
	struct Person {
        std::string name;
        int age = 30;
        float weight;
        float height;
	};

	Person get_user_info() {

        Person person;

		std::cout << "Hello!" << std::endl;
		
		std::cout << "Enter your name:" << std::endl;
		std::cin >> person.name;

		std::cout << "Enter your age:" << std::endl;
		std::cin >> person.age;

		return person;
	}

    void get_user_info(Person& person) {

        std::cout << "Hello!" << std::endl;

        std::cout << "Enter your name:" << std::endl;
        std::cin >> person.name;

        std::cout << "Enter your age:" << std::endl;
        std::cin >> person.age;
    }

	void example() {

		Person person = get_user_info();

		if (person.age < 16) {
			std::cout << "Access denied!" << std::endl;
		}
        else {
			std::cout << "Hello, " << person.name << std::endl;
		}
	}

    void struct_initialization()
    {
        Person person = {"Ivan", 28, 89.4, 184.4}; //aggregate initialization
        Person person2 = {"Dmitry", 29}; // weight and height will be initialized with 0
        Person person3 {"Dmitry", 29}; //C++11 braced initialization
        Person person4 = {.name = "Alex", .weight = 30}; //C++20 designated initializers

        Person person5;
        person5.age = 45;
        person5.height = 175.4;
    }

    struct File
    {
        int descriptor;
        std::string path;
    };

    struct ConnectionParams
    {
        int port;
        int ip[4];
        std::string username;
        std::string passwd;
    };

    struct Address
    {
        std::string city;
        std::string street;
        int index;
        int house;
        int apartments;
    };

    struct Employee
    {
        std::string name;
        Address address;
    };

    void nested_structures_examples()
    {
        Employee emp = {"Ivan", {"Moscow", "Tverskaya", 141000, 1, 2}};
        std::cout << "Employee name " << emp.name <<
                     " city " << emp.address.city << std::endl;
    }
} // namespace structures

int main() {

	motivation::example();
	structures::example();
    structures::struct_initialization();
    structures::nested_structures_examples();

	return 0;
}
