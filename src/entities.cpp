#include "entities.h"
#include "math.h"

bool update_dead(Robot robot, Map &map) {
    return map.at(robot.y).at(robot.x) != 'R';
}

unsigned move(Robot &robot, Map &map, int dx, int dy) {
    if (!robot.alive || dx < -1 || dx > 1 || dy < -1 || dy > 1)
        return 0;

    int new_x = robot.x + dx;
    int new_y = robot.y + dy;
    if (new_y >= 0 && new_y < map.size() && new_x >= 0 && new_x < map.at(new_y).size()) {
        map.at(robot.y)[robot.x] = ' ';
        int status = 1;
        switch (map.at(new_y).at(new_x)) {
            case '*':
            case 'r':
                robot.alive = false;
                break;

            case 'R':
                robot.x = new_x;
                robot.y = new_y;
                robot.alive = false;
                status = 2;
                break;

            case 'H':
                status = 3;
                break;

            default:
                robot.x = new_x;
                robot.y = new_y;
                break;
        }


        map.at(robot.y)[robot.x] = (robot.alive ? 'R' : 'r');
        return status;
    } else {
        robot.alive = false;
    }

    return 1;
}

bool should_be_dead(Player player, Map &map) {
    return map.at(player.y).at(player.x) != 'H';
}

int get_robot_dx(Robot robot, Player player) {
    int diff = player.x - robot.x;

    if (diff > 0)
        return 1;
    else if (diff < 0)
        return -1;
    else
        return 0;
}

int get_robot_dy(Robot robot, Player player) {
    int diff = player.y - robot.y;
    
    if (diff > 0)
        return 1;
    else if (diff < 0)
        return -1;
    else
        return 0;
}

unsigned move(Player &player, Map &map, int dx, int dy) {
    if (!player.alive || dx < -1 || dx > 1 || dy < -1 || dy > 1)
        return 0;

    int new_x = player.x + dx;
    int new_y = player.y + dy;
    if (new_y >= 0 && new_y < map.size() && new_x >= 0 && new_x < map.at(new_y).size()) {
        map.at(player.y)[player.x] = ' ';

        switch (map.at(new_y).at(new_x)) {
            case '*':
            case 'r':
            case 'R':
                return 0;

            default:
                player.x = new_x;
                player.y = new_y;
                break;
        }

        map.at(player.y)[player.x] = 'H';
    } else {
        return 0;
    }

    return 1;
}

bool is_move_valid(Player player, Map &map, int dx, int dy) {
    if (!player.alive || dx < -1 || dx > 1 || dy < -1 || dy > 1)
        return false;

    int new_x = player.x + dx;
    int new_y = player.y + dy;
    if (new_y >= 0 && new_y < map.size() && new_x >= 0 && new_x < map.at(new_y).size()) {
        switch (map.at(new_y).at(new_x)) {
            case '*':
            case 'r':
            case 'R':
                return false;

            default:
                return true;
        }
    }

    return false;
}
