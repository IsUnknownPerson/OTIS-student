#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <vector>
using namespace std;

/*
template<class T>
struct map_allocator
{
    typedef T value_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;

    map_allocator() noexcept {}
    template<class U>
    map_allocator(const map_allocator<U> &) noexcept
    {
        ;
    };

    T *allocate(std::size_t n) { return static_cast<T *>(::operator new(n * sizeof(T))); }
    void deallocate(T *p, std::size_t n) { ::operator delete(p); }

    template<class Up, class... Args>
    void construct(Up *p, Args &&...args)
    {
        ::new ((void *) p) Up(std::forward<Args>(args)...);
    }

    void destroy(pointer p) { p->~T(); }

    template<class U>
    struct rebind
    {
        typedef map_allocator<U> other;
    };
};

template<class T, class U>
constexpr bool operator==(const map_allocator<T> &, const map_allocator<U> &) noexcept
{
    return true;
}

template<class T, class U>
constexpr bool operator!=(const map_allocator<T> &, const map_allocator<U> &) noexcept
{
    return false;
}
*/

template<class T>
struct m_allocator
{ //алиас для типа
    using value_type = T;

    m_allocator() noexcept {} //конструктор копирования
    template<class U>
    m_allocator(const m_allocator<U> &) noexcept
    {}

    T *allocate(std::size_t n)
    {
        ++quantity;
        if (quantity <= 11)
            ;
        //cout << "quantity: " << quantity << endl;
        else {
            cout << "memory allocation failed in main.cpp " << __LINE__ << endl;
            throw std::bad_alloc{};
        }
        return static_cast<T *>(::operator new(n * sizeof(T)));
    }
    void deallocate(T *p, std::size_t n) { ::operator delete(p); }


    int quantity = 0;
};
template<class T, class U>
constexpr bool operator==(const m_allocator<T> &a1, const m_allocator<U> &a2) noexcept
{
    return true;
}
template<class T, class U>
constexpr bool operator!=(const m_allocator<T> &a1, const m_allocator<U> &a2) noexcept
{
    return false;
}


int main()
{
    cout << "stl map m1 with default allocator----->\n";
    map<int, int> m1;
    for (size_t i = 0; i < 10; ++i) {
        if (i > 0) {
            m1[i] = 1;
            for (size_t j = 1; j <= i; ++j)
                m1[i] *= j;
        } else
            m1[i] = 1;
    }
    for (auto const &el : m1)
        cout << el.first << ' ' << el.second << "; ";
    cout << "\n<-----stl map m1 with default allocator" << endl;


    cout << "\nstl map m2 with my allocator----->\n";
    map<int, int, std::less<int>, m_allocator<pair<const int, int>>> m;

    for (size_t i = 0; i < 10; ++i) {
        if (i > 0) {
            m[i] = 1;
            for (size_t j = 1; j <= i; ++j)
                m[i] *= j;
        } else
            m[i] = 1;
    }
    for (auto const &el : m)
        cout << el.first << ' ' << el.second << "; ";
    cout << "\n<-----stl map m2 with my allocator" << endl;



    return 0;
}
