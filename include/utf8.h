#ifndef UTF8_H
#define UTF8_H

#include <string>

namespace utf8 {

    /**
     * @brief Returns the number of code points present in the given string.
     * 
     * @param s the string whose UTF8 length is to be returned.
     * @return The number of UTF8 code points present in the given string.
     */
    std::size_t length(const char* str);

    /**
     * @brief Returns the number of code points present in the given string.
     * 
     * @param s the string whose UTF8 length is to be returned.
     * @return The number of UTF8 code points present in the given string.
     */
    std::size_t length(const std::string str);

    /**
     * @brief Adds filler characters until the given string has the specified length.
     * 
     * @param s The string that will be filled.
     * @param filler The filler character.
     * @param length The desired length.
     * @param left true to add the filler characters to the start of the string, false otherwise.
     * 
     * @return The filled string.
     */
    std::string zfill(std::string str, const char filler, const std::size_t length, const bool left);

    /**
     * @brief Removes whitespace characters at the start of the string.
     * 
     * @param str The string to trim.
     * @return The trimmed string.
     */
    std::string ltrim(std::string str);

    /**
     * @brief Removes whitespace characters at the end of the string.
     * 
     * @param str The string to trim.
     * @return The trimmed string.
     */
    std::string rtrim(std::string str);

    /**
     * @brief Removes whitespace characters at both the start and the end of the string.
     * 
     * @param str The string to trim.
     * @return The trimmed string.
     */
    std::string trim(std::string str);
} // namespace utf8

#endif
