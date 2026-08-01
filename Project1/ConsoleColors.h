#ifndef CONSOLE_COLORS_H
#define CONSOLE_COLORS_H

#include <string>

// Creating a namespace to keep our color variables organized
namespace Colors {
    // RESET (Crucial to revert the console back to its default state)
    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";

    // FOREGROUND COLORS
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";

    // BACKGROUND COLORS (Optional: for highlighting critical data)
    const std::string BG_RED = "\033[41m";
    const std::string BG_GREEN = "\033[42m";
}

#endif