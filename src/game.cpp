#include <fstream>
#include <string>
#include <iomanip>
#include <bits/stdc++.h>
#include <exception>
#include <stdio.h>
#include <unistd.h>
#include "entities.h"
#include "game.h"

namespace info {

    /**
     * @brief Displays the game's main menu.
     */
    void menu() {
        screen::clear();

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

    /**
     * @brief Displays the game's rules.
     */
    void rules() {
        screen::clear();

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
            << "-------------\n";

        cout << endl;
    }

    /**
     * @brief Displays the game's exit message.
     */
    void bye() {
        cout << "    ___            \n"  
             << "   | _ )_  _ ___   \n"
             << "   | _ \\ || / -_) \n"
             << "   |___/\\_, \\___|\n"
             << "       |__/        \n";

        cout << endl;
    }
} // namespace info

namespace keyboard {

    /**
     * @brief Blocks execution until the user presses the RETURN key.
     */
    void wait_for_enter() {
        cout << "Press ENTER to continue..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    /**
     * @brief Auxiliary function.
     */
    template <typename T>
    bool read_value_interactive(const string prompt, const string warning, T &result, const function<bool(T)> validator) {
        cout << "? " << prompt << flush;
        while (true) {
            // Is true if, and only if, all the content present on the line is of the type T
            bool is_input_valid = false;
            const char *error = warning.c_str();

            try {
                is_input_valid = cin.peek() != '\n' 
                    && cin >> result && cin.peek() == '\n'
                    && validator(result);
            } catch (const char *exception) {
                error = exception;
            }

            // Clear the buffer
            // We do this to avoid having "123a[EOF]" trigger the loop more than once.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (is_input_valid) {
                cout << "\x1B[F\x1B[G✓\x1B[" << prompt.length() + 3 << "G\x1B[K" << result << "\n\x1B[K" << flush;
                return true;
            } else {
                if (!cin.eof())
                    cout << ">> " << error << "\x1B[F";

                cout << "\x1B[" << prompt.length() + 3 << "G\x1B[K";

                if (cin.eof()) {
                    cout << "EOF\n\x1B[F\x1B[G×\x1B[E\x1B[K" << flush;
                    return false;
                }
            }
        }
    }

    /**
     * @brief Auxiliary function.
     */
    template <typename T>
    bool read_value_dinossaur(const string prompt, const string warning, T &result, const function<bool(T)> validator) {
        while (true) {
            cout << "? " << prompt << flush;

            bool is_input_valid = false;
            const char *error = warning.c_str();

            try {
                is_input_valid = cin.peek() != '\n' 
                    && cin >> result && cin.peek() == '\n'
                    && validator(result);
            } catch (const char *exception) {
                error = exception;
            }
                
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (is_input_valid) {
                return true;
            } else {
                if (cin.eof()) {
                    cout << "EOF" << endl;
                    return false;
                } else {
                    cout << "\u26A0 " << error << endl;
                }
            }
        }
    }

    /**
     * @brief Auxiliary function.
     */
    template <typename T>
    inline bool read_value_adaptive(const string prompt, const string warning, T &result, const function<bool(T)> validator) {
        if (isatty(fileno(stdin)) && isatty(fileno(stdout)))
            return read_value_interactive<T>(prompt, warning, result, validator);
        
        return keyboard::read_value_dinossaur<T>(prompt, warning, result, validator);
    }

    /**
     * @brief Prompts the user to provide a value through console input.
     * On interactive terminals, it will be done in a "fancy" fashing and in a single line.
     * Otherwise, it will be done in a more "traditional" manner. 
     * 
     * @param prompt The text that will be used to prompt the user for a value.
     * @param warning The error message that will be presented to the user if the value could not be parsed or if the validator function returns false.
     * @param result The variable where the result will be stored.
     * @param validator An optional function that determines if the value is valid.
     * This function is only executed after the parsing of the value was successful.
     * If this function throws a string, it will be presented to the user as an error message.
     * If this function returns false, the warning message will be presented to the user.
     * 
     * @return true, if the input is valid, or false, if cin has reached EOF. 
     */
    bool read_value(const string prompt, const string warning, unsigned int &result, const function<bool(unsigned int)> validator) {
        return keyboard::read_value_adaptive<unsigned int>(prompt, warning, result, validator);
    }

