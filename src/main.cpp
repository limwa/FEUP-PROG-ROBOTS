#include <fstream>
#include <string>
#include <iomanip>
#include <bits/stdc++.h>
#include "utils.h"
#include "entities.h"

using namespace std;

time_t game_timer(bool overwrite) {  // Funtion to get playing time
    static time_t start_time;

    if (overwrite)
        return start_time = time(NULL);

    return time(NULL) - start_time;
}

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
 
         << "There is one hope: make the robots hit the maze or each other. If all of them are destroyed, the player wins.\n\n"

         << "The controls are as follows: \n"
         << "-------------\n"
         << "| Q | W | E |\n"
         << "| A | S | D |\n"
         << "| Z | X | C |\n"
         << "-------------" << endl;

    cout << endl;
}

bool readMap(unsigned int number, vector<vector<char>> &result) {  // Stores chosen map in 2D vector
    const static string maze_str = "MAZE_";
    const static string txt_str = ".TXT";

    string file_name = to_string(number);
    if (number < 10)
        file_name.insert(file_name.begin(), '0');  // Transforms single digit numbers into XX format

    file_name.insert(0, maze_str);
    file_name.append(txt_str);  // Gets file name to correct format
    
    ifstream file;
    file.open(file_name, ios::in);
    if (!file.is_open()) {
        return false;
    }
        
    char ch;
    bool found_eof = false;  // EOF will break the program at any time
    unsigned players = 0;
    while (!found_eof) {
        vector<char> line;
        while(true) {
            file.get(ch);
            if (file.eof()) {
                found_eof = true;
                break;
            }

            if (ch == '\n')
                break;
            else if (ch == 'H')  // Makes sure there's at least a player
                players++;

            line.push_back(ch);
        }
        
        if (line.size() > 0)
            result.push_back(line);            
    }
    
    file.close();
    return players == 1;  // Makes sure there's only one player in the map
}

bool loadMap(unsigned int &number, vector<vector<char>> &result) {  // Validates map number choice
    result.clear();

    function<string(unsigned int)> fun = [&result] (unsigned int res) {
        if (res == 0)
            return string();

        if (res >= 100)
            return string("Please specify a number between 1 and 99");

        if (!readMap(res, result))
            return string("A map with that number does not exist");

        return string(); 
    };
    
    bool success = input::read_value(
        "Please select a map to play on (0 to return to menu): ",
        "Please specify a number",
        number,
        fun
    );

    cout << endl;
    return success;
}

bool get_deltas_from_direction(char direction, int &dx, int &dy) {  // Gets direction through vector coordinates
    switch (direction) {
        case 'Q':
            dx = -1;
            dy = -1;
            break;

        case 'W':
            dx = 0;
            dy = -1;
            break;

        case 'E':
            dx = 1;
            dy = -1;
            break;

        case 'A':
            dx = -1;
            dy = 0;
            break;
            
        case 'S':
            dx = 0;
            dy = 0;
            break;

        case 'D':
            dx = 1;
            dy = 0;
            break;

        case 'Z':
            dx = -1;
            dy = 1;
            break;

        case 'X':
            dx = 0;
            dy = 1;
            break;

        case 'C':
            dx = 1;
            dy = 1;
            break;

        default:
            return false;
    }

    return true;
}

bool saveScore(string &player_name, int player_score, unsigned int map_number) {
    const static string maze_str = "MAZE_";
    const static string txt_str = "_WINNERS.TXT";

    string file_name = to_string(map_number);
    if (map_number < 10)
        file_name.insert(file_name.begin(), '0');  // Transforms single digit numbers into XX format

    file_name.insert(0, maze_str);
    file_name.append(txt_str);  // Gets file name to correct format
    
    struct Score {
        string name; 
        int score;
    };

    vector<Score> scores;

    ifstream read_file;  // Opening file for read and write
    read_file.open(file_name, ios::in);  // Reading file

    if (read_file.is_open()) {    
        read_file.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignoring 2 first lines
        read_file.ignore(numeric_limits<streamsize>::max(), '\n');

        while (read_file.good() && !read_file.eof()) {
            input::Name name_struct;
            read_file >> name_struct;

            char sep;
            read_file >> sep;

            int read_score;
            read_file >> read_score;

            read_file.ignore(numeric_limits<streamsize>::max(), '\n');

            if (read_file.peek() != '\n') {
                Score score = { name_struct.name, read_score }; 
                scores.push_back(score);
            }
        }
        
        read_file.close();
    }

    ofstream write_file;
    write_file.open(file_name, ios::trunc);  // Writing to file
    if (!write_file.is_open()) {
        return false;  
    }

    scores.push_back({ player_name, player_score });

    sort(scores.begin(), scores.end(), [] (auto first, auto second) {  
        return first.score < second.score;
    });

    write_file << "Player          - Time\n"; 
    write_file << "----------------------\n"; 

    for (auto score : scores) {
        write_file << score.name;
        for (int i = 0; i < 15 - input::utf8Len(score.name.c_str()); i++)
            write_file << ' ';
            
        write_file << " - ";
        
        for (int i = 0; i < 4 - to_string(score.score).length(); i++)
            write_file << ' ';
            
        write_file << score.score << '\n';
    }   

    write_file << flush;

    write_file.close();
    return true;
}

