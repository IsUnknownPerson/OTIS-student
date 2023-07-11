#pragma once
#include <iostream>

template <typename T>
struct Felement{
    Felement* next;
    Felement* prev;
    T value;
};

template <typename T>
struct Selement{
    Selement* next;
    T value;
};

template <typename T>
class mForvardList
{

};

template <typename T>
class mFullList
{
public:
    mFullList() : msize{0}, element{nullptr} {
        _end = new Felement<T>;
    }

    ~mFullList(){
        Felement<T> *current = element;
        Felement<T> *next;// = element->next;

        for (unsigned int i=0; i<(msize); ++i)
        {
            next = current->next;
            delete current;
            current = next;
        }


        //        std::cout << std::endl;
        //        for(int i=0; element<size(); ++i)
        //            std::cout << element[i] << " ";

        //        auto next = element->next;
        //        delete element;

        //        while (next != _end){
        //            next = element->next;
        //            delete next->prev;
        //        }
        //        delete next;


    }

    mFullList(std::initializer_list<T> data): msize{0}, element{nullptr}{

        _end = new Felement<T>;
        _end->next = nullptr;
        _end->prev = nullptr;
        for (auto &l : data){
            push_back(l);
        }

    }


    T& operator[] (size_t index) //operator [] overload, return element by reference to change value
    {
        if (index < 0 || index >= msize)
            throw std::out_of_range("Vector index out of range");

        Felement<T> * temp = element;
        for (unsigned int i=0; i<index; ++i){
            temp = temp->next;
        }
        if (temp == _end)
            ; //TODO ASSERT
        return temp->value;
    }

    void erase(unsigned int index){
        if (index >= msize)
            ; //TODO ASSERT

        Felement<T> * temp = element;
        for (unsigned int i=0; i<index; ++i){
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        --msize;
        delete temp;

    }

    void push_back(T data)
    {
        if(msize == 0){
            ++msize;
            Felement<T> *new_element = new Felement<T>;
            element = new_element;
            element->next = _end;
            element->prev = nullptr;
            element->value = data;
            _end->prev = element;
        }
        else {
            Felement<T> *new_element = new Felement<T>;
            Felement<T> *temp = _end->prev;



            //            for (; temp->next != _end;)
            //                temp = temp->next;

            auto prewel = temp;
            temp->next = new_element;
            temp = temp->next;
            temp->prev = prewel;
            temp->next = _end;
            _end->prev = temp;
            temp->value = data;
            ++msize;
        }
    }

    void insert(unsigned int index, T data)
    {
        if(((msize == 0) && (index == 0)) ||
                (index == msize))
        {
            push_back(data);
            return;
        }

        Felement<T> *new_element = new Felement<T>;
        Felement<T> *temp = element;

        for (unsigned int i=0; i<index-1; ++i)
            temp = temp->next;

        auto prewel = temp;
        auto nextel = temp->next;

        prewel->next = new_element;
        new_element->prev = temp;
        new_element->next = nextel;
        new_element->value = data;
        nextel->prev = new_element;

        if (index == msize)
            _end->prev = new_element;
        ++msize;
    }


    void push_front(T data)
    {
        if(msize == 0){
            push_back(data);
            return;
        }
        Felement<T> *new_element = new Felement<T>;

        element->prev = new_element;
        new_element->next = element;
        element = new_element;
        element->prev = nullptr;
        element->value = data;
        ++msize;
    }

    int size() const {
        return msize;
    }




public:
    struct iterator {
        iterator(Felement<T> *b = nullptr) {
            begin = b;
        }

        T operator *() {
            return begin->value;
        }

        Felement<T> operator ++() {
            //TODO assert
            //            if (begin == nullptr)
            //                static_assert


            begin = begin->next;
            return *begin;
        }

        bool operator !=  (const iterator &over) {
            return begin != over.begin;
        }

    private:
        Felement<T> *begin;
    };

    iterator begin(){
        return iterator(element);
    }

    iterator end() const {

        //        iterator temp = iterator(element);
        //        iterator temp2 = iterator(element);
        //        while (temp != nullptr){
        //            temp2 = temp;
        //            ++temp;
        //        }
        //        return temp2;
        return iterator(_end);
    }


private:
    int msize;
    Felement<T> *element;
    Felement<T> *_end;
};



