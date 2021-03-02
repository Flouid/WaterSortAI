#include "levels.h"
#include "solver.h"

using namespace std;

int main() {
//    l1();
//    l2();
//    l3();

//    // TESTING POUR FUNCTION

//    // invalid, source empty
//    pour_test(Tube(), Tube());
//    // invalid, mismatched colors
//    pour_test(Tube({"empty", "empty", "dark blue", "red"}),
//              Tube({"empty", "empty", "red", "dark blue"}));
//    // invalid, target full
//    pour_test(Tube({"empty", "green", "green", "green"}),
//              Tube({"green", "dark blue", "red", "black"}));
//    // valid single pour
//    pour_test(Tube({"empty", "empty", "empty", "green"}),
//              Tube({"empty", "green", "green", "green"}));
//    // valid double pour
//    pour_test(Tube({"empty", "green", "green", "red"}), Tube("Tube"));
//    // valid 4 slot pour
//    pour_test(Tube({"green", "green", "green", "green"}), Tube("Tube"));

    // TESTING GET_NUM_MOVES
    GameState board({Tube({"empty", "empty", "empty", "orange"}),
                     Tube({"empty", "orange", "orange", "orange"})});
    board.print_board();
    Solver solver(board);
    cout << "Number of valid pours: " << solver.get_num_valid_pours() << endl;
}