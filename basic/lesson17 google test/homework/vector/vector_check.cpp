#include "mvector.cpp"
#include <iostream>

using namespace std;



struct vector_checks{

    void vector_base_task_check()
    {
       std::cout << "vector base task check:" << std::endl;
        mVector<int> v;

        for(size_t i=0; i<10; ++i){
            v.push_back(i);
        }

        cout << "Vector of " << v.size() << " elements: ";
        for(size_t i=0; i<v.size(); ++i)
            cout << v[i] << " ";
        cout << endl;

        cout << "Vector erraze 3, 5, 7 element. Vector: ";
        v.erase(6);
        v.erase(4);
        v.erase(2);
        for(std::size_t i=0; i<v.size(); ++i)
            cout << v[i] << " ";
        cout << endl;

        cout << "Add front element. Vector: ";
        v.push_front(10);
        for(size_t i=0; i<v.size(); ++i)
            cout << v[i] << " ";
        cout << endl;

        cout << "Add element in the middle. Vector: ";

        v.insert(v.size()/2, 20);
        for(size_t i=0; i<v.size(); ++i)
            cout << v[i] << " ";
        cout << endl;

        cout << "Add back element. Vector: ";
        v.push_back(30);
        for(size_t i=0; i<v.size(); ++i)
            cout << v[i] << " ";
        cout << endl;

        std::cout << "--------------------------\n" << std::endl;
    }

    void vector_move_semantics_rValue_task()
    {
        cout << "vector copy and move semantics check:" << endl;


        mVector<int> vector_first{2,22,222,2222};
        cout << "vector_first:" << endl;
        for(size_t i=0; i<vector_first.size(); ++i)
            cout << vector_first[i] << " ";

        mVector<int> vector_second;
        vector_second = vector_first;    //copy assignment operator
        for(size_t i=0; i<vector_second.size(); ++i)
            cout << vector_second[i] << " ";

        vector_second = {1,11,111,11,3,33,333,33,7,77,777,77}; //move assignment operator
        for(size_t i=0; i<vector_second.size(); ++i)
            cout << vector_second[i] << " ";


        mVector<int> checkCtor1{vector_second}; //copy ctor
        for(size_t i=0; i<checkCtor1.size(); ++i)
            cout << checkCtor1[i] << " ";
        cout << endl;

        mVector<int> checkCtor2 = std::move(vector_second); //move ctor
        //vector_second = nullptr;
        for(size_t i=0; i<checkCtor2.size(); ++i)
            cout << checkCtor2[i] << " ";
        cout << endl;

        std::cout << endl << "--------------------------\n" << std::endl;
    }

    void vector_iterator_task()
    {
        std::cout << "vector initializer_list check:" << std::endl;
        mVector<int> v{1,2,777,4,5};
        for (auto z : v)
            cout << z << " ";
        std::cout << std::endl;

        std::cout << "vector iterator check:" << std::endl;
        mVector<int>::iterator it;
        it = v.begin();
        for (auto i=it; i!=v.end(); ++i)
            cout << *i << " ";
        cout << endl;
        std::cout << "--------------------------\n" << std::endl;
    }


    // outIter<mVector<int>> ff;

};








