#include "initgame.h"
#include "gessing.h"
#include "string"

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

    gessing gues(init.rand_value);

    cout << "you win! attempts = " << gues.attempts;

    init.save_and_print_record(to_string(gues.attempts));



    cout << "\nWrite any symbol + enter to close\n";
    string t;
    cin >> t;
    return 0;
}
