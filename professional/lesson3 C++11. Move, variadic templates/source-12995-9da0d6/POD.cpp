#include <iostream>

struct Trivial {
	int value;
};

struct TrivialAlso {
	Trivial tr;
};

struct StillTrivial : public TrivialAlso {
	int other_value;
};

struct NotSoTrivial {
	virtual void some_method() {

	}
};


int main() {
	return 0;
}