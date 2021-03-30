#include <stdio.h>
#include <unistd.h>
#include "utils.h"

using namespace std;

std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
 
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
 
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

namespace input {
    std::basic_istream<char>& operator>>(std::basic_istream<char>& istream, Name &name) {
        char ch;
        string result;

        while (result.length() < 15 && istream.good() && istream.peek() != '\n' && istream.get(ch))
            result.push_back(ch);

        trim(result);
        name.name = result;
        return istream;
    }

    std::basic_ostream<char>& operator<<(std::basic_ostream<char>& ostream, Name &name) {
        ostream << name.name;
        return ostream;
    }

    template <typename T>
    bool read_value_interactive(string prompt, string default_warning, T &result, const function<string(T)> validator) {
        static string csi = "\x1B[";

        string warning;
        cout << "? " << prompt << flush;
        while (true) {
            // Is true if, and only if, all the content present on the line is a number
            bool is_input_valid = cin.peek() != '\n' 
                && cin >> result && cin.peek() == '\n';

            warning = is_input_valid ? validator(result) : default_warning;

            if (is_input_valid)
                is_input_valid = warning.length() == 0;

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
                    cout << csi << 'K' << flush; // Clear the line in case there is something there
                    return false;
                }
            }
        }
    }

    template <typename T>
    bool read_value_dinossaur(string prompt, string default_warning, T &result, const function<string(T)> validator) {
        string warning;
        while (true) {
            cout << "? " << prompt << flush;
            bool is_input_valid = cin.peek() != '\n' 
                && cin >> result && cin.peek() == '\n';

            if (is_input_valid)
                is_input_valid = (warning = validator(result)).length() == 0;
                
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

    bool read_value(std::string prompt, string default_warning, unsigned int &result, const std::function<string(unsigned int)> validator) {
        if (isatty(fileno(stdout))) {
            return read_value_interactive<unsigned int>(prompt, default_warning, result, validator);
        } else {
            return read_value_dinossaur<unsigned int>(prompt, default_warning, result, validator);
        }
    }

    bool read_value(std::string prompt, string default_warning, char &result, const std::function<string(char)> validator) {
        if (isatty(fileno(stdin)) && isatty(fileno(stdout))) {
            return read_value_interactive<char>(prompt, default_warning, result, validator);
        } else {
            return read_value_dinossaur<char>(prompt, default_warning, result, validator);
        }
    }

    bool read_value(std::string prompt, string default_warning, Name &result, const std::function<string(Name)> validator) {
        if (isatty(fileno(stdin)) && isatty(fileno(stdout))) {
            return read_value_interactive<Name>(prompt, default_warning, result, validator);
        } else {
            return read_value_dinossaur<Name>(prompt, default_warning, result, validator);
        }
    }

    void clear_screen() {
        for (int i = 0; i < 5; i++) {
            cout << '\n';
        }

        cout << flush;
    }

    void wait_for_enter() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int utf8Len(const char* s) {
        int len = 0;
        while (*s)
            len += (*s++ & 0xc0) != 0x80;
        return len;
    }

} // namespace input

namespace files {
 
} // namespace files
