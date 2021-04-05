#include <iostream>
#include "screen.h"

#include "info.h"

using namespace std;

namespace info {

    /**
     * @brief Displays the game's main menu.
     */
    void menu() {
        screen::clear();

        cout << ".______________________________________________________.\n"
             << "|                                                      |\n"
             << "|                                                      |\n"
             << "|                                                      |\n"
             << "|       .___  ___.  _______ .__   __.  __    __        |\n"
             << "|       |   \\/   | |   ____||  \\ |  | |  |  |  |       |\n"
             << "|       |  \\  /  | |  |__   |   \\|  | |  |  |  |       |\n"
             << "|       |  |\\/|  | |   __|  |  . `  | |  |  |  |       |\n"
             << "|       |  |  |  | |  |____ |  |\\   | |  `--'  |       |\n"    
             << "|       |__|  |__| |_______||__| \\__|  \\______/        |\n"
             << "|                                                      |\n"
             << "|                                                      |\n"
             << "|                                                      |\n"
             << "|                                                      |\n"
             << "|                       1) Rules                       |\n"
             << "|                       2) Play                        |\n"
             << "|                       0) Exit                        |\n"
             << "|                                                      |\n"
             << "|                                                      |\n"
             << "|                                                      |\n"
             << "|                                                      |\n"
             << "|______________________________________________________|\n";

        cout << endl;
    }

    /**
     * @brief Displays the game's rules.
     */
    void rules() {
        screen::clear();

        cout << "            _              \n"
             << " _ __ _   _| | ___  ___    \n"
             << "| '__| | | | |/ _ \\/ __|  \n"
             << "| |  | |_| | |  __/\\__ \\ \n"
             << "|_|   \\__,_|_|\\___||___/ \n\n\n";
                            
        
        cout << "The player is placed in a maze made up of high-voltage fences and posts.\n"
             << "There are also some interceptor robots that will try to destroy the player.\n"
             << "If the player touches the maze or any of these robots, that is the end of the game (and the player!).\n"
             << "The robots are also destroyed when they touch the fences/posts or when they collide with each other.\n\n"
     
             << "Ever time the player moves in any direction (horizontally, vertically, or diagonally) to a contiguous cell,\n"
             << "each robot moves one cell closer to the new player's location, in whichever direction is the shortest path.\n"
             << "The robots have no vision sensors but they have an accurate odour sensor that allows them to follow the player!\n\n"
     
             << "There is one hope: make the robots hit the maze or each other. If all of them are destroyed, the player wins.\n\n"
 
             << "The controls are as follows: \n"
             << "-------------\n"
             << "| Q | W | E |\n"
             << "| A | S | D |\n"
             << "| Z | X | C |\n"
             << "-------------\n";

        cout << endl;
    }

    /**
     * @brief Displays the game's exit message.
     */
    void bye() {
        cout << "    ___            \n"  
             << "   | _ )_  _ ___   \n"
             << "   | _ \\ || / -_) \n"
             << "   |___/\\_, \\___|\n"
             << "       |__/        \n";

        cout << endl;
    }
} // namespace info
