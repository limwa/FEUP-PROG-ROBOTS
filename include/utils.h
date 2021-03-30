#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <functional>
#include <limits>

namespace input {
    
    struct Name { 
        std::string name; 
    };
    std::basic_istream<char>& operator>>(std::basic_istream<char>&, Name&); 
    std::basic_ostream<char>& operator<<(std::basic_ostream<char>&, Name&);

    bool read_value(std::string prompt, std::string default_warning, unsigned int &result, const std::function<std::string(unsigned int)> validator = [](unsigned int res) { return std::string(); });
    bool read_value(std::string prompt, std::string default_warning, char &result, const std::function<std::string(char)> validator = [](char res) { return std::string(); });
    bool read_value(std::string prompt, std::string default_warning, Name &result, const std::function<std::string(Name)> validator = [](Name res) { return std::string(); });
    
    void clear_screen();
    void wait_for_enter();

    int utf8Len(const char* s);

} // namespace input

namespace files {

} // namespace files

#endif
