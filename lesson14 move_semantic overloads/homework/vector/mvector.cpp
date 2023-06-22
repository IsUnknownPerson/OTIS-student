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
        //std::cout << "mcapacity: " << mcapacity << std::endl;
        if (mcapacity){
            T *new_region = new T[mcapacity];
            region = new_region;
            int i = 0;
            for (auto &v : data){
                region[i] = v;
                //std::cout << "region[" << i << "]: " << region[i] << std::endl;
                ++i;
            }
        }
    }


    ~mVector(){
        if(region)
            delete [] region;
    }

    T& operator[] (T index) //operator [] overload, return element by reference to change value
    {
        if (index < 0 || index >= msize)
            throw std::out_of_range("Vector index out of range");
        return region[index];
    }
    /*
    //copy ctor
    mVector(const mVector &other){
        std::cout << "vector copy ctor" << std::endl;
        region = other.region;
        msize = other.msize;
        mcapacity = other.mcapacity;
    }

    //move ctor
    mVector(mVector &other){
        std::cout << "vector move ctor" << std::endl;
        region = other.region;
        msize = other.msize;
        mcapacity = other.mcapacity;
        delete []region;
        region = nullptr;
    }

    //copy assignment operator
    mVector& operator= (const mVector &rhs){
        std::cout << "copy assignment operator" << std::endl;

        return *this;
    }
*/
    //move assignment operator
    mVector& operator= (mVector const &rhs){
        std::cout << "move assignment operator" << std::endl;
        region = rhs.region;
        msize = rhs.msize;
        mcapacity = rhs.mcapacity;
        return *this;
    }

    int size(){
        return msize;
    }

    int capacity(){
        return mcapacity;
    }

    void insert(int pos, T data)
    {
        if (pos>msize)
            throw std::out_of_range("Vector is too short for insert");
        else if(!mcapacity){
            ++mcapacity;
            T *new_region = new T[mcapacity];
            region = new_region;
        }
        else if (msize == mcapacity){
            if (mcapacity >= std::numeric_limits<T>::max() / 2)
                throw std::out_of_range("Vector is too long");
            mcapacity *= 2;
            T *new_region = new T[mcapacity];

            for (int i=0; i!=msize; ++i )
                new_region[i] = region[i];

            delete []region;
            region = new_region;
        }

        //I was too lazy to immediately fill in the vector
        //correctly in case of relocation
        ++msize;
        for (int i=msize; i!=(pos-1); --i )
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
            if (mcapacity >= std::numeric_limits<T>::max() / 2)
                throw std::out_of_range("Vector is too long");
            mcapacity *= 2;
            T *new_region = new T[mcapacity];

            for (int i=0; i!=msize; ++i )
                new_region[i+1] = region[i];

            delete []region;
            region = new_region;
        }
        else {
            for (int i=msize+1; i>0; --i )
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

            for (int i=0; i!=msize; ++i )
                new_region[i] = region[i];

            delete []region;
            region = new_region;
        }
        region[msize] = data;
        //*(region + size) /* sizeof(int)*size)*/ = d;
        ++msize;
    }

    void erase (int index)
    {
        for (int i = index; i<msize; ++i)
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
        //        bool operator == (const iterator &over) {
        //            return begin == over.begin;
        //        }

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
    int msize;
    int mcapacity;
    T *region;
};




