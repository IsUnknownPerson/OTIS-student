#include <map>
#include <unordered_map>
#include <iostream>

// SFINAE

// enable_if

// f<T1, T2>(int x1, float x2);

struct Bar {
    int x;
};

struct EncoderStream {
    static constexpr bool encoder_stream_tag = true;

    EncoderStream& operator<<(int) { return *this; }
};

template<typename Stream, std::enable_if_t<Stream::encoder_stream_tag, bool> = true>
Stream& operator<<(Stream& s, Bar object) {
    return s << object.x;
}

std::ostream& operator<<(std::ostream& s, Bar object) {
    return s << "S { x: " << object.x << "}";
}

template<typename Stream,
         std::enable_if_t<Stream::encoder_stream_tag, bool> = true, 
         typename Container, 
         typename = typename Container::iterator>
    EncoderStream& operator<<(Stream& s, Container const& c) {
        for (auto& elem: c) { // begin(), end(), it++, *it, it == it
            s << elem;
        }
        return s;
    }

// static_asserts
template<typename Stream,
         std::enable_if_t<Stream::encoder_stream_tag, bool> = true, 
         typename K, typename V>
    EncoderStream& operator<<(Stream& s, std::map<K, V> const& c) {
    static_assert(sizeof(K) == -1, "Cannot encode maps");
    return s;
}

template<typename Stream,
         std::enable_if_t<Stream::encoder_stream_tag, bool> = true, 
         typename K, typename V>
    EncoderStream& operator<<(Stream& s, std::unordered_map<K, V> const& c) = delete;

// named requirements

struct Foo {};

int main() {
    std::map<Foo, int> map;
    Foo f{};
    map[f] = 5;

    std::unordered_map<Foo, int> umap;
    // umap[Foo{}] = 5;

    Bar bar;
    EncoderStream s;
    s << bar;
    std::cout << bar;
    
    //s << map;
    //std::unordered_map<int, int> umap;
    //s << umap;
}