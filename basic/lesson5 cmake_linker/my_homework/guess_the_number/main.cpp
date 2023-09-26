#include "initgame.h"
#include "gessing.h"
#include "string"

#include <array>

using namespace std;



int main(int argc, char** argv)
{
    initgame init;

    if (argc > 1)
    {
        //        cout << "\nargc is: " << argc <<";   argv[1] = " << argv[1] << "\n";
        //        cout << "and argv[1][1] = " << argv[1][1] << "\n";

        if (argv[1][6] == '1')
            init.generate_random(9);
        else if (argv[1][6] == '2')
            init.generate_random(49);
        else if (argv[1][6] == '3')
            init.generate_random(99);
        else
            init.generate_random(99);
    }

//#include <cstring>
//#include <algorithm>
#include <array>
//    char getNthSymbol(const char* cString, size_t n, char defaultSymbol) {
//        if (std::strlen(cString) >= n) { // or maybe = only
//            return cString[n];
//        }
//        return defaultSymbol;
//    }

//    const char level = getNthSymbol(argv[1], 6, '3');
//    const size_t levelId = std::clamp(level, '1', '3') - '1';
//    init.generate_random( std::array{9, 49, 99}[levelId] );
//auto d = array{9, 49, 99}[2] ;   cout << "d = " << d; //d = 99



    gessing gues(init.rand_value);

    cout << "you win! attempts = " << gues.attempts;

    init.save_and_print_record(to_string(gues.attempts));



    cout << "\nWrite any symbol + enter to close\n";
    string t;
    cin >> t;
    return 0;
}
