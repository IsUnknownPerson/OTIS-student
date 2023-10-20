#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif
#include <iostream>
#include <memory>

//operator new overload
void* operator new(std::size_t sz)
{
    std::cout << "new(size_t), size = " << sz << std::endl;
    if (sz == 0)
        ++sz; // avoid std::malloc(0) which may return nullptr on success

    if (void *ptr = std::malloc(sz))
        return ptr;

    throw std::bad_alloc{};
}

void* operator new[](std::size_t sz)
{
    std::cout << "new[](size_t), size = " << sz << std::endl;
    if (sz == 0)
        ++sz; // avoid std::malloc(0) which may return nullptr on success
 
    if (void *ptr = std::malloc(sz))
        return ptr;
 
    throw std::bad_alloc{}; // required by [new.delete.single]/3
}

void* operator new(std::size_t sz, const std::nothrow_t& nothrow_value) noexcept
{
    std::cout << "nothrow new(size_t), size = " << sz << std::endl;
    if (sz == 0)
        ++sz; // avoid std::malloc(0) which may return nullptr on success

    if (void *ptr = std::malloc(sz))
        return ptr;

    return nullptr;
}

void operator delete(void* ptr) noexcept
{
    std::cout << "delete" << std::endl;
    std::free(ptr);
}

void operator delete[](void* ptr) noexcept
{
    std::cout << "delete[]" << std::endl;
    std::free(ptr);
}

struct X
{
    static void* operator new(std::size_t count)
    {
        std::cout << "X::new for size " << count << '\n';
        return ::operator new(count);
    }

    int val;
};

int main(int, char *[]) {
    const int NumberOfInts = 10;

    int* arr = new int[NumberOfInts];

    void* mem = ::operator new(NumberOfInts * sizeof(int));
    int* arr2 = new(mem) int[NumberOfInts];

    int* arr3 = new (std::nothrow) int(6);

    //delete arr3;
    //delete arr2;
    //delete[] arr;

    X* x = new X();

	return 0;
}
