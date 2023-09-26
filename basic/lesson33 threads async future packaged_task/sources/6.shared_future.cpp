#include <iostream>
#include <future>
#include <chrono>
 
int main()
{   
    std::promise<void> ready_promise, t1_ready_promise, t2_ready_promise;
    std::shared_future<void> ready_future(ready_promise.get_future());
 
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
 

    auto fun1 = [&, ready_future]() -> std::chrono::duration<double, std::milli> 
    {
        t1_ready_promise.set_value();
        ready_future.wait(); // waits for the signal from main()
        return std::chrono::high_resolution_clock::now() - start;
    };
 
 
    auto fun2 = [&, ready_future]() -> std::chrono::duration<double, std::milli> 
    {
        t2_ready_promise.set_value();
        ready_future.wait(); // waits for the signal from main()
        return std::chrono::high_resolution_clock::now() - start;
    };
 
    auto fut1 = t1_ready_promise.get_future();
    auto fut2 = t2_ready_promise.get_future();
 
    auto result1 = std::async(std::launch::async, fun1);
    auto result2 = std::async(std::launch::async, fun2);
 
    // wait for the threads to become ready
    fut1.wait();
    fut2.wait();
 
    // the threads are ready, start the clock
    start = std::chrono::high_resolution_clock::now();
 
    // signal the threads to go
    ready_promise.set_value();
 
    std::cout << "Thread 1 received the signal "
              << result1.get().count() << " ms after start\n"
              << "Thread 2 received the signal "
              << result2.get().count() << " ms after start\n";

    /*
     *бонус shared_future: его можно ждать из разных потоков
     *
     Как будет выполняться программа:
     - объявляется - создается все, но не начинает выполняться
     - строчки 31 и 32 создают потоки выполнения fun1 и fun2
      запускает их и они делают работу, все встает на ready_future.wait();
      дальше ждет когда понадобится результат
     - в основном потоке занимаемся чем-то другим
     - если основной поток справился раньше, чем доработали потоки, то
       ждем пока потоки не дорабатают fut1.wait(); и fut2.wait();
     - запрашиваем результат из потоков ready_promise.set_value();
       и потоки разрушаются, сохранив результат
     - используем результат (строчка 44 std::cout)
     */
}




