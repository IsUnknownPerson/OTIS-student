#include <thread>
#include <mutex>
#include <iostream>
#include <optional>
#include <queue>
#include <atomic>

constexpr static int productsCount = 1000;

namespace heater {

    class Queue {
    public:
        void push(int value) {
            std::unique_lock /*<std::mutex>*/ lock{mutex}; //начиная с С++17
            queue.push(value); //компилятор сам может вывести <std::mutex>
        }

        std::optional<int> pop() {
            std::optional<int> result;
            std::unique_lock lock{mutex};

            if (!queue.empty()) {
                result = queue.front();
                queue.pop();
            }
            return result;
        }
    private:
        std::mutex mutex;
        std::queue<int> queue;
    };

    void example() {
        Queue queue;
        std::atomic<bool> stopped{};
        int total{};

        auto producer = std::thread([&] () {
            for (int i = 0; i < productsCount; ++i) {
                queue.push(i);
            }
            stopped = true;
        });

        auto consumer = std::thread([&] () {
            bool stop = {};

            while (!stop) {
                auto value = queue.pop();

                if (value) {
                    total += *value;
                } else {
                    stop = stopped;
                }
            }
        });

        producer.join();
        consumer.join();

        std::cout << total << std::endl;
        std::cout << productsCount * (productsCount - 1) / 2 << std::endl;
    }
}

int main() {
    heater::example();
}
