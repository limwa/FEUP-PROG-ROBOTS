#ifndef GAME_H
#define GAME_H

#include "mazes.h"

/**
 * @brief Asks the uszer for the map he/she wants to play on.
 * 
 * @return The chosen maze's number.
 */
mazes::Maze ask_maze();

/**
 * @brief Asks the user for a move to play.
 * 
 * @param maze The maze the player is playing on.
 * @return A letter corresponding to the move.
 */
char ask_move(const mazes::Maze &maze);

/**
 * @brief Asks the user for his/her name.
 * 
 * @return The name provided by the user.
 */
string ask_name();

/**
 * @brief Plays the game.
 */
void play_game();

#endif
