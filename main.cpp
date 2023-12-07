#include "fraction.h"

using namespace std;
int main() {
//    uint132_t x(13'000'000'000);
//    uint64_t num = 13'000'000'000;
//    for (int i = 0; i < 6; ++i) {
//        num *= 13;
//        x *= 13;
//        assert(x == num);
//    }
//    cout << to_string(x) << endl;
    Fraction frac;
    frac.Input(cin, 10);
    Print(cout, frac, 10);
}
