#include <thread>
#include <mutex>
#include <iostream>
#include <optional>
#include <queue>
#include <condition_variable>

constexpr static int productsCount = 1000;

namespace cv {

    class Queue {
    public:
        void push(int value) {
            std::unique_lock lock{mutex};
            queue.push(value);
            cv.notify_one();
        }

        /** @brief Takes entry with waiting is case of empty queue.
         *  @param entry result entry.
         *  @note This is blocking function!
         *  @return false in case of empty stopped queue
         */
        bool pop(int& value) {
            std::unique_lock lock{mutex};
            cv.wait(lock, [this] () {
                return !queue.empty() || stopped;
            }); //проверяем предикатом не ложное ли пробуждение
            //редко бывают ложные пробуждения, но бьют всегда больно
            //предикат указывается вторым параметром: !queue.empty() || stopped
            // предикат - то что вернет true или false
            //если никто не пробудил, то дальше cv.wait не попадем

            bool noMore = queue.empty() && stopped;

            if (!queue.empty()) {
                value = queue.front();
                queue.pop();
            }
            return !noMore;
        }

        /** @brief Notificates all threads to unblock them.
         */
        void stop() {
            std::unique_lock lock{mutex};
            stopped = true;
            cv.notify_all(); // (!) all
        }
    private:
        std::condition_variable cv;
        std::mutex mutex;
        std::queue<int> queue;
        bool stopped{};
    };

    void example() {
        Queue queue;
        int total{};

        auto producer = std::thread([&] () {
            for (int i = 0; i < productsCount; ++i) {
                queue.push(i);
            }
            queue.stop();
        });

        auto consumer = std::thread([&] () {
            int value{};

            while (queue.pop(value)) {
                total += value;
            }
        });

        producer.join();
        consumer.join();

        std::cout << total << std::endl;
        std::cout << productsCount * (productsCount - 1) / 2 << std::endl;
    }
}

int main() {
    cv::example();
}
