#include <fstream>
#include "levels.h"

using namespace std;

GameState ingest_text_file(const string &filename)
{
    ifstream file;
    file.open(filename);

    return GameState();
}

int main()
{
    string filename;

    cout << "Enter the name of an input file: ";
    cin >> filename;
    cin.ignore(); // the \n character

    GameState state = ingest_text_file(filename);
}