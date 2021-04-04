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

    if (number == 0)
        throw true;

    if (!is_successful)
        throw false;

    return maze;
}

char ask_move(const mazes::Maze &maze) {

    char letter;
    bool is_successful = keyboard::read_value(
        "Your move: ",
        "Your move must be one of Q, A, Z, W, S, X, E, D, or C",
        letter,
        [&maze] (auto res) {
            if (!logic::player::is_move_valid(maze, res))
                throw "Uh oh, that move seems invalid";

            return true;
        }
    );

    cout << endl;

    if (!is_successful)
        throw false;

    return letter;
}

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
            cout << "Your score was saved!" << endl;
        } catch (const char *exception) {
            cout << ">> Warning: " << exception << endl;
        }
        
        cout << endl;
        keyboard::wait_for_enter();

        throw true; // Make sure to free memory and restart game
    } catch (bool ex) {
        free(maze.cells);
        throw ex;
    }
}
