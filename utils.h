#include <iostream>
#include <functional>
#include <limits>

namespace input {

    bool read_value(std::string prompt, std::string warning, unsigned int &result, const std::function<bool(unsigned int)> validator = [](unsigned int res) { return true; });
    bool read_value(std::string prompt, std::string warning, char &result, const std::function<bool(char)> validator = [](char res) { return true; });
    
    void clear_screen();
    void wait_for_enter();
} // namespace input

namespace files {

} // namespace files