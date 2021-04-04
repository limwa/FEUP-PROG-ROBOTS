#ifndef MAZES_H
#define MAZES_H

#include <vector>

using namespace std;

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
        unsigned int id;

        size_t width;
        size_t height;
        unsigned int* cells;
        
        Player player;
        vector<mazes::Robot> robots;
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

    size_t get_cell_index(const mazes::Maze &maze, size_t x, size_t y);

    unsigned int& get_cell_value_at(const mazes::Maze &maze, size_t x, size_t y);

    unsigned int& get_cell_value_at_player_position(const mazes::Maze &maze);

    /**
     * @brief Returns whether or not a maze number is valid.
     * 
     * @param maze A maze number.
     * @return true, if the maze number is valid, or false, otherwise.
     */
    bool is_maze_number_valid(unsigned int maze);

    void show_maze(const mazes::Maze &maze);
} // namespace mazes

#endif
