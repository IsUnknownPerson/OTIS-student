#include "list_check.cpp"
#include "vector_check.cpp"
#include <iostream>




int main()
{
    vector_checks vChecks;

    vChecks.vector_base_task_check();
    std::cout << "vector capacity task done" << std::endl;
    std::cout << "--------------------------\n" << std::endl;
    //vChecks.vector_move_semantics_rValue_task();
    vChecks.vector_iterator_task();


    full_linked_list_checks fListChecks;

    fListChecks.list_base_task_check();
    fListChecks.list_iterator_task();









    return 0;
}
