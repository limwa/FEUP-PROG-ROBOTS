#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <string>
#include <functional>

namespace keyboard {

    struct Name {
        std::string data;
    };

    /**
     * @brief Blocks execution until the user presses the RETURN key.
     */
    void wait_for_enter();

    /**
     * @brief Prompts the user to provide a value through console input.
     * On interactive terminals, it will be done in a "fancy" fashing and in a single line.
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
    bool read_value(const std::string prompt, const std::string warning, unsigned int &result, const std::function<bool(unsigned int)> validator = [](unsigned int res) { return true; });
    
    /**
     * @brief Prompts the user to provide a value through console input.
     * On interactive terminals, it will be done in a "fancy" fashing and in a single line.
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
    bool read_value(const std::string prompt, const std::string warning, char &result, const std::function<bool(char)> validator = [](char res) { return true; });

    bool read_value(const std::string prompt, const std::string warning, Name &result, const std::function<bool(Name)> validator = [](Name res) { return true; });
} // namespace keyboard

#endif
