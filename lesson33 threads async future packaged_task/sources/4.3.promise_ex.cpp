// OTUS C++ basic course
// Promise example

#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <thread>

int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::cout << "Answer to the Ultimate question of Life, Universe, and "
                 "Everything:... ";
    std::cout.flush();
    std::thread ultimate_question_of_life{[&p]() {
            //полезный код, но если возникла проблема - выбрасываем ассерт
        try {
            throw std::runtime_error{"Not enough computing power"};
                //Если код наш, то вместо трай-кэтч лучше напрямую сделать:
                //p.set_exception(std::make_exception_ptr(std::logic_error("sdfs")));
        } catch (...) {
            try {
                p.set_exception(std::current_exception());
            } catch (...) {}  // set_exception() may throw too
        }
    }};
    try {
        std::cout << f.get() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    ultimate_question_of_life.join();
}