bool playGame() {
    Map map;  // Defined in entities.h as the vector cointaining the game's map
    unsigned int map_number;
    if (!loadMap(map_number, map))
        return false;

    if (map_number == 0)
        return true;

    Player player;  // Struct defining the player's status
    vector<Robot> robots;  // Vector that will store all robots present in the map

    for (size_t i = 0; i < map.size(); i++) {
        vector<char> line = map.at(i);  // Defining a vector for each line in map
        for (size_t j = 0; j < line.size(); j++) {
            char character = line.at(j);  

            switch (character) {
                case 'R':
                    robots.push_back({
                        static_cast<unsigned int> (robots.size() + 1),  // Increasing vector size if robot is found
                        static_cast<int> (j),
                        static_cast<int> (i),
                        true
                    });
                    break;
                
                case 'H':
                    player = { static_cast<int> (j), static_cast<int> (i), true };  // Assigning position and status to player struct
                    break;

                default:
                    break;
            }          
        }
    }

    game_timer(true);  // Starts timer
    while (true) {
        input::clear_screen();
        for (size_t i = 0; i < map.size(); i++) {  // Prints map to the console
            vector<char> line = map.at(i);
            for (size_t j = 0; j < line.size(); j++) {
                char ch = line.at(j);
                cout << ch;
            }
            cout << endl;
        }

        cout << endl;

        char letter;
        int dx, dy;
        bool is_not_eof = input::read_value(  // Validates player's move
            "Your move: ",
            "Your move must be one of Q, A, Z, W, S, X, E, D, or C",
            letter,
            [player, &map, &dx, &dy] (auto res) {
                if(get_deltas_from_direction(toupper(res), dx, dy) && is_move_valid(player, map, dx, dy))
                    return string();
                else
                    return string("Your move must be one of Q, A, Z, W, S, X, E, D, or C AND must be a valid move");
            }
        );

        cout << endl;

        if (!is_not_eof)
            return false;

        map.at(player.y)[player.x] = ' ';  // Replaces previous place with empty space
        move(player, map, dx, dy);

        for (size_t i = 0; i < robots.size(); i++) {
            Robot &robot = robots.at(i);

            switch (move(robot, map, get_robot_dx(robot, player), get_robot_dy(robot, player))) {  // Moves every robot independently in order
                                                                                                   //Returns 1, 2 or 3 depending on the outcome
                case 2:  // Robot colided with another robot, creating a stump
                    for (size_t j = 0; j < robots.size(); j++) {
                        if (i == j)  // Checking robot's id is not his own
                            continue;

                        Robot &another_robot = robots.at(j);
                        if (robot.x == another_robot.x && robot.y == another_robot.y)
                            another_robot.alive = false;
                    }

                    break;

                case 3:  // Robot colided with player
                    player.alive = false;  // Player's status becomes dead
                    break;

                default:
                    break;
            }
        }

        map.at(player.y)[player.x] = (player.alive ? 'H' : 'h');  // Replacing player with "h" if dead

        if (!player.alive)  // Ending game when player dies
            break;

        bool has_game_ended = true;
        for (auto robot : robots) {
            if (robot.alive)  // Checking if there are robots alive; if so (and player's not dead), game will not end
                has_game_ended = false;
        }

        if (has_game_ended)
            break;
    }

    time_t score = game_timer(false);  // Timestamping game's end

    input::clear_screen();
    for (size_t i = 0; i < map.size(); i++) { // Displays last game frame
        vector<char> line = map.at(i);
        for (size_t j = 0; j < line.size(); j++) {
            char ch = line.at(j);
            cout << ch;
        }
        cout << endl;
    }

    cout << endl;
    
    if (player.alive) {
        cout << "You won :)" << endl;
        cout << "You finished the game in " << score << " seconds" << endl;
    } else {
        cout << "You lost :(" << endl;
    }
    
    cout << endl;
    cout << "Press ENTER to continue..." << endl;
    input::wait_for_enter();

    if (!player.alive)
        return true;

    input::Name name_struct;
    if (!input::read_value("Well done, champion! What's your name? ", "Please specify your name (must have 15 characters or less)", name_struct))
        return false;

    string name = name_struct.name;

    saveScore(name, score, map_number);
    return true;
}

/* void writePoints(double start, string name) {  // Writes winners file
    string ln;
    fstream points;
    points.open ("points.txt", ios::in);

    points << name << setw(10) << " - " << endl;  //indentar direito <<
    points.close();
} */

void displayWinners() {  // Displays winners 
    ifstream file;
    file.open("points.txt", ios::in);  
	if (!file) {
		cout << "No such file";
	}
    
    //display lines
    file.close();
}

int main(int, char**) {
    while (true) {
        displayMenu();

        unsigned int option;
        if (!input::read_value("Your option: ", "Your option must be one of 0, 1 or 2", option, [] (auto res) {
            return (res > 2 ? string("Your option must be one of 0, 1 or 2") : string()); 
        }))
            option = 0; // Exits the program
        
        cout << endl;
    
        switch (option) {
            case 0:  //Exits program
                cout << "    ___            \n"  
                     << "   | _ )_  _ ___   \n"
                     << "   | _ \\ || / -_) \n"
                     << "   |___/\\_, \\___|\n"
                     << "       |__/        \n" << endl;
                return 0;
                
            case 1:  // Displays Rules
                displayRules();
                cout << endl << "Press ENTER to continue..." << endl;
                input::wait_for_enter();
                break;
                
            case 2:  // Starts game sequence
                if (!playGame()) {
                    cout << "    ___            \n"  
                         << "   | _ )_  _ ___   \n"
                         << "   | _ \\ || / -_) \n"
                         << "   |___/\\_, \\___|\n"
                         << "       |__/        \n" << endl;
                    return 0;
                }
                break;

            default:
                cout << "The power of Christ compels you!" << endl;
                return 1;
        }
    }
}
