#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<char>> Map;

struct Robot {
    unsigned int id;
    int x;
    int y;
    bool alive;
};

struct Player {
    int x;
    int y;
    bool alive;
};

bool update_dead(Robot robot, Map &map);
int get_robot_dx(Robot robot, Player player);
int get_robot_dy(Robot robot, Player player);
unsigned move(Robot &robot, Map &map, int dx, int dy);

bool should_be_dead(Player player, Map &map);
unsigned move(Player &player, Map &map, int dx, int dy);
bool is_move_valid(Player player, Map &map, int dx, int dy);

#endif
