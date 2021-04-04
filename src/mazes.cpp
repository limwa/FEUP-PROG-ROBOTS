#include <iostream>

#include "mazes.h"

namespace mazes {

    /**
     * @brief Returns whether or not a cell has something dead in it.
     * 
     * @param value The value of a cell.
     * @return true, if the cell has something dead in it, or false, otherwise.
     */
    bool is_cell_dead(unsigned int value) {
        return value & mazes::masks::DEAD;
    }

    /**
     * @brief Returns whether or not a cell has a human in it.
     * 
     * @param value The value of a cell.
     * @return true, if the cell has a human in it, or false, otherwise.
     */
    bool is_cell_human(unsigned int value) {
        return value & mazes::masks::HUMAN;
    }

    /**
     * @brief Returns whether or not a cell has a robot in it.
     * 
     * @param value The value of a cell.
     * @return true, if the cell has a robot in it, or false, otherwise.
     */
    bool is_cell_robot(unsigned int value) {
        return value & mazes::masks::ROBOT;
    }

    /**
     * @brief Returns whether or not a cell has a barrier in it.
     * 
     * @param value The value of a cell.
     * @return true, if the cell has a barrier in it, or false, otherwise.
     */
    bool is_cell_barrier(unsigned int value) {
        return value & mazes::masks::BARRIER;
    }

    /**
     * @brief Returns a character representing the value present in a given cell.
     * If a value is not recognized, the character '?' is returned.
     * 
     * @param value The value of a cell.
     * @return The character representing the value present in a given cell.
     */
    char translate_from_cell_value(unsigned int value) {
        if (mazes::is_cell_barrier(value))
                return '*';

        if (mazes::is_cell_human(value))
            if (mazes::is_cell_dead(value))
                return 'h';
            else
                return 'H';

        if (mazes::is_cell_robot(value))
            if (mazes::is_cell_dead(value))
                return 'r';
            else
                return 'R';

        if (value == mazes::EMPTY)
            return ' ';

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
                return mazes::masks::BARRIER;

            case 'H':
                return mazes::masks::HUMAN;

            case 'R':
                return mazes::masks::ROBOT;

            case ' ':
                return mazes::EMPTY;

            default:
                throw "The provided character is invalid";
        }
    }

    size_t get_cell_index(size_t width, size_t height, size_t x, size_t y) {
        if (x >= width || y >= height)
            throw "The provided coordinates are invalid";

        return x + y * width;
    }

    size_t get_cell_index(const mazes::Maze &maze, size_t x, size_t y) {
        return get_cell_index(maze.width, maze.height, x, y);
    }

    unsigned int& get_cell_value_at(const mazes::Maze &maze, size_t x, size_t y) {
        return maze.cells[get_cell_index(maze, x, y)];
    }

    unsigned int& get_cell_value_at_player_position(const mazes::Maze &maze) {
        return get_cell_value_at(maze, maze.player.x, maze.player.y);
    }

    /**
     * @brief Returns whether or not a maze number is valid.
     * 
     * @param maze A maze number.
     * @return true, if the maze number is valid, or false, otherwise.
     */
    bool is_maze_number_valid(unsigned int maze) {
        return maze < 100;
    }

    void show_maze(const mazes::Maze &maze) {
        for (int i = 0; i < maze.width * maze.height; i++) {
            if (i % maze.width == 0)
                cout << '\n';

            cout << mazes::translate_from_cell_value(maze.cells[i]);
        }

        cout << endl;
    }
} // namespace mazes
