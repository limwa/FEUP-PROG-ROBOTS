#include "utils.h"
#include <fstream>
#include <vector>

using namespace std;

void displayMenu() {  //Displays inicial menu
    input::clear_screen();

    cout << ".______________________________________________________.\n"
         << "|                                                      |\n"
         << "|                                                      |\n"
         << "|                                                      |\n"
         << "|       .___  ___.  _______ .__   __.  __    __        |\n"
         << "|       |   \\/   | |   ____||  \\ |  | |  |  |  |       |\n"
         << "|       |  \\  /  | |  |__   |   \\|  | |  |  |  |       |\n"
         << "|       |  |\\/|  | |   __|  |  . `  | |  |  |  |       |\n"
         << "|       |  |  |  | |  |____ |  |\\   | |  `--'  |       |\n"    
         << "|       |__|  |__| |_______||__| \\__|  \\______/        |\n"
         << "|                                                      |\n"
         << "|                                                      |\n"
         << "|                                                      |\n"
         << "|                                                      |\n"
         << "|                       1) Rules                       |\n"
         << "|                       2) Play                        |\n"
         << "|                       0) Exit                        |\n"
         << "|                                                      |\n"
         << "|                                                      |\n"
         << "|                                                      |\n"
         << "|                                                      |\n"
         << "|______________________________________________________|\n";

                                          

    cout << endl;
}

void displayRules() {  //Displays rules of the game
    input::clear_screen();

    cout << "            _              \n"
         << " _ __ _   _| | ___  ___    \n"
         << "| '__| | | | |/ _ \\/ __|  \n"
         << "| |  | |_| | |  __/\\__ \\ \n"
         << "|_|   \\__,_|_|\\___||___/ \n\n\n";
                         
    
    cout << "The player is placed in a maze made up of high-voltage fences and posts.\n"
         << "There are also some interceptor robots that will try to destroy the player.\n"
         << "If the player touches the maze or any of these robots, that is the end of the game (and the player!).\n"
         << "The robots are also destroyed when they touch the fences/posts or when they collide with each other.\n\n"
 
         << "Ever time the player moves in any direction (horizontally, vertically, or diagonally) to a contiguous cell,\n"
         << "each robot moves one cell closer to the new player's location, in whichever direction is the shortest path.\n"
         << "The robots have no vision sensors but they have an accurate odour sensor that allows them to follow the player!\n\n"
 
         << "There is one hope: make the robots hit the maze or each other. If all of them are destroyed, the player wins.\n";

    cout << endl;
}

bool readMap(unsigned int number, vector<vector<char>> &result) {  //Stores chosen map in 2D vector
    const static string maze_str = "MAZE_";
    const static string txt_str = ".TXT";

    string file_name = to_string(number);
    if (number < 10)
        file_name.insert(file_name.begin(), '0');  //Transforms single digit numbers into XX format

    file_name.insert(0, maze_str);
    file_name.append(txt_str);  //Gets file name to correct format
    
    ifstream file;
    file.open(file_name, ios::in);
    if (!file.is_open()) {
        return false;
    }
        
    char ch;
    bool foundEOF = false;
    while (!foundEOF) {
        vector<char> line;
        while(true) {
            file.get(ch);
            if (file.eof()) {
                foundEOF = true;
                break;
            }

            if (ch == '\n')
                break;

            line.push_back(ch);
        }
        
        if (line.size() > 0)
            result.push_back(line);            
    }
    
    file.close();
    return true;
}

bool loadMap(unsigned int &number, vector<vector<char>> &result) {  //Valildates map number choice
    result.clear();

    function<bool(unsigned int)> fun = [&result] (unsigned int res) { 
        return res < 100 && (res == 0 || readMap(res, result)); 
    };
    
    bool success = input::read_value(
        "Please select a map to play on (0 to return to menu): ",
        "The number must be between 1 and 99 (and the corresponding file must exist)",
        number,
        fun);

    cout << endl;
    return success;
}

bool playGame() {
    unsigned int map_number;
    vector<vector<char>> map;
    if (!loadMap(map_number, map))
        return false;

    if (map_number == 0)
        return true;

    for (int i = 0; i < map.size(); i++) {
        vector<char> line = map.at(i);
        cout << "Line " << i + 1 << ":";

        for (int j = 0; j < line.size(); j++) {
            char ch = line.at(j);
            cout << " " << ch;
        }

        cout << "/" << endl;
    }

    return true;
}

int main(int, char**) {
    while (true) {
        displayMenu();

        unsigned int option;
        if (!input::read_value("Your option: ", "Your option must be one of 0, 1 or 2", option, [] (auto res) { return res <= 2; }))
            option = 0; // Exits the program
        
        cout << endl;
    
        switch (option) {
            case 0:
                cout << "Bye!" << endl;
                return 0;
                
            case 1:
                displayRules();
                cout << endl << "Press ENTER to continue..." << endl;
                input::wait_for_enter();
                break;
                
            case 2:
                if (!playGame()) {
                    cout << "Bye!" << endl;
                    return 0;
                }
                break;

            default:
                cout << "The power of Christ compels you!" << endl;
                return 1;
        }
    }
}

/* void getMove() {  //nao sei se isto esta bem
    input::read_value("Your move: ", 
    "Your move must be Q, A, Z, W, S, X, E, D, or C.", 
    move, [] (auto res), 
    {return ((res == 'Q') || (res == 'A') || (res == 'Z') || (res == 'W') || (res == 'S') || (res == 'X') || (res == 'E') || (res == 'D') || (res == 'C'))});
} */

