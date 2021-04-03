#ifndef GAME_H
#define GAME_H

#include <string>
#include <functional>

namespace info {

    /**
     * @brief Displays the game's main menu.
     */
    void menu();

    /**
     * @brief Displays the game's rules.
     */
    void rules();

    /**
     * @brief Displays the game's exit message.
     */
    void bye();
} // namespace info

namespace keyboard {

    /**
     * @brief Blocks execution until the user presses the RETURN key.
     */
    void wait_for_enter();

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
    bool read_value(const std::string prompt, const std::string warning, unsigned int &result, const std::function<bool(unsigned int)> validator = [](unsigned int res) { return true; });
    
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
    bool read_value(const std::string prompt, const std::string warning, char &result, const std::function<bool(char)> validator = [](char res) { return true; });


} // namespace keyboard

namespace screen {

    /**
     * @brief Clears the terminal window.
     */
    void clear();
} // namespace screen

namespace utf8 {

    /**
     * @brief Returns the number of code points present in the given string.
     * 
     * @param s the string whose UTF8 length is to be returned.
     * @return The number of UTF8 code points present in the given string.
     */
    size_t length(const char* str);

    /**
     * @brief Returns the number of code points present in the given string.
     * 
     * @param s the string whose UTF8 length is to be returned.
     * @return The number of UTF8 code points present in the given string.
     */
    size_t length(const string str);

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
    std::string zfill(std::string str, const char filler, const size_t length, const bool left);

    /**
     * @brief Removes whitespace characters at the start of the string.
     * 
     * @param str The string to trim.
     * @return The trimmed string.
     */
    std::string ltrim(std::string str);

    /**
     * @brief Removes whitespace characters at the end of the string.
     * 
     * @param str The string to trim.
     * @return The trimmed string.
     */
    std::string rtrim(std::string str);

    /**
     * @brief Removes whitespace characters at both the start and the end of the string.
     * 
     * @param str The string to trim.
     * @return The trimmed string.
     */
    std::string trim(std::string str);
} // namespace utf8

namespace timer {

    /**
     * @brief Starts the game timer.
     */
    void start();

    /**
     * @brief Returns the number of seconds since the game timer started.
     * 
     * @return The number of seconds since the game timer started.
     */
    time_t stop();
} // namespace timer

namespace mazes {
    namespace masks {

        /**
         * @brief Bitmask that indicates whether a cell has a barrier in it.
         */
        const unsigned int BARRIER = 1;

        /**
         * @brief Bitmask that indicates whether a cell has a human in it.
         */
        const unsigned int HUMAN = 2;

        /**
         * @brief Bitmask that indicates whether a cell has a robot in it.
         */
        const unsigned int ROBOT = 4;

        /**
         * @brief Bitmask that indicates whether a cell has something dead in it.
         */
        const unsigned int DEAD = 8;
    } // namespace masks

    /**
     * @brief Default value for a cell.
     */
    const unsigned int EMPTY = 0;

    /**
     * @brief Represents a player.
     * 
     */
    struct Player {
        size_t x;
        size_t y;
    };

    /**
     * @brief Represents a robot.
     */
    struct Robot {
        size_t id;
        size_t x;
        size_t y;
    };

    /**
     * @brief Represents a game maze.
     */
    struct Maze {
        size_t width;
        size_t height;
        unsigned int* cells;
        
        Player player;
        vector<Robot> robots;
    };

    /**
     * @brief Returns whether or not a cell has something dead in it.
     * 
     * @param value The value of a cell.
     * @return true, if the cell has something dead in it, or false, otherwise.
     */
    bool is_cell_dead(unsigned int value);

    /**
     * @brief Returns whether or not a cell has a human in it.
     * 
     * @param value The value of a cell.
     * @return true, if the cell has a human in it, or false, otherwise.
     */
    bool is_cell_human(unsigned int value);

    /**
     * @brief Returns whether or not a cell has a robot in it.
     * 
     * @param value The value of a cell.
     * @return true, if the cell has a robot in it, or false, otherwise.
     */
    bool is_cell_robot(unsigned int value);

    /**
     * @brief Returns whether or not a cell has a barrier in it.
     * 
     * @param value The value of a cell.
     * @return true, if the cell has a barrier in it, or false, otherwise.
     */
    bool is_cell_barrier(unsigned int value);

    /**
     * @brief Returns a character representing the value present in a given cell.
     * If a value is not recognized, the character '?' is returned.
     * 
     * @param value The value of a cell.
     * @return The character representing the value present in a given cell.
     */
    char translate_from_cell_value(unsigned int value);

    /**
     * @brief Returns the value that is represented by the given character.
     * If the character is not recognized, an error is thrown.
     * 
     * @param value The value of a cell.
     * @return The character representing the value present in a given cell.
     */
    unsigned int translate_to_cell_value(char value);
    
    size_t get_cell_index(size_t width, size_t height, size_t x, size_t y);
    size_t get_cell_index(mazes::Maze &maze, size_t x, size_t y);
    unsigned int& get_cell_value_at(mazes::Maze &maze, size_t x, size_t y);

    /**
     * @brief Returns whether or not a maze number is valid.
     * 
     * @param maze A maze number.
     * @return true, if the maze number is valid, or false, otherwise.
     */
    bool is_maze_number_valid(unsigned int maze);
} // namespace mazes

namespace files {
    
    /**
     * @brief Returns the name of the file containing the given maze.
     * 
     * @param number The number of the maze.
     * @return The name of the file containing the given maze.
     */
    string get_maze_file_name(unsigned int number);

    /**
     * @brief Returns the name of the file containing the given maze's winners.
     * 
     * @param number The number of the maze.
     * @return The name of the file containing the given maze's winners.
     */
    string get_maze_winners_file_name(unsigned int number);

    /**
     * @brief Opens the given file for reading.
     * If the file doesn't exist and it couldn't be created, an error is thrown.
     * 
     * @param file_name The name of the file. 
     * @return An open stream to the given file.
     */
    ifstream open_file_reader(string file_name);

    /**
     * @brief Opens the given file for writing.
     * If the file doesn't exist, an error is thrown.
     * 
     * @param file_name The name of the file. 
     * @return An open stream to the given file.
     */
    ofstream open_file_writer(string file_name);
    
    mazes::Maze read_maze(unsigned int maze);
    void save_score(unsigned int maze, string player_name, time_t player_score);
} // namespace files

#endif