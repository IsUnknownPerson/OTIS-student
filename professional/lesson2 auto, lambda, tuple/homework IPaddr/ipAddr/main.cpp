#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//#include <map>
#include <list>
#include <set>
#include <tuple>

using namespace std;
using uint_tuple = tuple<unsigned short, unsigned short, unsigned short, unsigned short>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main(int argc, char const *argv[])
{
    try {
        std::vector<std::vector<std::string>> ip_pool;

        if (argc < 2)
            throw std::exception("no file choosed");

        set<string> IPaddrSet;

        ifstream ifs(argv[1]);
        if (!ifs.bad()) {
            //auto x = ifs.rdbuf();
            string temp;

            while (std::getline(ifs, temp, '\n')) {
                IPaddrSet.insert(split(temp, '\t')[0]);
            }
            if (!IPaddrSet.size())
                throw exception("file is empty");

            ifs.close();
        } else
            throw exception("can't read file");

        set<uint32_t> addrSortedUint;
        for (const auto &addr : IPaddrSet) {
            auto IPpartS = split(addr, '.');
            auto IPpartN0 = stoi(IPpartS[0]);
            auto IPpartN1 = stoi(IPpartS[1]);
            auto IPpartN2 = stoi(IPpartS[2]);
            auto IPpartN3 = stoi(IPpartS[3]);
            addrSortedUint.insert(
                ((IPpartN0 << 24) + (IPpartN1 << 16) + (IPpartN2 << 8) + IPpartN3));
        }

        set<uint32_t>::iterator it = addrSortedUint.end();
///*
        for (; it != addrSortedUint.begin(); --it) {
            --it;
            cout << ((*it >> 24) & 0xFF) << '.' << ((*it >> 16) & 0xFF) << '.'
                 << ((*it >> 8) & 0xFF) << '.' << (*it & 0xFF) << endl;
            ++it;
        }
//*/
        it = addrSortedUint.end();
        for (; it != addrSortedUint.begin(); --it) {
            --it;
            if (((*it >> 24) & 0xFF) == 1)
                cout << ((*it >> 24) & 0xFF) << '.' << ((*it >> 16) & 0xFF) << '.'
                     << ((*it >> 8) & 0xFF) << '.' << (*it & 0xFF) << endl;
            ++it;
        }

        it = addrSortedUint.end();
        for (; it != addrSortedUint.begin(); --it) {
            --it;
            if ((((*it >> 24) & 0xFF) == 46) && (((*it >> 16) & 0xFF) == 70))
                cout << ((*it >> 24) & 0xFF) << '.' << ((*it >> 16) & 0xFF) << '.'
                     << ((*it >> 8) & 0xFF) << '.' << (*it & 0xFF) << endl;
            ++it;
        }

        it = addrSortedUint.end();
        for (; it != addrSortedUint.begin(); --it) {
            --it;
            if ((((*it >> 24) & 0xFF) == 46) || (((*it >> 16) & 0xFF) == 46)
                || (((*it >> 8) & 0xFF) == 46) || (((*it) & 0xFF) == 46))
                cout << ((*it >> 24) & 0xFF) << '.' << ((*it >> 16) & 0xFF) << '.'
                     << ((*it >> 8) & 0xFF) << '.' << (*it & 0xFF) << endl;
            ++it;
        }

        //for (const auto &x : addrSortedUint)
        // cout << ((x >> 24)&0xFF) << '.' << ((x >> 16)&0xFF) << '.' << ((x >> 8)&0xFF) << '.' << (x&0xFF) << endl;

        /*
        vector<uint_tuple> IPaddrSorted1;
        IPaddrSorted1.reserve(IPaddrSet.size());
        for (const auto &addr : IPaddrSet) {
            auto IPpartS = split(addr, '.');
            auto IPpartN0 = stoi(IPpartS[0]);
            auto IPpartN1 = stoi(IPpartS[1]);
            auto IPpartN2 = stoi(IPpartS[2]);
            auto IPpartN3 = stoi(IPpartS[3]);

            bool inserted = false;

            if (IPaddrSorted1.size()) {
                for (uint64_t i = 0; i < IPaddrSorted1.size(); ++i) {
                    if (IPpartN0 > get<0>(IPaddrSorted1[i])) {

                            IPaddrSorted1.insert(IPaddrSorted1.begin() + i,
                                                make_tuple(IPpartN0, IPpartN1, IPpartN2, IPpartN3));
                            inserted = true;
                            break;
                    }
                }
                if (!inserted) {
                    IPaddrSorted1.push_back(make_tuple(IPpartN0, IPpartN1, IPpartN2, IPpartN3));
                }

            } else {
                IPaddrSorted1.push_back(make_tuple(IPpartN0, IPpartN1, IPpartN2, IPpartN3));
            }
        }



        for (uint64_t i = 0; i < IPaddrSorted1.size(); ++i) {
            cout << endl;

            cout << get<0>(IPaddrSorted1[i]) << '.' << get<1>(IPaddrSorted1[i]) << '.'
                 << get<2>(IPaddrSorted1[i]) << '.' << get<3>(IPaddrSorted1[i]);
        }
        //cout << '\n' << "IPaddrSorted size: " << IPaddrSorted.size() << endl;
*/
        /*
        std::string line = "91.64.189.22	0	2\n";
        std::vector<std::string> v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
        line = "91.64.189.133	0	2\n";
        v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
        line = "91.64.189.222	0	2\n";
        v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));


        // TODO reverse lexicographically sort

        for (std::vector<vector<string>>::const_iterator ip = ip_pool.cbegin();
             ip != ip_pool.cend();
             ++ip) {
            for (std::vector<string>::const_iterator ip_part = ip->cbegin();
                 ip_part != ip->cend();
                 ++ip_part) {
                if (ip_part != ip->cbegin()) {
                    cout << ".";
                }
                cout << *ip_part;
            }
            cout << endl;
        }
*/
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }

    return 0;
}