    /**
     * @brief Prompts the user to provide a value through console input.
     * On interactive terminals, it will be done in a "fancy" fashing and in a single line.
     * Otherwise, it will be done in a more "traditional" manner. 
     * 
     * @param prompt The text that will be used to prompt the user for a value.
     * @param warning The error message that will be presented to the user if the value could not be parsed or if the validator function returns false.
     * @param result The variable where the result will be stored.
     * @param validator An optional function that determines if the value is valid.
     * This function is only executed after the parsing of the value was successful.
     * If this function throws a string, it will be presented to the user as an error message.
     * If this function returns false, the warning message will be presented to the user.
     * 
     * @return true, if the input is valid, or false, if cin has reached EOF. 
     */
    bool read_value(const string prompt, const string warning, char &result, const function<bool(char)> validator) {
        return keyboard::read_value_adaptive<char>(prompt, warning, result, validator);
    }

} // namespace keyboard

namespace screen {

    /**
     * @brief Clears the terminal window.
     */
    void clear() {
        for (int i = 0; i < 100; i++) {
            cout << '\n';
        }

        cout << flush;
    }
} // namespace screen

namespace utf8 {

    /**
     * @brief Returns the number of code points present in the given string.
     * 
     * @param s the string whose UTF8 length is to be returned.
     * @return the number of UTF8 code points present in the given string.
     */
    size_t length(const char* str) {
        size_t len = 0;
        while (*str) 
            len += (*str++ & 0xc0) != 0x80;

        return len;
    } 

    /**
     * @brief Returns the number of code points present in the given string.
     * 
     * @param s the string whose UTF8 length is to be returned.
     * @return the number of UTF8 code points present in the given string.
     */
    size_t length(const string str) {
        return length(str.c_str());
    }

    /**
     * @brief Adds filler characters until the given string has the specified length.
     * 
     * @param s The string that will be filled.
     * @param filler The filler character.
     * @param length The desired length.
     * @param left true to add the filler characters to the start of the string, false otherwise.
     * 
     * @return The filled string.
     */
    string zfill(string str, const char filler, const size_t length, const bool left) {
        if (utf8::length(str) >= length)
            return str;

        size_t missing_characters = length - utf8::length(str);
        str.resize(str.size() + missing_characters);
        for (size_t i = 0; i < missing_characters; i++) {
            if (left)
                str.insert(str.begin(), filler);
            else
                str.insert(str.end(), filler);
        }

        return str;
    }

    /**
     * @brief Removes whitespace characters at the start of the string.
     * 
     * @param str The string to trim.
     * @return The trimmed string.
     */
    string ltrim(string str) {
        return str.erase(0, str.find_first_not_of("\t\n\v\f\r "));
    }

    /**
     * @brief Removes whitespace characters at the end of the string.
     * 
     * @param str The string to trim.
     * @return The trimmed string.
     */
    string rtrim(string str) {
        return str.erase(str.find_last_not_of("\t\n\v\f\r ") + 1);
    }
    
    /**
     * @brief Removes whitespace characters at both the start and the end of the string.
     * 
     * @param str The string to trim.
     * @return The trimmed string.
     */
    string trim(string str) {
        return ltrim(rtrim(str));
    }
} // namespace utf8

namespace timer {

    time_t start_time;

    /**
     * @brief Starts the game timer.
     */
    void start() {
        start_time = time(NULL);
    }

    /**
     * @brief Returns the number of seconds since the game timer started.
     * 
     * @return The number of seconds since the game timer started.
     */
    time_t stop() {
        return time(NULL) - start_time;
    }
} // namespace timer

namespace game {

    /**
     * @brief Returns whether or not a cell has something dead in it.
     * 
     * @param value The value of a cell.
     * @return true, if the cell has something dead in it, or false, otherwise.
     */
    bool is_cell_dead(unsigned int value) {
        return value & game::masks::DEAD;
    }

    /**
     * @brief Returns whether or not a cell has a human in it.
     * 
     * @param value The value of a cell.
     * @return true, if the cell has a human in it, or false, otherwise.
     */
    bool is_cell_human(unsigned int value) {
        return value & game::masks::HUMAN;
    }

    /**
     * @brief Returns whether or not a cell has a robot in it.
     * 
     * @param value The value of a cell.
     * @return true, if the cell has a robot in it, or false, otherwise.
     */
    bool is_cell_robot(unsigned int value) {
        return value & game::masks::ROBOT;
    }

