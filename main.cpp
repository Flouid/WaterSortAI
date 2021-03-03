#include <fstream>

#include "GameState.h"
#include "Solver.h"

using namespace std;

GameState ingest_text_file(const string &filename)
{
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "The file could not be opened\n";
        return GameState();
    }

    Tube t;
    // checks if there are any valid tubes to read in the file
    if (!(in >> t)){
        cout << "The file has no valid tubes to read\n";
        return GameState();
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

int main()
{
    string filename;

    cout << "Enter the name of an input file: ";
    cin >> filename;
    cin.ignore(); // the \n character

    Solver solver(ingest_text_file(filename));
    solver.run();
}