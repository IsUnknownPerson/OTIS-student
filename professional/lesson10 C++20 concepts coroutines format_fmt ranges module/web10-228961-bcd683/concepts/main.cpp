#include <map>
#include <unordered_map>
#include <iostream>

template <typename T, typename W>
concept Hashable = requires {
                       std::hash<T>();
                   };

template <std::derived_from<int> K, typename V>
std::unordered_map<K, V> create_map()
{
    return {};
}

struct S
{
};

struct Bar
{
    using iterator = int;
    int x;
};

template <typename Stream>
concept EncoderStreamConcept = Stream::encoder_stream_tag;

template<typename C> requires EncoderStreamConcept<C>
decltype(auto) operator<<(C &s, Bar object)
{
    return s << object.x;
}

std::ostream &operator<<(std::ostream &s, Bar object)
{
    return s << "S { x: " << object.x << "}";
}

struct EncoderStream
{
    static constexpr bool encoder_stream_tag = true;

    EncoderStream &operator<<(int) { return *this; }
};

template <typename C>
concept Container = requires(C c) {
     { c.begin() } -> std::same_as<int>;
     { c.end() } -> std::input_iterator;
};

decltype(auto) operator<<(EncoderStreamConcept auto&s, Container auto const &c)
{
    for (auto &elem : c)
    {
        s << elem;
    }
    return s;
}

// static_asserts
template <typename K, typename V>
decltype(auto) operator<<(EncoderStreamConcept auto &s, std::map<K, V> const &c)
{
    static_assert(sizeof(K) == -1, "Cannot encode maps");
    return s;
}

template <typename K, typename V> requires Hashable<K>
decltype(auto) operator<<(EncoderStreamConcept auto &s, std::unordered_map<K, V> const &c) = delete;

int main()
{
    auto map = create_map<S, int>();
    //map[Foo{}] = 5;

    Bar bar;
    EncoderStream s;
    s << bar;
    std::cout << bar;
    
    // s << map;
    std::unordered_map<int, int> umap;
    //s << umap;
}