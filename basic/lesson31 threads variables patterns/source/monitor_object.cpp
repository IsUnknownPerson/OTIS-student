#include <exception>
#include <iostream>
#include <utility>
#include <mutex>
#include <vector>
#include <thread>
#include <cassert>

namespace monitor {

	// Monitor
	// Monitor object
	template <class T>
	class monitor {
	public:
		template <typename... Args>
		monitor(Args &&...args) : m_data{std::forward<Args>(args)...} {}

		struct helper {
			helper(monitor *mon) 
				: m_parent{mon}
				, m_lock{mon->m_mutex} {}
			
			T *operator->() {
				return &m_parent->m_data; 
			}
		private:
			monitor *m_parent;
			std::lock_guard<std::mutex> m_lock;
		};

		helper operator->() { return helper(this); }

	private:
		T m_data;
		std::mutex m_mutex;
	};


	void example() {
		monitor<std::vector<int>> thread_safe_vector{1, 2, 3, 4, 5};

		auto lambda = [](monitor<std::vector<int>> &vec) {
            //std::lock_guard<std::mutex> lck; один раз блокируем
            //не нужно, так как наш вектор в мониторе и потокобезопасен
			for (int i = 0; i < 10; ++i) {
				vec->push_back(i);
                //но тут 10 раз монитором заблокируется
                //это хуже чем 1 раз, но зато проще и быстрей написать
                //цена монитора получается высокой
			}
		};

		std::thread thr1{lambda, std::ref(thread_safe_vector)};
		std::thread thr2{lambda, std::ref(thread_safe_vector)};

		thr1.join();
		thr2.join();

		for (int i = 0; i < thread_safe_vector->size(); ++i) {
				std::cout << ' ';
			std::cout << thread_safe_vector->data()[i];
		}
		auto size = thread_safe_vector->size();
		auto iter = thread_safe_vector->cbegin();
	}
}

int main() {
	monitor::example();

	return 0;
}
