//
// Created by Louis Keith on 3/1/21.
//

#include "levels.h"

void solve_state(const GameState &state)
{
    Solver solver(state);
    solver.run();
}

GameState l1()
{
    GameState state(
            {Tube("Tube 0", {"empty", "empty", "empty", "orange"}),
             Tube("Tube 1", {"empty", "orange", "orange", "orange"})});
    return state;
}

GameState l2()
{
    GameState state(
            {Tube("Tube 0", {"orange", "dark blue", "orange", "dark blue"}),
             Tube("Tube 1", {"dark blue", "orange", "dark blue", "orange"}),
             Tube("Tube 2")});
    return state;
}

GameState l3()
{
    GameState state(
            {Tube("Tube 0", {"dark blue", "red", "orange", "dark blue"}),
             Tube("Tube 1", {"dark blue", "red", "orange", "orange"}),
             Tube("Tube 2", {"red", "orange", "dark blue", "red"})});
    state.init_board();
    return state;
}

GameState l4()
{
    GameState state(
            {Tube("Tube 0", {"orange", "orange", "red", "dark blue"}),
             Tube("Tube 1", {"red", "dark blue", "red", "dark blue"}),
             Tube("Tube 2", {"orange", "red", "dark blue", "orange"})});
    state.init_board();
    return state;
}

GameState l5()
{
    GameState state(
            {Tube("Tube 0", {"pink", "dark blue", "orange", "lime"}),
             Tube("Tube 1", {"pink", "dark blue", "lime", "orange"}),
             Tube("Tube 2", {"red", "orange", "red", "pink"}),
             Tube("Tube 3", {"dark blue", "red", "pink", "orange"}),
             Tube("Tube 4", {"dark blue", "red", "lime", "lime"})});
    state.init_board();
    return state;
}

GameState l6()
{
    GameState state(
            {Tube("Tube 0", {"lime", "lime", "lime", "red"}),
             Tube("Tube 1", {"lime", "pink", "red", "orange"}),
             Tube("Tube 2", {"orange", "red", "orange", "pink"}),
             Tube("Tube 3", {"pink", "orange", "pink", "dark blue"}),
             Tube("Tube 4", {"red", "dark blue", "dark blue", "dark blue"})});
    state.init_board();
    return state;
}

GameState l7()
{
    GameState state(
            {Tube("Tube 0", {"orange", "red", "orange", "lime"}),
             Tube("Tube 1", {"orange", "red", "dark blue", "dark blue"}),
             Tube("Tube 2", {"orange", "dark blue", "pink", "pink"}),
             Tube("Tube 3", {"dark blue", "red", "pink", "lime"}),
             Tube("Tube 4", {"pink", "lime", "red", "lime"})});
    state.init_board();
    return state;
}

GameState l8()
{
    GameState state(
            {Tube("Tube 0", {"dark blue", "lime", "orange", "lime"}),
             Tube("Tube 1", {"orange", "pink", "pink", "orange"}),
             Tube("Tube 2", {"red", "dark blue", "red", "pink"}),
             Tube("Tube 3", {"pink", "lime", "red", "dark blue"}),
             Tube("Tube 4", {"orange", "red", "lime", "dark blue"})});
    state.init_board();
    return state;
}

GameState l9()
{
    GameState state(
            {Tube("Tube 0", {"pink", "dark blue", "red", "pink"}),
             Tube("Tube 1", {"orange", "lime", "lime", "red"}),
             Tube("Tube 2", {"pink", "orange", "orange", "red"}),
             Tube("Tube 3", {"dark blue", "lime", "red", "pink"}),
             Tube("Tube 4", {"dark blue", "dark blue", "orange", "lime"})});
    state.init_board();
    return state;
}

GameState l10()
{
    GameState state(
            {Tube("Tube 0", {"dark blue", "lime", "dark blue", "pink"}),
             Tube("Tube 1", {"red", "pink", "black", "orange"}),
             Tube("Tube 2", {"lime", "light blue", "light blue", "dark blue"}),
             Tube("Tube 3", {"lime", "orange", "orange", "pink"}),
             Tube("Tube 4", {"red", "lime", "black", "black"}),
             Tube("Tube 5", {"light blue", "light blue", "red", "dark blue"}),
             Tube("Tube 6", {"black", "orange", "pink", "red"})});
    state.init_board();
    return state;
}