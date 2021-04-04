#include <string>

#include "logic.h"

namespace logic {
    void get_deltas_from_direction(const char direction, int &dx, int &dy) {  // Gets direction through vector coordinates
        switch (toupper(direction)) {
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
                throw "The given direction is invalid";
        }
    }

    namespace player {
        bool is_move_valid(const mazes::Maze &maze, const int dx, const int dy) {
            if (dx < -1 || dx > 1 || dy < -1 || dy > 1)
                return false;

            if (mazes::is_cell_dead(mazes::get_cell_value_at_player_position(maze)))
                return false;

            int new_x = maze.player.x + dx;
            int new_y = maze.player.y + dy;
            if (new_x < 0 || new_y < 0 || new_x >= maze.width || new_y >= maze.height)
                return false;

            unsigned int value = mazes::get_cell_value_at(maze, new_x, new_y);
            if (mazes::is_cell_robot(value) || mazes::is_cell_barrier(value))
                return false;

            return true;    
        }

        bool is_move_valid(const mazes::Maze &maze, char direction) {
            int dx, dy;
            logic::get_deltas_from_direction(direction, dx, dy);

            return logic::player::is_move_valid(maze, dx, dy);
        }

        void move(mazes::Maze &maze, int dx, int dy) {
            if (!logic::player::is_move_valid(maze, dx, dy))
                throw "The provided move is not valid";

            int new_x = maze.player.x + dx;
            int new_y = maze.player.y + dy;

            mazes::get_cell_value_at_player_position(maze) &= ~mazes::masks::HUMAN;
            
            maze.player.x = new_x;
            maze.player.y = new_y;

            mazes::get_cell_value_at_player_position(maze) |= mazes::masks::HUMAN;
        }

        void move(mazes::Maze &maze, char direction) {
            int dx, dy;
            logic::get_deltas_from_direction(direction, dx, dy);

            logic::player::move(maze, dx, dy);
        }
    } // namespace player
    
    namespace robot {
        
        void get_suggested_deltas(const mazes::Maze &maze, const mazes::Robot &robot, int &dx, int &dy) {
            int delta_x = maze.player.x - robot.x;
            int delta_y = maze.player.y - robot.y;

            if (delta_x > 0)
                dx = 1;
            else if (delta_x < 0)
                dx = -1;
            else
                dx = 0;

            if (delta_y > 0)
                dy = 1;
            else if (delta_y < 0)
                dy = -1;
            else
                dy = 0;
        }

        void move(mazes::Maze &maze, mazes::Robot &robot) {
            int dx, dy;
            logic::robot::get_suggested_deltas(maze, robot, dx, dy);

            int new_x = robot.x + dx;
            int new_y = robot.y + dy;
            if (new_x < 0 || new_x >= maze.width)
                new_x = robot.x;

            if (new_y < 0 || new_y >= maze.height)
                new_y = robot.y;

            unsigned int& current_value = mazes::get_cell_value_at(maze, robot.x, robot.y);
            unsigned int& new_value = mazes::get_cell_value_at(maze, new_x, new_y);

            if (mazes::is_cell_dead(current_value))
                return;

            if (mazes::is_cell_barrier(new_value)) {
                if (!mazes::is_cell_dead(new_value)) { // If the barrier is powered
                    current_value |= mazes::masks::DEAD; // Kill robot
                    new_value |= mazes::masks::DEAD; // Make barrier unpowered
                }
            } else if (mazes::is_cell_robot(new_value)) {
                if (mazes::is_cell_dead(new_value)) { // If the robot in the new position is dead
                    current_value |= mazes::masks::DEAD;
                } else { // If the robot in the new position is alive
                    current_value &= ~mazes::masks::ROBOT; // Move the robot
                    new_value |= mazes::masks::DEAD; // Kill both robots;

                    robot.x = new_x;
                    robot.y = new_y;
                }
            } else if (mazes::is_cell_human(new_value)) {
                new_value |= mazes::masks::DEAD;
            } else {
                current_value &= ~mazes::masks::ROBOT; // Move the robot
                new_value |= mazes::masks::ROBOT;

                robot.x = new_x;
                robot.y = new_y;
            }
        }        
    } // namespace robot
} // namespace logic