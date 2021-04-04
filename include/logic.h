#include "mazes.h"

namespace logic {
    void get_deltas_from_direction(const char direction, int &dx, int &dy);

    namespace player {
        bool is_move_valid(const mazes::Maze &maze, const int dx, const int dy);

        bool is_move_valid(const mazes::Maze &maze, char direction);

        void move(mazes::Maze &maze, int dx, int dy);

        void move(mazes::Maze &maze, char direction);
    } // namespace player
    
    namespace robot {
        
        void get_suggested_deltas(const mazes::Maze &maze, const mazes::Robot &robot, int &dx, int &dy);

        void move(mazes::Maze &maze, mazes::Robot &robot);        
    } // namespace robot
} // namespace logic