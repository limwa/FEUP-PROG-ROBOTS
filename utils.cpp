#include <stdio.h>
#include <unistd.h>
#include "utils.h"

using namespace std;

namespace input {

    template <typename T>
    bool read_value_interactive(string prompt, string warning, T &result, const function<bool(T)> validator) {
        static string csi = "\x1B[";
        cout << "? " << prompt << flush;

        while (true) {
            // Is true if, and only if, all the content present on the line is a number
            bool is_input_valid = cin.peek() != '\n' 
                && cin >> result && cin.peek() == '\n'
                && validator(result);

            // Clear the buffer
            // We do this to avoid having "123a[EOF]" trigger the loop more than once.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (is_input_valid) {
                // Change status to valid
                cout << csi << 'F' << csi << 'G';
                cout << "✓";

                cout << csi << prompt.length() + 3 << 'G'; // Place cursor at the start of the input area
                cout << csi << 'K'; // Clear the input area

                cout << result << endl;

                cout << csi << 'K' << flush; // Clear the line in case there is something there
                return true;
            } else {
                if (!cin.eof()) {
                    // Show warning
                    cout << ">> " << warning;
                    cout << csi << 'F'; // Place cursor on the previous line
                }

                cout << csi << prompt.length() + 3 << 'G'; // Place cursor at the start of the input area
                cout << csi << 'K' << flush; // Clear the input area

                if (cin.eof()) {
                    cout << "EOF" << endl;

                    // Change status to invalid
                    cout << csi << 'F' << csi << 'G';
                    cout << "×";
                    cout << csi << 'E' << flush;

                    return false;
                }
            }
        }
    }

    template <typename T>
    bool read_value_dinossaur(string prompt, string warning, T &result, const function<bool(T)> validator) {
        while (true) {
            cout << "? " << prompt << flush;
            bool is_input_valid = cin.peek() != '\n' 
                && cin >> result && cin.peek() == '\n'
                && validator(result);
                
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (is_input_valid) {
                return true;
            } else {
                if (cin.eof()) {
                    cout << "EOF" << endl;
                    return false;
                } else {
                    cout << "\u26A0 " << warning << endl;
                }
            }
        }
    }

    bool read_value(std::string prompt, std::string warning, unsigned int &result, const std::function<bool(unsigned int)> validator) {
        if (isatty(fileno(stdout))) {
            return read_value_interactive<unsigned int>(prompt, warning, result, validator);
        } else {
            return read_value_dinossaur<unsigned int>(prompt, warning, result, validator);
        }
    }

    bool read_value(std::string prompt, std::string warning, char &result, const std::function<bool(char)> validator) {
        if (isatty(fileno(stdin)) && isatty(fileno(stdout))) {
            return read_value_interactive<char>(prompt, warning, result, validator);
        } else {
            return read_value_dinossaur<char>(prompt, warning, result, validator);
        }
    }

    void clear_screen() {
        for (int i = 0; i < 100; i++) {
            cout << '\n';
        }

        cout << flush;
    }

    void wait_for_enter() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

} // namespace input

namespace files {
 
} // namespace files
