#include <iostream>
#include <vector>
#include <array>
#include <string_view>
#include "line_separator.h"

void asCArray() {
    LineSeparator::out("As c dynamic array");

    // runtime size
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (std::size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    for (const auto &i: vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // std::array too
    std::cout << "First: " << vec.front() << ", last: " << vec.back() << std::endl;
    // all as std::array: [], at, iters


    // const objects are not allowed (elements must be assignable)
    // std::vector<const int> vec2{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
}

void letsConst() {
    LineSeparator::out("const");

    std::vector<int> ann = {12, 24};
    const std::vector<int> bob = {11, 21, 31, 41};
    ann = bob;

    for (const int i: ann) {
        std::cout << i << " ";
    }
    std::cout << std::endl;


    //Const vector
    const std::vector<int> vector_4 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::cout << "bob[2] = " << bob[2] << std::endl;

    //Cannot assign to return value because function 'operator[]' returns a const value
    //const_reference operator[]( size_type pos ) const
    // bob[2] = 25;
}

struct S {
    explicit S(std::string s)
        : s(std::move(s)) {
        std::cout << "Ctor " << this->s << std::endl;
    }

    ~S() {
        std::cout << "Dtor " << s << std::endl;
    }

    S(const S &other)
        : s(other.s) {
        std::cout << "Copy ctor" << s << std::endl;
    }
private:
    std::string s;
};

void realloc() {
    LineSeparator::out("realloc");
    const size_t count = 50;

    // naive push_back
    {
        std::vector<int> vec;
        std::cout << "vec.size(): " << vec.size() << std::endl;

        // Oops... reallocations in for-loop
        for (std::size_t i = 0; i < count; ++i) {
            vec.push_back(i);
        }
    }

    // reserve
    {
        std::vector<int> vec;
        vec.reserve(count);
        std::cout   << "vec.size(): " << vec.size()
                    << "\t vec.capacity(): " << vec.capacity() << std::endl;

        for (std::size_t i = 0; i < count; ++i) {
            vec.push_back(i);
        }
    }

    // resize
    {
        std::vector<int> vec;
        vec.resize(count);
        // or better std::vector<double> vec(count);

        for (std::size_t i = 0; i < count; ++i) {
            // not push_back !
            vec[i] = i;
        }
    }

    LineSeparator::out("emplace_back");
    //emplace_back
    {

        std::vector<double> v;
        v.push_back(1);
        v.emplace_back(1);
    }
    {
        std::vector<S> a;
        std::cout << "push_back" << std::endl;
        a.push_back(S("A"));
    }
    {
        std::cout << "emplace_back" << std::endl;
        std::vector<S> b;
        b.emplace_back("B");
    }

    LineSeparator::out("realloc demo");
    std::vector<S> vec;
    vec.emplace_back("Ann");
    std::cout << "(1)" << std::endl;
    vec.emplace_back("Bob");
    std::cout << "(2)" << std::endl;
    vec.emplace_back("Max");
    std::cout << "(3)" << std::endl;
}

void typicalBugs() {
    std::vector<int> v = {1, 2};
    auto iter = v.begin();
    int* ptr = v.data();

    v.push_back(3);
    // or
    // v.insert(v.begin(), 3);
    // v.insert(v.begin() + 1, 3);

    // UB
    //std::cout << *iter << std::endl;
    //std::cout << *ptr << std::endl;
}

// Common interface problem
template <typename Container>
void traversingContainerElements(const Container& data_container, const std::string_view& msg) {
    std::cout << msg << std::endl;

    std::cout << " by index:\t";
    for (std::size_t i = 0; i < data_container.size(); ++i) {
        std::cout << data_container[i] << " ";
    }
    std::cout << std::endl;

    std::cout << " for-each:\t";
    for (const auto& i: data_container) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << " by iterator:\t";
    for (auto it = data_container.cbegin(); it != data_container.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl;
}

void unification() {
    LineSeparator::out("unification:");

    std::array<int, 10> array_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    traversingContainerElements(array_1, "Array:");

    std::vector<double> vector_2 = {1., 2., 3., 4., 5., 6., 7., 8., 9., 10.};
    traversingContainerElements(vector_2, "Vector:");
}


int main() {
    asCArray();
    letsConst();
    realloc();
    typicalBugs();
    unification();
}