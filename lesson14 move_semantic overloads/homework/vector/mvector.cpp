#include <iostream>
#include <limits>

template <typename T>
class mVector
{
public:
    mVector() : msize{0}, mcapacity{0}, region{nullptr}{}

    mVector(std::initializer_list<T> data): msize{0}, mcapacity{0}, region{nullptr}{
        msize = data.size();
        mcapacity = 2*msize;
        if (mcapacity){
            T *new_region = new T[mcapacity];
            region = new_region;
            size_t i = 0;
            for (auto &v : data){
                region[i] = v; ++i;
            }
        }
    }

    ~mVector(){
        //if(region) //nullptr можно удалять безболезненно
        delete [] region;
    }


    //move ctor
    mVector(const mVector  &rhs ) {
        std::cout << "\nvector copy ctor" << std::endl;
        T *new_region = new T[rhs.mcapacity];

        for (size_t i=0; i<rhs.msize; ++i)
           new_region[i] = rhs.region[i];

        region = new_region;
        msize = rhs.msize;
        mcapacity = rhs.mcapacity;
    }

    //copy ctor
    mVector(mVector &&rhs) noexcept{
        std::cout << "vector move ctor" << std::endl;
        region = rhs.region;
        msize = rhs.msize;
        mcapacity = rhs.mcapacity;
        rhs.region = nullptr;
        //rhs = nullptr;
    }

    //copy assignment operator
    mVector& operator = (mVector &rhs){
        std::cout << std::endl << "copy assignment operator" << std::endl;
        T *new_region = new T[rhs.mcapacity];

        for (size_t i=0; i<rhs.msize; ++i)
            new_region[i] = rhs[i];

        region = new_region;
        msize = rhs.msize;
        mcapacity = rhs.mcapacity;
        //rhs = nullptr;
        return *this;
    }


    T& operator[] (size_t index) //operator [] overload, return element by reference to change value
    {
        if (/*index < 0 ||*/ index >= msize)
            throw std::out_of_range("Vector index out of range");
        return region[index];
    }


    mVector& operator = (mVector &&rhs) noexcept{
        std::cout << std::endl << "move assignment operator" << std::endl;

        delete region;
        msize = rhs.msize;
        mcapacity = rhs.mcapacity;
        region = rhs.region;
        rhs.region = nullptr;
      //  rhs =  nullptr;
        return *this;
    }


    size_t size(){
        return msize;
    }

    size_t capacity(){
        return mcapacity;
    }

    void insert(size_t pos, T data)
    {
        if (pos>msize)
            throw std::out_of_range("Vector is too short for insert");
        else if(!mcapacity){
            ++mcapacity;
            T *new_region = new T[mcapacity];
            region = new_region;
        }
        else if (msize == mcapacity){
            if (mcapacity >= std::numeric_limits<size_t>::max() / 2)
                throw std::out_of_range("Vector is too long");
            mcapacity *= 2;
            T *new_region = new T[mcapacity];

            for (size_t i=0; i!=msize; ++i )
                new_region[i] = region[i];

            delete []region;
            region = new_region;
        }

        //I was too lazy to immediately fill in the vector
        //correctly in case of relocation
        ++msize;
        for (size_t i=msize; i!=(pos-1); --i )
            region[i+1] = region[i];
        region[pos] = data;

    }

    void push_front(T data){
        if(!mcapacity){
            ++mcapacity;
            T *new_region = new T[mcapacity];
            region = new_region;
        }
        else if (msize == mcapacity)
        {
            if (mcapacity >= std::numeric_limits<size_t>::max() / 2)
                throw std::out_of_range("Vector is too long");
            mcapacity *= 2;
            T *new_region = new T[mcapacity];

            for (size_t i=0; i!=msize; ++i )
                new_region[i+1] = region[i];

            delete []region;
            region = new_region;
        }
        else {
            for (size_t i=msize+1; i>0; --i )
                region[i] = region[i-1];
        }
        region[0] = data;
        ++msize;
    }

    void push_back(T data){
        if(!mcapacity){
            ++mcapacity;
            T *new_region = new T[mcapacity];
            region = new_region;
        }
        else if (msize == mcapacity){
            if (mcapacity >= std::numeric_limits<T>::max() / 2)
                throw std::out_of_range("Vector is too long");
            mcapacity *= 2;
            T *new_region = new T[mcapacity];

            for (size_t i=0; i!=msize; ++i )
                new_region[i] = region[i];

            delete []region;
            region = new_region;
        }
        region[msize] = data;
        //*(region + size) /* sizeof(int)*size)*/ = d;
        ++msize;
    }

    void erase (size_t index)
    {
        for (size_t i = index; i<msize; ++i)
            region[i] = region[i+1];
        --msize;
    }

public:
    struct iterator {
        iterator(T *b = nullptr) {
            begin = b;
        }

        T operator *() {
            return *begin;
        }

        T operator ++() {
            begin++;
            return *(begin);
        }

        bool operator !=  (const iterator &over) {
            return begin != over.begin;
        }

    private:
        T* begin;
    };


    iterator begin(){
        return iterator(region);
    }

    iterator end(){
        return iterator(region + msize);
    }



private:
    size_t msize;
    size_t mcapacity;
    T *region;
};




