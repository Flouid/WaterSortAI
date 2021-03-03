#include "levels.h"

using namespace std;

void invalid_tube_init()
{
    Tube t1("Tube 1", {"green", "blue", "black", "empty"});
    GameState board;
    board.add_tube(t1);
    board.print_board();
}

int main()
{
    GameState state = l107();
    solve_state(state);
}