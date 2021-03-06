#include <fstream>

#include "Solver.h"

using namespace std;

/**
 * Ingests a text file into a vector of tubes that constitutes a game state
 *
 * @param filename string representing filename
 * @return vector of tubes representing gamestate
 */
vector<Tube> ingest_text_file(const string &filename)
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
    return tubes;
}

/**
 * Gets a filename from a user.
 *
 * @return string representing the file name
 */
string get_filename()
{
    string filename;

    cout << "Enter the name of an input text file (w/o .txt): ";
    cin >> filename;
    cin.ignore(); // the \n character

    return filename + ".txt";
}

/**
 * Gets the testing mode from the user.
 *
 * @return boolean representing whether or not testing mode is on.
 */
char get_mode()
{
    char response;

    cout << "Fast or perfect solve? (f/p): ";
    cin >> response;
    cin.ignore(); // the \n character
    cout << endl;

    if (response == 'f' || response == 'p')
        return response;
    else
        exit(1);
}

int main()
{
    Solver solver(ingest_text_file(get_filename()));
    solver.run(get_mode());
}