#include <iostream>
#include <limits>
#include "unistd.h"
#include "utf8.h"

#include "keyboard.h"

using namespace std;

namespace keyboard {

    std::basic_istream<char>& operator>>(std::basic_istream<char>& istream, keyboard::Name &name) {
        name.data.clear();
        
        char ch;
        while ((istream.peek() != '\n' && istream.get(ch)) && utf8::length(name.data) < 15)
            name.data.push_back(ch);

        return istream;
    }

    std::basic_ostream<char>& operator<<(std::basic_ostream<char>& ostream, keyboard::Name &name) {
        return ostream << name.data;
    }

    /**
     * @brief Blocks execution until the user presses the RETURN key.
     */
    void wait_for_enter() {
        cout << "Press ENTER to continue..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    /**
     * @brief Auxiliary function.
     */
    template <typename T>
    bool read_value_interactive(const string prompt, const string warning, T &result, const function<bool(T)> validator) {
        cout << "? " << prompt << flush;
        while (true) {
            // Is true if, and only if, all the content present on the line is of the type T
            bool is_input_valid = false;
            const char *error = warning.c_str();

            try {
                is_input_valid = cin.peek() != '\n' 
                    && cin >> result && cin.peek() == '\n'
                    && validator(result);
            } catch (const char *exception) {
                error = exception;
            }

            // Clear the buffer
            // We do this to avoid having "123a[EOF]" trigger the loop more than once.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (is_input_valid) {
                cout << "\x1B[F\x1B[G✓\x1B[" << prompt.length() + 3 << "G\x1B[K" << result << "\n\x1B[K" << flush;
                return true;
            } else {
                if (!cin.eof())
                    cout << ">> " << error << "\x1B[F";

                cout << "\x1B[" << prompt.length() + 3 << "G\x1B[K";

                if (cin.eof()) {
                    cout << "EOF\n\x1B[F\x1B[G×\x1B[E\x1B[K" << flush;
                    return false;
                }
            }
        }
    }

    /**
     * @brief Auxiliary function.
     */
    template <typename T>
    bool read_value_dinossaur(const string prompt, const string warning, T &result, const function<bool(T)> validator) {
        while (true) {
            cout << "? " << prompt << flush;

            bool is_input_valid = false;
            const char *error = warning.c_str();

            try {
                is_input_valid = cin.peek() != '\n' 
                    && cin >> result && cin.peek() == '\n'
                    && validator(result);
            } catch (const char *exception) {
                error = exception;
            }
                
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (is_input_valid) {
                return true;
            } else {
                if (cin.eof()) {
                    cout << "EOF" << endl;
                    return false;
                } else {
                    cout << "\u26A0 " << error << endl;
                }
            }
        }
    }

    /**
     * @brief Auxiliary function.
     */
    template <typename T>
    inline bool read_value_adaptive(const string prompt, const string warning, T &result, const function<bool(T)> validator = [] (T res) { return true; }) {
        if (isatty(fileno(stdin)) && isatty(fileno(stdout)))
            return keyboard::read_value_interactive<T>(prompt, warning, result, validator);
        
        return keyboard::read_value_dinossaur<T>(prompt, warning, result, validator);
    }

    /**
     * @brief Prompts the user to provide a value through console input.
     * On interactive terminals, it will be done in a "fancy" fashion and in a single line.
     * Otherwise, it will be done in a more "traditional" manner. 
     * 
     * @param prompt The text that will be used to prompt the user for a value.
     * @param warning The error message that will be presented to the user if the value could not be parsed or if the validator function returns false.
     * @param result The variable where the result will be stored.
     * @param validator An optional function that determines if the value is valid.
     * This function is only executed after the parsing of the value was successful.
     * If this function throws a string, it will be presented to the user as an error message.
     * If this function returns false, the warning message will be presented to the user.
     * 
     * @return true, if the input is valid, or false, if cin has reached EOF. 
     */
    bool read_value(const string prompt, const string warning, unsigned int &result, const function<bool(unsigned int)> validator) {
        return keyboard::read_value_adaptive<unsigned int>(prompt, warning, result, validator);
    }

    /**
     * @brief Prompts the user to provide a value through console input.
     * On interactive terminals, it will be done in a "fancy" fashion and in a single line.
     * Otherwise, it will be done in a more "traditional" manner. 
     * 
     * @param prompt The text that will be used to prompt the user for a value.
     * @param warning The error message that will be presented to the user if the value could not be parsed or if the validator function returns false.
     * @param result The variable where the result will be stored.
     * @param validator An optional function that determines if the value is valid.
     * This function is only executed after the parsing of the value was successful.
     * If this function throws a string, it will be presented to the user as an error message.
     * If this function returns false, the warning message will be presented to the user.
     * 
     * @return true, if the input is valid, or false, if cin has reached EOF. 
     */
    bool read_value(const string prompt, const string warning, char &result, const function<bool(char)> validator) {
        return keyboard::read_value_adaptive<char>(prompt, warning, result, validator);
    }

        /**
     * @brief Prompts the user to provide a value through console input.
     * On interactive terminals, it will be done in a "fancy" fashion and in a single line.
     * Otherwise, it will be done in a more "traditional" manner. 
     * 
     * @param prompt The text that will be used to prompt the user for a value.
     * @param warning The error message that will be presented to the user if the value could not be parsed or if the validator function returns false.
     * @param result The variable where the result will be stored.
     * @param validator An optional function that determines if the value is valid.
     * This function is only executed after the parsing of the value was successful.
     * If this function throws a string, it will be presented to the user as an error message.
     * If this function returns false, the warning message will be presented to the user.
     * 
     * @return true, if the input is valid, or false, if cin has reached EOF. 
     */
    bool read_value(const string prompt, const string warning, Name &result, const function<bool(Name)> validator) {
        return keyboard::read_value_adaptive<Name>(prompt, warning, result, validator);
    }
} // namespace keyboard
