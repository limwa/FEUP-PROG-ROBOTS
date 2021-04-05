#include <iostream>
#include "keyboard.h"
#include "info.h"
#include "game.h"

using namespace std;

int main(int, char**) {
    while (true) {
        info::menu();

        unsigned int option;
        bool success = keyboard::read_value(
            "Your option: ", 
            "Your option must be one of 0, 1 or 2", 
            option, 
            [] (auto res) { return res <= 2; }
        );

        if (!success)
            option = 0; // Exits the program
        
        cout << endl;

        
        string line;

        switch (option) {
            case 0:  //Exits program
                info::bye();
                return 0;
                
            case 1:  // Displays Rules
                info::rules();
                keyboard::wait_for_enter();
                break;
                
            case 2:  // Starts game sequence
                try {
                    play_game();
                } catch (bool ex) {
                    if (!ex) {
                        info::bye();
                        return 1;
                    }
                }
                break;

            default:
                cout << "The power of Christ compels you!" << endl;
                return 2;
        }
    }
}
