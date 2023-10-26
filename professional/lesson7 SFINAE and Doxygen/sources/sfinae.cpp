#include <string>
#include <type_traits>
int main() {

}
/*
namespace motivation {
    struct String {
        String(const char* s): s(s) {};
        String(const std::string& s): s(s) {};
        String(std::string s): s(std::move(s)) {};

        String(const String &other): s{other.s} {}
    private:
        std::string s;
    };

    void example() {
        String ann("Hello, World!");
        String bob = ann;
    }
}

// tmps - Template Metaprogramming Professional Solution (no)
namespace tmps {
    struct String {
        template <class T>
        String(T&& s): s(std::forward<T>(s)) {}

        String(const String &other): s{other.s} {}
    private:
        std::string s;
    };

    void example() {
        String ann("Hello, World!");
        // Compile time error
        //String bob = ann;
    }
}

namespace solution {
    struct String {
        template<typename T, typename =
            typename std::enable_if_t<
                not std::is_same_v<
                    std::remove_reference_t<T>, String
                >,
                void
            >
        >
        String(T&& s): s(std::forward<T>(s)) {}

        String(const String &other): s{other.s} {}
    private:
        std::string s;
    };

    void example() {
        String ann("Hello, World!");
        String bob = ann;
    }
}


int main() {
    motivation::example();
    tmps::example();
    solution::example();
}
*/
