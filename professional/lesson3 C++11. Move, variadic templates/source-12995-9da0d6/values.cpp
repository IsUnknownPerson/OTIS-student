#include <iostream>
#include <string>
#include <vector>

// Helper class to trace methods
struct Tracer {
	Tracer() : m_name("empty") {
		std::cout << "default ctor" << std::endl;
	}

	explicit Tracer(const char* x_) : m_name(x_) {
		std::cout << "ctor " << m_name << std::endl;
	}

	Tracer(const Tracer& rhs) { // Why not	: m_name(rhs.m_name)
		std::cout << "copy ctor from " << rhs.m_name << " to " << m_name << std::endl;
		m_name = rhs.m_name;
	}

	~Tracer() {
		std::cout << "dtor " << m_name << std::endl;
	}

	Tracer& operator=(const Tracer& rhs) {
		std::cout << "copy assign from " << rhs.m_name << " to " << m_name << std::endl;
		m_name = rhs.m_name;
		return *this;
	}

	void doSomethingForAdditionalInitialization() {
		// just a stub
	}
private:
	std::string m_name;
};


void sendValueToRemoveHost(const Tracer& tracer) {
	std::cout << "Tracer was sent" << std::endl;
	// here tracer value should be destroyed - we don't need it now
}


static Tracer gTracer("staticTracer");
void justAnExample() {
	static Tracer tracer{"staticLocalTracer"};
}


int main() {

	std::cout << "Start of the main" << std::endl;

	justAnExample();

	// Example 1 - we want to move, not to copy!
	std::vector<Tracer> tracers;
	
	for (int i=0; i<3; ++i) {
		
		Tracer value{"value"};
		
		value.doSomethingForAdditionalInitialization();
		
		tracers.push_back(value);

	}

	// Example 2 - we want to move, not to copy and not reference!
	{
		Tracer veryBigObject{"Some very very very long string"}; // 10 GB
		sendValueToRemoveHost(veryBigObject);
		
		// Some code here 
		// Still 10 GB

		// And some more ...
		// Still 10 GB here

	} // free 10 GB only here

	std::cout << "End of the main" << std::endl;

	return 0;
}




