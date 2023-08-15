// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>
#include <thread>
#include <future>


const size_t TOPK = 10;


using Counter = std::map<std::string, std::size_t>;
//  Counter counter;

inline std::string tolower(const std::string &str);

//std::vector<Counter::const_iterator> count_words(std::istream& stream, Counter &counter);

Counter count_words2(char*);


//std::vector<Counter::const_iterator> sort_words(const Counter&, const size_t k);

void merge_and_print (std::ostream& stream,
                      std::vector<Counter> &);



int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    //std::promise<std::vector<Counter::const_iterator>> p;
    //std::vector<std::promise<std::vector<Counter::const_iterator>>> pp;
    //std::future<std::vector<Counter::const_iterator>> f = p.get_future();
    //std::vector<std::future<std::vector<Counter::const_iterator>>> ff;
    std::vector<std::future<Counter>> tasks;

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Counter> dicts;

    for (int i = 1; i < argc; ++i)
    {
        tasks.push_back(std::async(std::launch::async, count_words2, argv[i]));
    }

    for (size_t i=0; i<tasks.size(); ++i)
        tasks[i].wait();
    for (size_t i=0; i<tasks.size(); ++i)
        dicts.push_back(tasks[i].get());

    merge_and_print(std::cout, dicts);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_mks = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto elapsed_s = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_mks.count() << "us = ";
    std::cout << elapsed_ms.count() << "ms = ";
    std::cout << elapsed_s.count() << "s\n";
}

void merge_and_print (std::ostream& stream,
                      std::vector<Counter> &dicts)
{
    for (size_t i=1; i<dicts.size(); ++i)
    {
        for (auto it = dicts[i].begin(); it != dicts[i].end(); it++) //или так: for (auto &it : dicts[i]){
        {
            auto x = dicts[0].find(it->first);                      //и тут тогда auto x = dicts[0].find(it.first);
            if (x != dicts[0].end())   //(x->first != "")
                x->second += it->second;
            else
                dicts[0].insert({it->first, it->second});
        }
    }


    std::vector<Counter::const_iterator> words;
    words.reserve(dicts[0].size());


        for (auto it = std::cbegin(dicts[0]); it != std::cend(dicts[0]); ++it) {
            words.push_back(it);
        }


    std::partial_sort(
                std::begin(words), std::begin(words) + TOPK, std::end(words),
                [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
                std::begin(words), std::begin(words) + TOPK,
                [&stream](const Counter::const_iterator &pair) {
        stream << std::setw(4) << pair->second << " " << pair->first
               << '\n';
    });
  /*  */
}


std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

/*
std::vector<Counter::const_iterator> count_words(std::istream& stream, Counter &counter) {

    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string &s) { ++counter[tolower(s)]; });

    return sort_words(std::move(counter), TOPK);
}
*/

Counter count_words2(char* argv) {

    Counter counter;

    std::ifstream input{argv};
    if (!input.is_open()) {
        std::cerr << "Failed to open file " << argv << '\n';
        return counter;
    }

    std::for_each(std::istream_iterator<std::string>(input),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string &s) { ++counter[tolower(s)]; });

    //sort_words(std::move(counter), TOPK);

    return counter;
}

/*
std::vector<Counter::const_iterator> sort_words(const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
                std::begin(words), std::begin(words) + k, std::end(words),
                [](auto const &lhs, auto const &rhs) { return lhs->second > rhs->second; });

    return words;
}
*/