    /**
     * @brief Returns whether or not a cell has a barrier in it.
     * 
     * @param value The value of a cell.
     * @return true, if the cell has a barrier in it, or false, otherwise.
     */
    bool is_cell_barrier(unsigned int value) {
        return value & game::masks::BARRIER;
    }

    /**
     * @brief Returns a character representing the value present in a given cell.
     * If a value is not recognized, the character '?' is returned.
     * 
     * @param value The value of a cell.
     * @return The character representing the value present in a given cell.
     */
    char translate_from_cell_value(unsigned int value) {
        if (value & game::masks::BARRIER)
            return '*';

        if (value & game::masks::HUMAN)
            if (is_cell_dead(value))
                return 'h';
            else
                return 'H';

        if (value & game::masks::ROBOT)
            if (is_cell_dead(value))
                return 'r';
            else
                return 'R';

        return '?';
    }

    /**
     * @brief Returns the value that is represented by the given character.
     * If the character is not recognized, an error is thrown.
     * 
     * @param value The value of a cell.
     * @return The character representing the value present in a given cell.
     */
    unsigned int translate_to_cell_value(char value) {
        switch (value) {
            case '*':
                return game::masks::BARRIER;

            case 'H':
                return game::masks::HUMAN;

            case 'R':
                return game::masks::ROBOT;

            case ' ':
                return game::EMPTY;

            default:
                throw "The provided character is invalid";
        }
    }

    size_t get_cell_index(size_t width, size_t height, size_t x, size_t y) {
        if (x >= width || y >= height)
            throw "The provided coordinates are invalid";

        return x + y * width;
    }

    size_t get_cell_index(game::Map &map, size_t x, size_t y) {
        return get_cell_index(map.width, map.height, x, y);
    }

    unsigned int& get_cell_value_at(game::Map &map, size_t x, size_t y) {
        return map.cells[get_cell_index(map, x, y)];
    }

    /**
     * @brief Returns whether or not a map number is valid.
     * 
     * @param map A map number.
     * @return true, if the map number is valid, or false, otherwise.
     */
    bool is_map_number_valid(unsigned int map) {
        return map < 100;
    }
} // namespace map

namespace files {
    
    /**
     * @brief Returns the name of the file containing the given maze.
     * 
     * @param number The number of the maze.
     * @return The name of the file containing the given maze.
     */
    string get_maze_file_name(unsigned int number) {
        if (!game::is_map_number_valid(number))
            throw "The provided maze number is invalid";

        string file_name = utf8::zfill(to_string(number), '0', 2, true);
        return "MAZE_" + file_name + ".TXT";
    }

    /**
     * @brief Returns the name of the file containing the given maze's winners.
     * 
     * @param number The number of the maze.
     * @return The name of the file containing the given maze's winners.
     */
    string get_maze_winners_file_name(unsigned int number) {
        if (!game::is_map_number_valid(number))
            throw "The provided maze number is invalid.";

        string file_name = utf8::zfill(to_string(number), '0', 2, true);
        return "MAZE_" + file_name + "_WINNERS.TXT";
    }

    /**
     * @brief Opens the given file for reading.
     * If the file doesn't exist, an error is thrown.
     * 
     * @param file_name The name of the file. 
     * @return An open stream to the given file.
     */
    ifstream open_file_reader(string file_name) {
        ifstream file;
        file.open(file_name, ios::in);
        if (!file.is_open())
            throw "The given file doesn't exist";

        return file;
    }

    /**
     * @brief Opens the given file for writing.
     * If the file doesn't exist and it couldn't be created, an error is thrown.
     * 
     * @param file_name The name of the file. 
     * @return An open stream to the given file.
     */
    ofstream open_file_writer(string file_name) {
        ofstream file;
        file.open(file_name, ios::trunc);
        if (!file.is_open())
            throw "Couldn't create the given file";

        return file;
    }

