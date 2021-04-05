#include "mazes.h"

namespace logic {

    /**
     * @brief Translates the given direction to horizontal and a vertical variations.
     * 
     * @param direction The player's move.
     * @param dx The variable to store the variation on the horizontal direction associated with the provided direction on.
     * @param dy The variable to store the variation on the vertcal direction associated with the provided direction on.
     */
    void get_deltas_from_direction(const char direction, int &dx, int &dy);

    namespace player {
        /**
         * @brief Checks whether the given move is valid.
         * 
         * @param maze The maze the player is playing on.
         * @param dx The change in the player's horizontal position.
         * @param dy The change in the player's vertical position.
         * @return true, if the given move is valid, or false, otherwise.
         */
        bool is_move_valid(const mazes::Maze &maze, const int dx, const int dy);

        /**
         * @brief Checks whether the given move is valid.
         * 
         * @param maze The maze the player is playing on.
         * @param direction The player's move.
         * @return true, if the move is valid, or false, otherwise.
         */
        bool is_move_valid(const mazes::Maze &maze, char direction);

        /**
         * @brief Moves the player.
         * 
         * @param maze The maze the player is playing on.
         * @param dx The change in the player's horizontal position.
         * @param dy The change in the player's vertical position.
         */
        void move(mazes::Maze &maze, int dx, int dy);

        /**
         * @brief Moves the player.
         * 
         * @param maze The maze the player is playing on.
         * @param direction The player's move.
         */
        void move(mazes::Maze &maze, char direction);
    } // namespace player
    
    namespace robot {
        
        /**
         * @brief Provides the horizontal and vertical variations that get the robot the closest to the player.
         * 
         * @param maze The maze the player is playing on.
         * @param robot A robot.
         * @param dx The change in the robot's horizontal position.
         * @param dy The change in the robot's vertical position.
         */
        void get_suggested_deltas(const mazes::Maze &maze, const mazes::Robot &robot, int &dx, int &dy);

        /**
         * @brief Moves the robot.
         * 
         * @param maze The maze the player is playing on.
         * @param robot A robot.
         */
        void move(mazes::Maze &maze, mazes::Robot &robot);        
    } // namespace robot
} // namespace logic
