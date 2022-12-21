#pragma once

#include <string>

namespace chestnut::engine
{
    // Utility message boxes that can display useful information to the user
    // They can be used even before initializing the engine

    void messageBoxInfo(const std::string& message, const char *title = "Error");

    bool messageBoxYesNo(const std::string& message, const char *title);

} // namespace chestnut::engine
