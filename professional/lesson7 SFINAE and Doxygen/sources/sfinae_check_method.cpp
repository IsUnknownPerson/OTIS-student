#include <type_traits>
#include <iostream>
#include <vector>
int main() {

}

/*
struct Point {
    inline int x() const { return 42; };
};
struct QPointD {
    inline double x() const { return 42.; };
};

template<typename T>
struct has_x_method {
    template<typename U>
    static decltype(U().x()) detect(const U&);
    static std::nullptr_t detect(...);
    static constexpr bool value =
        not std::is_same<
            std::nullptr_t,
            decltype(detect(std::declval<T>()))
        >::value;
};

int main() {
    std::cout << std::boolalpha
        << "Pt has x() "<< has_x_method<QPointD>::value << std::endl
        << "Point has x() " << has_x_method<Point>::value << std::endl
        << "vector has x() " << has_x_method<std::vector<int>>::value << std::endl;
}
*/
