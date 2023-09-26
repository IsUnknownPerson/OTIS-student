// OTUS C++ basic course
// std::package_task example

#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>
//#include <functional>

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

void task_lambda() {
    std::packaged_task<bool(int)> task([](int n) { return is_prime(n); });
    std::future<bool> result = task.get_future();
    task(4159);
    std::cout << "is_prime(4159): " << result.get() << "\n";
}

void task_bind() {
    std::packaged_task<bool()> task(std::bind(is_prime, 5021));
    std::future<bool> result = task.get_future();
    task();
    std::cout << "is_prime(5021): " << result.get() << "\n";
}

void task_thread() {
    std::packaged_task<bool(int)> task(is_prime);
    std::future<bool> result = task.get_future();
    std::thread task_td(std::move(task), 7919);
    task_td.join();
    std::cout << "is_prime(7919): " << result.get() << "\n";
}

int main() {
    std::cout << "before 1 task" << std::endl;
    task_lambda();
    std::cout << "after 1 task before 2 task" << std::endl;
    task_bind();
    std::cout << "after 2 task before 3 task" << std::endl;
    task_thread();
    std::cout << "after 3 task" << std::endl;
}



