#include "GameState.h"

using namespace std;

int main() {

    Tube tube0;
    Tube tube1("Tube 1");
    Tube tube2("Tube 2", {"pink", "green", "blue", "black"});

    GameState board;
    board.add_tube(tube0);
    board.add_tube(tube1);
    board.add_tube(tube2);
    board.init_board();
    board.print_board();

    return 0;
}
