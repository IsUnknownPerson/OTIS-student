#include "gessing.h"


using std::cout;
using std::cin;

gessing::gessing(int rand_value)
{
    int guess;
    do {
    cin >> guess;
        if (cin.fail())
        {
            cin.clear(); // возвращаем cin в 'обычный' режим работы
            cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера

            cout << "It is not number. try again\r\n";
            continue;
        }

        if (guess < rand_value)
            cout << "greater than " << guess << "\r\n";
        else if (guess > rand_value)
            cout << "less than " << guess << "\r\n";
        ++attempts;
    }while (guess != rand_value);
}
