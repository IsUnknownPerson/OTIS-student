#pragma once

#if __has_include(<coroutine>)
#   include <coroutine>
    namespace coro = std;
#elif __has_include(<experimental/coroutine>)
#   include <experimental/coroutine>
    namespace coro = std::experimental;
#else
#   error "Coroutines are not supported"
#endif
