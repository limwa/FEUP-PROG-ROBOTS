#include <iostream>
#include "keyboard.h"
#include "screen.h"
#include "mazes.h"
#include "files.h"
#include "logic.h"
#include "timer.h"
#include "utf8.h"

#include "game.h"

using namespace std;

/**
 * @brief Asks the user for the map he/she wants to play on.
 * 
 * @return The chosen maze's number.
 */
mazes::Maze ask_maze() {
    mazes::Maze maze;

    unsigned int number;
    bool is_successful = keyboard::read_value(
        "Please select a maze to play on (0 to return to menu): ",
        "Please specify a number between 0 and 99",
        number,
        [&maze] (auto res) {
            if (res >= 100)
                return false;

            if (res == 0)
                return true;

            maze = files::read_maze(res);
            return true;
        }
    );

    cout << endl;

    if (!is_successful)
        throw false;

    if (number == 0)
        throw true;    

    return maze;
}

/**
 * @brief Asks the user for a move to play.
 * 
 * @param maze The maze the player is playing on.
 * @return A letter corresponding to the move.
 */
char ask_move(const mazes::Maze &maze) {

    char letter;
    bool is_successful = keyboard::read_value(
        "Your move: ",
        "Your move must be one of Q, A, Z, W, S, X, E, D, or C",
        letter,
        [&maze] (auto res) {
            bool is_move_valid;
            try {
                is_move_valid = logic::player::is_move_valid(maze, res);
            } catch (const char *exception) {
                return false;
            }

            if (!is_move_valid)
                throw "Uh oh, that move seems invalid";

            return true;
        }
    );

    cout << endl;

    if (!is_successful)
        throw false;

    return letter;
}

/**
 * @brief Asks the user for his/her name.
 * 
 * @return The name provided by the user.
 */
string ask_name() {
    keyboard::Name name = { string() };

    bool is_successful = keyboard::read_value(
        "Well done, champion! What's your name? ",
        "The provided name must have less than 15 characters",
        name
    );

    cout << endl;

    if (!is_successful)
        throw false;

    return name.data;
}

/**
 * @brief Plays the game.
 */
void play_game() {
    mazes::Maze maze = ask_maze();

    timer::start();

    try {
        bool has_player_won;
        while (true) {
            screen::clear();
            mazes::show_maze(maze);
            cout << endl;

            char move = ask_move(maze);

            logic::player::move(maze, move);

            if (mazes::is_cell_dead(mazes::get_cell_value_at_player_position(maze))) {
                has_player_won = false;
                break;
            }

            for (auto &robot : maze.robots) {
                logic::robot::move(maze, robot);
            }

            if (mazes::is_cell_dead(mazes::get_cell_value_at_player_position(maze))) {
                has_player_won = false;
                break;
            }

            bool are_robots_alive = false;
            for (auto robot : maze.robots) {
                if (!mazes::is_cell_dead(mazes::get_cell_value_at(maze, robot.x, robot.y))) {
                    are_robots_alive = true;
                    break;
                }
            }

            if (!are_robots_alive) {
                has_player_won = true;
                break;
            }
        }

        time_t score = timer::stop();

        screen::clear();
        mazes::show_maze(maze);
        cout << endl;

        if (has_player_won) {
            cout << "You won :)\n"
                 << "Congratulations! You finished the game in " << score << " seconds!" << endl;
        } else {
            cout << "You lost :(" << endl;
        }

        cout << endl;
        keyboard::wait_for_enter();

        if (!has_player_won)
            return;

        string name = ask_name();
        try {
            files::save_maze_score(maze.id, name, score);
            cout << ">> Your score was saved!" << endl;
        } catch (const char *exception) {
            cout << ">> " << exception << endl;
        }
        
        cout << endl;
        keyboard::wait_for_enter();

        throw true; // Make sure to free memory and restart game
    } catch (bool ex) {
        free(maze.cells);
        throw ex;
    }
}
