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
        std::cout << "list move semantics rValue check:" << std::endl;
        std::cout << "ERROR\n";
        std::cout << "--------------------------\n" << std::endl;
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





