#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;



long work(int, int);



int main()
{
    std::vector<std::future<long>> tasks;
    auto start = std::chrono::high_resolution_clock::now();

    tasks.push_back(std::async(std::launch::async, work, 38, 1));
    tasks.push_back(std::async(std::launch::async, work, 37, 3));
    tasks.push_back(std::async(std::launch::async, work, 37, 4));
    tasks.push_back(std::async(std::launch::async, work, 37, 5));
    tasks.push_back(std::async(std::launch::async, work, 37, 1));
    tasks.push_back(std::async(std::launch::async, work, 37, 2));
    tasks.push_back(std::async(std::launch::async, work, 37, 6));



    for (size_t i=0; i<tasks.size(); ++i)
        tasks[i].wait();
    for (size_t i=0; i<tasks.size(); ++i)
        std::cout << tasks[i].get() << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "elapsed time: "<< elapsed_ms.count() << "ms\n";
    return 0;
}

long work(int n, int b){
    if ( n == 1 || n == 2) return (n -1)*b; //fibonachi
    return (work(n-1, b) + work(n-2, b)); //убрать b, чтоб последовательность фибоначи была
}