    game::Map read_map(unsigned int map) {
        ifstream file = files::open_file_reader(files::get_maze_file_name(map));

        char sep;
        size_t width, height;
        file >> width >> sep >> height;
        if (sep != 'x')
            throw "The given file does not fulfill the expected format";

        unsigned int* cells = (unsigned int*) malloc(width * height * sizeof(unsigned int)); £;//TODO: free(cells); !!!!!!!!!!!!!!!!!
        
        game::Player player;
        bool has_found_player = false;

        vector<game::Robot> robots;
        
        char ch;
        size_t index = 0;
        while (cin.get(ch)) {
            if (ch == '\n') {
                if (index % width != 0)
                    throw "The given file does not fulfill the expected format";

                continue;
            }

            unsigned int value = game::translate_to_cell_value(ch);

            size_t x = index % width;
            size_t y = index / width;

            if (game::is_cell_human(value)) {
                if (!has_found_player) {
                    player.x = x;
                    player.y = y;

                    has_found_player = true;
                } else 
                    throw "The given file does not fulfill the expected format";
            } else if (game::is_cell_robot(value)) {
                robots.push_back({
                    robots.size() + 1, // Robot IDs start at 1
                    x, y
                });
            }

            cells[index++] = value;
        }

        if (index < width * height)
            throw "The given file does not fulfill the expected format";

        file.close();
        return { width, height, cells, player, robots };
    }

