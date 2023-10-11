#include <tuple>
#include <iostream>

struct A {
    int i;
    double d;

    bool operator<(A const& other) const {
        return std::tie(i, d) < std::tie(other.i, other.d);
    }

    bool operator>(A const& other) const {
        return std::tie(i, d) > std::tie(other.i, other.d);
    }

    bool operator<=(A const& other) const {
        return !(*this > other);
    }

    bool operator>=(A const& other) const {
        return !(*this < other);
    }

    bool operator==(A const& other) const {
        return std::tie(i, d) == std::tie(other.i, other.d);
    }

    bool operator!=(A const& other) const {
        return !(*this == other);
    }
};

struct B {
    int i;
    double d;

    int cmp(B const& other) const {
        if (std::tie(i, d) < std::tie(other.i, other.d)) {
            return -1;
        }
        if (std::tie(i, d) == std::tie(other.i, other.d)) {
            return 0;
        }
        if (std::tie(i, d) > std::tie(other.i, other.d)) {
            return 1;
        }
        std::terminate();
    }

    bool operator<(B const& other) const {
        return cmp(other) < 0;
    }

    bool operator>(B const& other) const {
        return cmp(other) > 0;
    }

    bool operator<=(B const& other) const {
        return cmp(other) <= 0;
    }

    bool operator>=(B const& other) const {
        return cmp(other) >= 0;
    }

    bool operator==(B const& other) const {
        return cmp(other) == 0;
    }

    bool operator!=(B const& other) const {
        return cmp(other) != 0;
    }
};

struct C {
    int i;
    double d;

    int operator<=>(C const& other) const {
        if (std::tie(i, d) < std::tie(other.i, other.d)) {
            return -1;
        }
        if (std::tie(i, d) == std::tie(other.i, other.d)) {
            return 0;
        }
        return 1;
    }

    // if operator<=> is not not defaulted, operator== and operator!= are not generated
    bool operator==(C const& other) const = default;
};

struct D {
    int i;
    double d;

    auto operator<=>(D const& other) const = default;

    // a defaulted <=> overload will also allow the type to be compared with <, <=, >, and >=. 
    // if operator<=> is defaulted and operator== is not declared at all,
    // then operator== is implicitly defaulted. 
};

int main() {
    static_cast<void>(C{} < C{});
    static_cast<void>(C{} < C{});
    static_cast<void>(C{} <= C{});
    static_cast<void>(C{} >= C{});
    //static_cast<void>(C{} == C{});
    //static_cast<void>(C{} != C{});

    static_cast<void>(D{} < D{});
    static_cast<void>(D{} < D{});
    static_cast<void>(D{} <= D{});
    static_cast<void>(D{} >= D{});
    static_cast<void>(D{} == D{});
    static_cast<void>(D{} != D{});

    static_assert(std::is_same_v<decltype(D{} <=> D{}), std::partial_ordering>);
}

// std::total_ordering std::partial_ordering 
// 
// total ordering
// "abc" == "abc"
// 
// weak ordering
// "abC" == "ABC"
//
// partial ordering
// NaN
