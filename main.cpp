#include <fstream>

#include "GameState.h"
#include "Solver.h"

using namespace std;

GameState ingest_text_file(const string &filename)
{
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "The file could not be opened\n";
        exit(1);
    }

    Tube t;
    // checks if there are any valid tubes to read in the file
    if (!(in >> t)){
        cout << "The file has no valid tubes to read\n";
        exit(1);
    }

    // loops through every tube and keeps track of them
    vector<Tube> tubes;
    while (true) {
        tubes.push_back(t);
        if (!(in >> t)) {
            break;
        }
    }

    // create a gamestate from all of the tubes and return it.
    return GameState(tubes);
}

void solve_from_text_file()
{
    string filename;

    cout << "Enter the name of an input text file (w/o .txt): ";
    cin >> filename;
    cin.ignore(); // the \n character

    // blank line
    cout << endl;

    Solver solver(ingest_text_file(filename + ".txt"));
    solver.run();

    solver.print_tree();

    cout << "The generated tree had " << solver.count_nodes() << " nodes\n";
}

int main()
{
    solve_from_text_file();
}