    bool save_score(unsigned int map, string player_name, time_t player_score) {
        static const string HEADER1 = "Player          - Time";
        static const string HEADER2 = "----------------------";

        struct Score {
            string name; 
            int score;
        };

        vector<Score> scores;
        string winners_file_name = files::get_maze_winners_file_name(map);

        // Read scores from file
        try {

            ifstream file_reader = files::open_file_reader(winners_file_name);

            string line;
            getline(file_reader, line);
            if (line != HEADER1)
                throw "The given file does not fulfill the expected format";

            getline(file_reader, line);
            if (line != HEADER2)
                throw "The given file does not fulfill the expected format";

            while (getline(file_reader, line)) {
                if (utf8::length(line) != utf8::length(HEADER1) || line.substr(15, 3) != " - ")
                    throw "The given file does not fulfill the expected format";

                string name = line.substr(0, 15);
                time_t score = stoi(line.substr(18, 4));

                scores.push_back({ name, score });
            }
            
            file_reader.close();
        } catch (...) {}

        // Sort scores 
        scores.push_back({ player_name, player_score });
        sort(scores.begin(), scores.end(), [] (auto first, auto second) {  
            return first.score < second.score;
        });

        // Write ordered scores to file
        ofstream file_writer = open_file_writer(winners_file_name); 

        file_writer << HEADER1 << '\n'
                    << HEADER2 << '\n';

        for (auto score : scores) {
            file_writer << utf8::zfill(score.name, ' ', 15, false)
                        << " - "
                        << utf8::zfill(to_string(score.score), ' ', 4, true)
                        << '\n';
        }   

        file_writer << flush;
        file_writer.close();

        return true;
    }
} // namespace files

// bool loadMap(unsigned int &number, vector<vector<char>> &result) {  // Validates map number choice
//     result.clear();

//     function<bool(unsigned int)> fun = [&result] (unsigned int res) {
//         if (res == 0)
//             return true;

//         if (res >= 100)
//             throw "Please specify a number between 1 and 99";

//         if (!readMap(res, result))
//             throw "A map with that number does not exist";

//         return true; 
//     };
    
//     bool success = input::read_value(
//         "Please select a map to play on (0 to return to menu): ",
//         "Please specify a number",
//         number,
//         fun
//     );

//     cout << endl;
//     return success;
// }

// bool get_deltas_from_direction(char direction, int &dx, int &dy) {  // Gets direction through vector coordinates
//     switch (direction) {
//         case 'Q':
//             dx = -1;
//             dy = -1;
//             break;

//         case 'W':
//             dx = 0;
//             dy = -1;
//             break;

//         case 'E':
//             dx = 1;
//             dy = -1;
//             break;

//         case 'A':
//             dx = -1;
//             dy = 0;
//             break;
            
//         case 'S':
//             dx = 0;
//             dy = 0;
//             break;

//         case 'D':
//             dx = 1;
//             dy = 0;
//             break;

//         case 'Z':
//             dx = -1;
//             dy = 1;
//             break;

//         case 'X':
//             dx = 0;
//             dy = 1;
//             break;

//         case 'C':
//             dx = 1;
//             dy = 1;
//             break;

//         default:
//             return false;
//     }

//     return true;
// }

// bool playGame() {
//     Map map;  // Defined in entities.h as the vector cointaining the game's map
//     unsigned int map_number;
//     if (!loadMap(map_number, map))
//         return false;

//     if (map_number == 0)
//         return true;

//     Player player;  // Struct defining the player's status
//     vector<Robot> robots;  // Vector that will store all robots present in the map

//     for (size_t i = 0; i < map.size(); i++) {
//         vector<char> line = map.at(i);  // Defining a vector for each line in map
//         for (size_t j = 0; j < line.size(); j++) {
//             char character = line.at(j);  

//             switch (character) {
//                 case 'R':
//                     robots.push_back({
//                         static_cast<unsigned int> (robots.size() + 1),  // Increasing vector size if robot is found
//                         static_cast<int> (j),
//                         static_cast<int> (i),
//                         true
//                     });
//                     break;
                
//                 case 'H':
//                     player = { static_cast<int> (j), static_cast<int> (i), true };  // Assigning position and status to player struct
//                     break;

//                 default:
//                     break;
//             }          
//         }
//     }

//     game_timer(true);  // Starts timer
//     while (true) {
//         input::clear_screen();
//         for (size_t i = 0; i < map.size(); i++) {  // Prints map to the console
//             vector<char> line = map.at(i);
//             for (size_t j = 0; j < line.size(); j++) {
//                 char ch = line.at(j);
//                 cout << ch;
//             }
//             cout << endl;
//         }

//         cout << endl;

//         char letter;
//         int dx, dy;
//         bool is_not_eof = input::read_value(  // Validates player's move
//             "Your move: ",
//             "Your move must be one of Q, A, Z, W, S, X, E, D, or C",
//             letter,
//             [player, &map, &dx, &dy] (auto res) {
//                 if(!get_deltas_from_direction(toupper(res), dx, dy) || !is_move_valid(player, map, dx, dy))
//                     throw "Your move must be one of Q, A, Z, W, S, X, E, D, or C AND must be a valid move";

//                 return true;
//             }
//         );

//         cout << endl;

//         if (!is_not_eof)
//             return false;

//         map.at(player.y)[player.x] = ' ';  // Replaces previous place with empty space
//         move(player, map, dx, dy);

//         for (size_t i = 0; i < robots.size(); i++) {
//             Robot &robot = robots.at(i);

//             switch (move(robot, map, get_robot_dx(robot, player), get_robot_dy(robot, player))) {  // Moves every robot independently in order
//                                                                                                    //Returns 1, 2 or 3 depending on the outcome
//                 case 2:  // Robot colided with another robot, creating a stump
//                     for (size_t j = 0; j < robots.size(); j++) {
//                         if (i == j)  // Checking robot's id is not his own
//                             continue;

//                         Robot &another_robot = robots.at(j);
//                         if (robot.x == another_robot.x && robot.y == another_robot.y)
//                             another_robot.alive = false;
//                     }

//                     break;

//                 case 3:  // Robot colided with player
//                     player.alive = false;  // Player's status becomes dead
//                     break;

//                 default:
//                     break;
//             }
//         }

//         map.at(player.y)[player.x] = (player.alive ? 'H' : 'h');  // Replacing player with "h" if dead

//         if (!player.alive)  // Ending game when player dies
//             break;

//         bool has_game_ended = true;
//         for (auto robot : robots) {
//             if (robot.alive)  // Checking if there are robots alive; if so (and player's not dead), game will not end
//                 has_game_ended = false;
//         }

//         if (has_game_ended)
//             break;
//     }

//     time_t score = game_timer(false);  // Timestamping game's end

//     input::clear_screen();
//     for (size_t i = 0; i < map.size(); i++) { // Displays last game frame
//         vector<char> line = map.at(i);
//         for (size_t j = 0; j < line.size(); j++) {
//             char ch = line.at(j);
//             cout << ch;
//         }
//         cout << endl;
//     }

//     cout << endl;
    
//     if (player.alive) {
//         cout << "You won :)" << endl;
//         cout << "You finished the game in " << score << " seconds" << endl;
//     } else {
//         cout << "You lost :(" << endl;
//     }
    
//     cout << endl;
//     input::wait_for_enter();

//     if (!player.alive)
//         return true;

//     input::Name name_struct;
//     if (!input::read_value("Well done, champion! What's your name? ", "Please specify your name (must have 15 characters or less)", name_struct))
//         return false;

//     string name = name_struct.name;

//     saveScore(name, score, map_number);
//     return true;
// }