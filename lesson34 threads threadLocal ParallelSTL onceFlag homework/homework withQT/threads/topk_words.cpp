#include "topk_words.h"
#include <thread>
#include <mutex>
#include <condition_variable>

//using Counter = std::map<std::string, std::size_t>;

topk_words::topk_words(int a, char **b)
    : argc{a}, argv{b}
{
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return;// EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();
    Counter freq_dict;

    //    for (int i = 1; i < argc; ++i) {
    //        std::ifstream input{argv[i]};
    //        if (!input.is_open()) {
    //            std::cerr << "Failed to open file " << argv[i] << '\n';
    //            return;// EXIT_FAILURE;
    //        }
    //        count_words(input, freq_dict);
    //    }

/*
    bool predicat = false;
    std::mutex mutex;
    std::mutex mutex2;
    std::unique_lock lck1{mutex};
    std::lock_guard lck2{mutex};
    std::scoped_lock mass_lock(mutex, mutex2);
    //если хоть один занят - ни один не захватит
    #include <shared_mutex>
    std::shared_lock lck3{mutex};//несколько потоков
    //смогут читать(только чтение) общий ресурс
    size_t nthreads = std::thread::hardware_concurrency();

    std::condition_variable cv;
    cv.wait(lck1); //wait должен получить
    //заблокированный(любым способом)! mutex
    // если поток уйдет в ожидание - мутекс
    //отпускается. Заблокируется когда поток продолжится
    cv.wait(lck1, true); //лочит. если там будет false - не лочит
    cv.notify_one();
    cv.notify_all();
    cv.wait_for(std::chrono::seconds(1)) != std::future_status::ready);//урок 32 4.2future_wait
    //пробуждение по предикату или по таймауту. что раньше случится
    cv.wait_until(); //по предикату или когда наступит время
    std::notify_all_at_thread_exit(cv, std::move(lck1));
    //если поток детачнут - в конце он должен оповестить
    //основной поток, что детачнутый доработал.
    //Чтобы детачнутого не грохнули раньше времени
    //если основная программа соберется завершиться

    std::string x = b[1];
    std::thread t1([&/'*input, freq_dict*'/](){this->count_words(x, freq_dict);});
    std::thread t2([&/'*input, freq_dict*'/](){this->count_words(input, freq_dict);});

    t1.join();
    t2.join();
*/

    std::stringstream  input(b[1]);
    count_words(input, freq_dict);
    print_topk(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us" << std::endl;
}

void topk_words::count_words(std::istream& stream, Counter& counter) {
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [/*&counter*/ &](const std::string &s) { ++counter[tolower(s)]; });
}

std::string topk_words::tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void topk_words::print_topk(std::ostream& stream, const Counter& counter, const size_t k) {   
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
                std::begin(words), std::begin(words) + k, std::end(words),
                [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
                std::begin(words), std::begin(words) + k,
                [&stream](const Counter::const_iterator &pair) {
        stream << std::setw(4) << pair->second << " " << pair->first
               << '\n';
    });
}
