#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include <cstring>

namespace hard {

	// Move medium
	void someStrangeFunction() {
		std::cout << std::endl << std::endl;
		std::cout << "*****     hard::someStrangeFunction()     *****" << std::endl;

		{
			std::string name{"Vasia"};
			std::string str2 = std::move(name);
			std::cout << "std::string str2 = std::move(name); name = " << name << std::endl;
			// Output:
			// 1. undefined.
			// 2. empty string.
			// 3. "Vaisa" in case short string optimization.
			// 4. something else implementation specific
		}

		{
			std::string name{"Vasia"};
			std::move(name);
			std::cout << "std::move(name); name = " << name << std::endl;
			// Output:
			// 1. undefined.
			// 2. empty string.
			// 3. "Vaisa" in case short string optimization.
			// 4. something else implementation specific
		}

		std::cout << std::endl << std::endl;
	}

	// Possible implementation
	template <typename T>
	typename std::remove_reference<T>::type&& 
	move(T&& arg) {
		return static_cast<
			typename std::remove_reference<T>::type&&
		>(arg);
	}

}



namespace basics {

	int global_value = 10;

	void example() {
		std::cout << std::endl << std::endl;
		std::cout << "*****      basics::example     ******" << std::endl;
		
		{
			// global_value is alive here

			int scope_value = 42; // scope variable
		} // value will be destroyed here

		// global_value is alive here

		int* dynamic_value = new int{20};

		// ... some code here

		delete dynamic_value;

		{
			static int local_static_value = 30;
		} // local_static_value will not be destroyed here!

		std::cout << std::endl << std::endl;
	}


}

namespace motivation {

	void example() {

		std::vector<std::string> strings1{
			"first",
			"second",
			"third"
		};

		// some code here

		std::vector<std::string> strings2;

		// now we need to take the first string from the string1 vector
		// and put it into the strings2 vector

		// without moving
		{
			std::string temp = strings1.back(); // first copy here
			strings1.pop_back();

			strings2.push_back(temp); // second copy here

			// we still can use temp here with correct behaviour
			std::cout << temp;
		}

		// with moving
		{
			int v1 = 42;
			int v2 = v1;

			std::string temp = std::move(strings1.back()); // no copy, but moving
			strings1.pop_back();

			strings2.emplace_back(std::move(temp)); // no copy, but moving

			// we can't use a value of the temp here (undefined)
			temp = "value";
		}

	}

}

namespace custom {

	struct string {
		string():
			m_data{nullptr}
			, m_size{0}
		{}

		explicit string(const char* value) {
			m_size = std::strlen(value) + 1; // one more byte for term null
			if (m_size) {
				m_data = new char[m_size];
				std::copy(value, value+m_size, m_data);
				m_data[m_size-1] = '\0';
			}
		}

		string(const string& rhs) {
			m_size = rhs.m_size;
			m_data = new char[m_size];
			std::copy(rhs.m_data, rhs.m_data+m_size, m_data);
		}

		string(string&& rhs)
			: m_data{nullptr}
			, m_size{0} 
		{
			swap(*this, rhs);
		}

		~string() {
			delete [] m_data;
		}

		const char* get() const {
			if (m_size)
				return m_data;
			else 
				return "\0";
		}

	private:
		friend void swap(string& lhs, string& rhs) {
			std::swap(lhs.m_data, rhs.m_data);
			std::swap(lhs.m_size, rhs.m_size);
		}

		char* m_data;
		size_t m_size;
	};

	void example() {
		std::cout << std::endl << std::endl;
		std::cout << "*****     custom::example()     *****" << std::endl;

		custom::string str{"trololo"};
		std::cout << str.get() << std::endl;

		std::cout << "***   after copy:" << std::endl;
		custom::string str2{ str }; // copy or move? -> copy

		std::cout << "str2 = " << str2.get() << std::endl;
		std::cout << "str = " << str.get() << std::endl;

		std::cout << "***   after move:" << std::endl;
		custom::string str3{ std::move(str) };

		std::cout << "str3 = " << str2.get() << std::endl;
		std::cout << "str = " << str.get() << std::endl;

		std::cout << std::endl << std::endl;
	} // destructor for str

}





// Move basic
void handleBigObjectFunc(std::string& bigString) {
	// just a reference here - it is not an "temporary" or "moved" object
}

void handleBigObjectFunc(std::string&& bigString) {
	// r-value reference here - it is a "temporary" or "moved" object
}





// Helper class to trace methods (with move ctor and operator= now!)
struct Tracer {
	Tracer() : m_name{"empty"} {

	}

	explicit Tracer(const char *x_) : m_name(x_) {
		std::cout << "ctor " << m_name << std::endl;
	}

	Tracer(const Tracer &rhs) : m_name(rhs.m_name) {
		std::cout << "copy ctor from " << rhs.m_name << " to " << m_name << std::endl;
	}

	Tracer(Tracer &&rhs) noexcept {
		std::cout << "move ctor from " << rhs.m_name << " to " << m_name << std::endl;
		m_name.swap(rhs.m_name);
	}

	~Tracer() {
		std::cout << "dtor " << m_name << std::endl;
	}

	Tracer &operator=(const Tracer &rhs) {
		std::cout << "copy assign from " << rhs.m_name << " to " << m_name << std::endl;
		return *this;
	}

	Tracer &operator=(Tracer &&rhs) noexcept {
		std::cout << "move assign from " << rhs.m_name << " to " << m_name << std::endl;
		m_name.swap(rhs.m_name);
		return *this;
	}
private:
	std::string m_name;
};


Tracer makeTracer4(const char* name, int fake) {
	if (fake % 2) {
		Tracer result1{name};
		return result1;
	}
	else {
		Tracer result2{"other"};
		return result2;
	}
}


int main(int argc, char* arg[]) {
	// Move medium
	hard::someStrangeFunction();

	custom::example();

	// Move basic
	std::string bigString{"very very big string"}; // 10 GB
	handleBigObjectFunc(bigString);

	handleBigObjectFunc(std::move(bigString));

	Tracer bigTracer{"bigTracer1"}; // 10 GB here
	Tracer otherTracer{"otherTracer"};

	otherTracer = bigTracer; // 20 GB here

	otherTracer = std::move(bigTracer); // maybe only 10 GB here

	Tracer moveTracer = makeTracer4("moveTracer", argc);

	std::cout << "End of the main" << std::endl;

	return 0;
}