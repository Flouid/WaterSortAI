#include "levels.h"
#include "solver.h"

using namespace std;

int main() {
    l1();
    l2();
    l3();

    // TESTING POUR FUNCTION

    // invalid, source empty
    pour_test(Tube(), Tube());
    // invalid, mismatched colors
    pour_test(Tube({"empty", "empty", "dark blue", "red"}),
              Tube({"empty", "empty", "red", "dark blue"}));
    // invalid, target full
    pour_test(Tube({"empty", "green", "green", "green"}),
              Tube({"green", "dark blue", "red", "black"}));
    // valid single pour
    pour_test(Tube({"empty", "empty", "empty", "green"}),
              Tube({"empty", "green", "green", "green"}));
    // valid double pour
    pour_test(Tube({"empty", "green", "green", "red"}), Tube("Tube"));
    // valid 4 slot pour
    pour_test(Tube({"green", "green", "green", "green"}), Tube("Tube"));

    // TESTING GET_NUM_MOVES

    // l1
    num_valid_pours_test(GameState(
            {Tube("Tube 0", {"empty", "empty", "empty", "orange"}),
             Tube("Tube 1", {"empty", "orange", "orange", "orange"})}));
    // l2
    num_valid_pours_test(GameState(
            {Tube("Tube 0", {"orange", "dark blue", "orange", "dark blue"}),
             Tube("Tube 1", {"dark blue", "orange", "dark blue", "orange"}),
             Tube("Tube 2")}));
    // l3
    GameState state_l3(
            {Tube("Tube 0", {"dark blue", "red", "orange", "dark blue"}),
             Tube("Tube 1", {"dark blue", "red", "orange", "orange"}),
             Tube("Tube 2", {"red", "orange", "dark blue", "red"})});
    state_l3.init_board();
    num_valid_pours_test(state_l3);

    // TESTING IS_GAME_COMPLETE

    GameState solved_test(
            {Tube("Tube 0", {"dark blue", "dark blue", "dark blue", "dark blue"}),
             Tube("Tube 1", {"orange", "orange", "orange", "orange"}),
             Tube("Tube 2", {"pink", "pink", "pink", "pink"}),
             Tube("Tube 3", {"red", "red", "red", "red"})});
    solved_test.init_board();
    is_game_complete_test(solved_test);
}