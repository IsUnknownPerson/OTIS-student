#include <future>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

void worker(int number, const std::string &str) {
	for (int i = 0; i < 10; ++i)
		std::cout << str << "Hello from thread number: " << number << std::endl;
};

void test1_simple_threads() {
	std::cout << "\ntest1_simple_threads\n";

	const std::string str = "Str ";
	std::thread thread1(worker, 0, std::ref(str));
	std::thread thread2(worker, 1, std::ref(str));

	thread1.detach();
	thread2.join();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}


void worker2(size_t number) {
	for (size_t i = 0; i < 3; ++i)
		std::cout << "Hello from thread with id = " << std::this_thread::get_id() << std::endl;
};

void test2_methods() {
	std::cout << "\ntest2_methods\n";

	auto threadCount = std::thread::hardware_concurrency();
	std::cout << "threadCount = " << threadCount << std::endl;
	if (!threadCount)
		threadCount = 2;

	std::vector<std::thread> threads;
	for (std::size_t i = 0; i < threadCount; ++i) {
		threads.emplace_back(worker2, i);
	}

	for (auto &th : threads) {
		// auto handle = th.native_handle();
		if (th.joinable())
			th.join();
	}
}


int worker3(std::mutex& coutMutex, std::mutex& cerrMutex, int number) {
	for (int i = 0; i < 3; ++i) {
		coutMutex.lock();
		std::cout << "Hello from thread with id = " << std::this_thread::get_id() << std::endl;
		coutMutex.unlock();

		cerrMutex.lock();
		std::cout << "Error from thread with id = " << std::this_thread::get_id() << std::endl;
		cerrMutex.unlock();
	}

	return 0;
};

void test3_mutexes() {
	std::cout << "\ntest3_mutexes\n";

	std::mutex coutMutex;
	std::mutex cerrMutex;

	std::thread thread1(worker3, std::ref(coutMutex), std::ref(cerrMutex), 0);
	std::thread thread2(worker3, std::ref(coutMutex), std::ref(cerrMutex), 1);

	// int result1 =  ??
	thread1.join();
	// int result2 =  ??
	thread2.join();
}


int main() {
	test1_simple_threads();

	test2_methods();

	test3_mutexes();

	return 0;
}
