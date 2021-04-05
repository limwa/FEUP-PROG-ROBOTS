#ifndef FILES_H
#define FILES_H

#include <fstream>
#include "mazes.h"

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
     * If the file doesn't exist, an error is thrown.
     * 
     * @param file_name The name of the file. 
     * @return An open stream to the given file.
     */
    ifstream open_file_reader(string file_name);

    /**
     * @brief Opens the given file for writing.
     * If the file doesn't exist and it couldn't be created, an error is thrown.
     * 
     * @param file_name The name of the file. 
     * @return An open stream to the given file.
     */
    ofstream open_file_writer(string file_name);

    /**
     * @brief Returns the requested maze's data.
     * If the given maze file doesn't exist, can't be read or doesn't fulfill the expected format
     * exceptions are thrown.
     * 
     * @param maze The number of the maze.
     * @return The requested maze's data, if it exists.
     */
    mazes::Maze read_maze(unsigned int maze);

    /**
     * @brief Writes the player's name and score in the winner's file. The entries are sorted in ascending score order.
     * If the file doesn't exist or doesn't fulfill the expected format, exceptions are thrown.
     * 
     * @param maze The number of the maze.
     * @param player_name The given player's name.
     * @param player_score The player's score.
     */
    void save_maze_score(unsigned int maze, string player_name, time_t player_score);
} // namespace files

#endif
