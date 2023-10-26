#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>

using namespace std;


template<typename T>
void print_ip(T a)
{
    if (is_same<T, const vector<int>>::value)
        cout << "vector?  why is same not work here" << endl;


    if ((is_same<T, const char *>::value) || (is_same<T, string>::value))
        cout << a << endl;

    else {
        unsigned char *x = (unsigned char *) &a;
        for (int i = sizeof(a) - 1; i >= 0; --i) {
            cout << static_cast<unsigned int>(*(x + i));
            if (i)
                cout << '.';
            else
                cout << endl;
        }
    }

}

template<typename T>
void print_ip(vector<T> a)
{
    size_t i = 0;
    for (; i < a.size() - 1; ++i) {
        cout << a[i] << '.';
    }
    cout << a[i] << endl;
}

template<typename T>
void print_ip(list<T> a)
{
    auto i = a.begin();
    while (i != a.end()) {
        cout << *i;
        ++i;
        if (i != a.end())
            cout << '.';
        else
            cout << endl;
    }
}

template<typename... T>
void print_ip(tuple<T...> a)
{
    std::vector<int> v;
    std::apply([&v](auto... args) { (v.push_back(args), ...); }, a);
    size_t i = 0;
    for (; i < v.size() - 1; ++i)
        cout << v[i] << '.';
    cout << v[i] << endl;
}




int main()
{
    print_ip(int8_t{-1}); // 255
    print_ip(int16_t{0}); // 0.0
    print_ip(int32_t{2130706433}); // 127.0.0.1
    print_ip(int64_t{8875824491850138409}); // 123.45.67.89.101.112.131.41
    print_ip(string{"Hello, World!"});
    print_ip(vector<int>{100, 200, 300, 400});
    print_ip(std::list<short>{400, 300, 200, 100});
    print_ip( std::make_tuple(123, 456, 789, 0) );

    return 0;
}
