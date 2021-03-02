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

    // l1
    GameState board1({Tube({"empty", "empty", "empty", "orange"}),
                     Tube({"empty", "orange", "orange", "orange"})});
    board1.print_board();
    Solver solver1(board1);
    cout << "Number of valid pours: " << solver1.get_num_valid_pours() << endl;

    // l2
    GameState board2({Tube("Tube 1", {"orange", "dark blue", "orange", "dark blue"}),
                      Tube("Tube 2", {"dark blue", "orange", "dark blue", "orange"}),
                      Tube("Tube 3")});
    board2.print_board();
    Solver solver2(board2);
    cout << "Number of valid pours: " << solver2.get_num_valid_pours() << endl;

    // l3
    GameState board3({Tube("Tube 1", {"dark blue", "red", "orange", "dark blue"}),
                      Tube("Tube 2", {"dark blue", "red", "orange", "orange"}),
                      Tube("Tube 3", {"red", "orange", "dark blue", "red"})});
    board3.init_board();
    board3.print_board();
    Solver solver3(board3);
    cout << "Number of valid pours: " << solver3.get_num_valid_pours() << endl;

}