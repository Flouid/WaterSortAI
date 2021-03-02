#include "levels.h"

using namespace std;

int main() {
//    l1();
//    l2();
//    l3();

    // TESTING POUR FUNCTION
    Tube t1("Tube 1");
    Tube t2("Tube 2");
    pour_test(t1, t2);      // invalid, source empty

    Tube t3("Tube 3", {"empty", "empty", "dark blue", "red"});
    Tube t4("Tube 4", {"empty", "empty", "red", "dark blue"});
    pour_test(t3, t4);      // invalid, mismatched colors

    Tube t5("Tube 5", {"empty", "green", "green", "green"});
    Tube t6("Tube 6", {"green", "dark blue", "red", "black"});
    pour_test(t5, t6);      // invalid, target full

    Tube t7("Tube 7", {"empty", "green", "green", "green"});
    Tube t8("Tube 8", {"empty", "empty", "empty", "green"});
    pour_test(t7, t8);      // valid single pour
}