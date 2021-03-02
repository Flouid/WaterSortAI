#include "levels.h"

using namespace std;

int main() {
//    l1();
//    l2();
//    l3();

    // TESTING POUR FUNCTION
    Tube t1("Tube 1");
    Tube t2("Tube 2");
    Tube t3("Tube 3", {"empty", "empty", "dark blue", "red"});
    Tube t4("Tube 4", {"empty", "empty", "red", "dark blue"});
    Tube t5("Tube 5", {"empty", "green", "green", "green"});
    Tube t6("Tube 6", {"empty", "empty", "empty", "green"});

    pour_test(t1, t2);      // invalid, source empty
    pour_test(t3, t4);      // invalid, mismatched colors
    pour_test(t5, t6);      // valid single pour
}