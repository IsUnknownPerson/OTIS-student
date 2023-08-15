#include "mlist.cpp"
#include <iostream>

using namespace std;

struct full_linked_list_checks{
    void list_base_task_check()
    {
        std::cout << "Full linked list base task check:" << std::endl;

        mFullList<int> l;

        for(int i=0; i<10; ++i){
            l.push_back(i);
        }

        cout << "Full linked list of " << l.size() << " elements: ";
        for(size_t i=0; i<l.size(); ++i)
            cout << l[i] << " ";
        cout << endl;

        cout << "Full linked list erraze 3, 5, 7 element: ";
        l.erase(6);
        l.erase(4);
        l.erase(2);
        for(size_t i=0; i<l.size(); ++i)
            cout << l[i] << " ";
        cout << endl;

        cout << "Add front element. Full linked list: ";
        l.push_front(10);
        for(std::size_t i=0; i<l.size(); ++i)
            cout << l[i] << " ";
        cout << endl;

        cout << "Add element in the middle. Full linked list: ";
        l.insert(l.size()/2, 20);
        for(size_t i=0; i<l.size(); ++i)
            cout << l[i] << " ";
        cout << endl;

        cout << "Add back element. Full linked list: ";
        l.push_back(30);
        for(std::size_t i=0; i<l.size(); ++i)
            cout << l[i] << " ";
        cout << endl;
        std::cout << "--------------------------\n" << std::endl;
    }

    void list_move_semantics_rValue_task()
    {
        cout << "list copy and move semantics check:" << endl;

        mFullList<int> l1{2,22,222,2222};
        cout << "list_first:" << endl;
        for(size_t i=0; i<l1.size(); ++i)
            cout << l1[i] << " ";

        mFullList<int> l2;
        l2 = l1;    //copy assignment operator
        for(size_t i=0; i<l2.size(); ++i)
            cout << l2[i] << " ";
/*
        l2 = {1,11,111,11,3,33,333,33,7,77,777,77}; //move assignment operator
        for(size_t i=0; i<l2.size(); ++i)
            cout << l2[i] << " ";


        mFullList<int> checkCtor1{l2}; //copy ctor
        for(size_t i=0; i<checkCtor1.size(); ++i)
            cout << checkCtor1[i] << " ";
        cout << endl;

        mFullList<int> checkCtor2 = std::move(l2); //move ctor
        //vector_second = nullptr;
        for(size_t i=0; i<checkCtor2.size(); ++i)
            cout << checkCtor2[i] << " ";
        cout << endl;
*/
        std::cout << endl << "--------------------------\n" << std::endl;
    }

    void list_iterator_task()
    {
        std::cout << "list initializer_list check:" << std::endl;
        mFullList<int> l{1,2,777,4,5};
                for (auto z : l)
                    cout << z << " ";
                std::cout << std::endl;

        std::cout << "list iterator check:" << std::endl;
        mFullList<int>::iterator it;
        it = l.begin();

        for (auto i=it; i!=l.end(); ++i)
        {
            cout << *i << " ";
        }
        std::cout << "\n--------------------------\n" << std::endl;
   }

};





