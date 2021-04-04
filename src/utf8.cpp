#include <string>

#include "utf8.h"

using namespace std;

namespace utf8 {

    /**
     * @brief Returns the number of code points present in the given string.
     * 
     * @param s the string whose UTF8 length is to be returned.
     * @return the number of UTF8 code points present in the given string.
     */
    size_t length(const char* str) {
        size_t len = 0;
        while (*str) 
            len += (*str++ & 0xc0) != 0x80;

        return len;
    } 

    /**
     * @brief Returns the number of code points present in the given string.
     * 
     * @param s the string whose UTF8 length is to be returned.
     * @return the number of UTF8 code points present in the given string.
     */
    size_t length(const string str) {
        return length(str.c_str());
    }

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
    string zfill(string str, const char filler, const size_t length, const bool left) {
        if (utf8::length(str) >= length)
            return str;

        size_t missing_characters = length - utf8::length(str);
        for (size_t i = 0; i < missing_characters; i++) {
            if (left)
                str.insert(str.begin(), filler);
            else
                str.insert(str.end(), filler);
        }

        return str;
    }

    /**
     * @brief Removes whitespace characters at the start of the string.
     * 
     * @param str The string to trim.
     * @return The trimmed string.
     */
    string ltrim(string str) {
        return str.erase(0, str.find_first_not_of("\t\n\v\f\r "));
    }

    /**
     * @brief Removes whitespace characters at the end of the string.
     * 
     * @param str The string to trim.
     * @return The trimmed string.
     */
    string rtrim(string str) {
        return str.erase(str.find_last_not_of("\t\n\v\f\r ") + 1);
    }
    
    /**
     * @brief Removes whitespace characters at both the start and the end of the string.
     * 
     * @param str The string to trim.
     * @return The trimmed string.
     */
    string trim(string str) {
        return ltrim(rtrim(str));
    }
} // namespace utf8
