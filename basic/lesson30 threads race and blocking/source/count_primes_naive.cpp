// Count number of prime numbers less then input parameter

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <future>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

bool is_prime(int n) {
	if (n < 2) {
		return false;
	}
	for (int i = 2; i < n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

void count_primes(int begin, int end, size_t& result) {
	size_t count = 0;
	while (begin <= end) {
		if(is_prime(begin)) ++count;
		begin++;
	}
	result += count;
}

// 100000 1
int main(int argc, char *argv[]) {
	using namespace std;
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " n [nthreads]\n";
		return EXIT_FAILURE;
	}
	int n = stoi(argv[1]);
	if (n <= 0) {
		cerr << "n must be positive number\n";
		return EXIT_FAILURE;
	}
	int n_threads = (argc > 2) ? stoi(argv[2]) : thread::hardware_concurrency();
	if (n_threads < 1) {
		cerr << "nthreads must be positive number\n";
		return EXIT_FAILURE;
	}
	chrono::time_point start = chrono::high_resolution_clock::now();

	size_t nprimes = 0;

	int batch_size = n / n_threads;
	std::vector<std::thread> threads;
	threads.reserve(n_threads);
	for(int i = 0; i < n_threads; i+=batch_size) {
		threads.emplace_back(
			std::thread{count_primes, i, std::min(n, i + batch_size), std::ref(nprimes)}
		);
	}

	for(auto& t : threads) {
		t.join();
	}

	chrono::time_point end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;
	cout << nprimes << '\n';
	cout << "It tooks " << elapsed.count() << " seconds with " << n_threads
		 << " threads\n";

	return 0;
}