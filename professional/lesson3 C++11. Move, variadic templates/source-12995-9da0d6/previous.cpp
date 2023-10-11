#include <iostream>

int func(int a, int b) {
	return a + b;
}

float func(float a, float b) {
	return a + b;
}

int main(int, char *[])
{
	decltype(func(1, 2)) result1 = func(10, 20);

	decltype(func(1.0f, 2.0f)) result = func(10, 20);

	int value = 42;
	int value2 = 42;
	int value3 = 42;
	int value4 = 42;
	int value5 = 42;
	// Error - could not access value
	// auto lambda0 = [](int a, int b) { return a + b + value; };

	// Ok - capture value by reference
	auto lambda1 = [&value](int a, int b) { return a + b + value; };
	// Ok - capture value by copy
	auto lambda2 = [value](int a, int b) { return a + b + value; };
	// Ok - capture all required variables by reference
	auto lambda3 = [&](int a, int b) { return a + b + value + value3; };
	// Ok - capture all required variables by copy
	auto lambda4 = [=](auto a, auto b) { return a + b + value + value3; };
	// Ok - capture all required variables by reference, but value3 by copy
	auto lambda5 = [&, value3](int a, int b) { return a + b + value + value3; };
	// Ok - capture all required variables by copy, but value 3 by reference
	auto lambda6 = [=, &value3](int a, int b) { return a + b + value + value3; };
	// Error - value3 captures by reference with common reference capture
	// auto lambda7 = [&, &value3](int a, int b) { return a + b + value + value3; };
	// Error - value3 captures by copy with common copy capture
	// auto lambda8 = [=, value3](int a, int b) { return a + b + value + value3; };
	// Ok - some variables by reference, some variable with copy
	auto lambda9 = [value, &value3](int a, int b) { return a + b + value + value3; };
	auto lambda10 = [&value, value3](int a, int b) { return a + b + value + value3; };
	auto lambda11 = [&value, &value3](int a, int b) { return a + b + value + value3; };
	auto lambda12 = [value, value3](int a, int b) { return a + b + value + value3; };

	lambda1(1,2);
	lambda2(1,2);
	lambda3(1,2);
	lambda4(1,2);
	lambda5(1,2);
	lambda6(1,2);
	lambda9(1,2);
	lambda10(1,2);
	lambda11(1,2);
	lambda12(1,2);

	return 0;
}
