#include <iostream>

#include "screen.h"

using namespace std;

namespace screen {

    /**
     * @brief Clears the terminal window.
     */
    void clear() {
        for (int i = 0; i < 100; i++) {
            cout << '\n';
        }

        cout << flush;
    }
} // namespace screen
