#include <iostream>
#include "move_me_out.h"

using namespace std;


unsigned long fib(unsigned long n)
{
    if (n<2) {
        return n;
    }
    return fib(n-1) + fib(n-2);
}

void f_array(int**, int, int);

void f_array(int **arr, int sizex, int sizey){
    int *p_array=(int*)arr;
    int x=0, y=0;
    //cout << p_array[ y * sizex + x ] << "\r\n"; // [ x ][ y ]
    x=3, y=4;
    //cout << p_array[ y * sizex + x ] << "\r\n"; // [ x ][ y ]

}


int f(int &a, int &b) {
  a = 3;
  b = 4;
  return a + b;
}

int main()
{
    int a = 1;
    int b = 2;
    int c = f(a, a);
    std::cout << a << b << c;




    //cout << "Hello World!" << endl;
    todo_move_me_out();

    //cout << "fibonachi number = " << fib(10) << "\r\n";

    int arr[5][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16},
        {17, 18, 19, 20}
    };
    f_array((int**)arr, 4, 5);


    return 0;
}
