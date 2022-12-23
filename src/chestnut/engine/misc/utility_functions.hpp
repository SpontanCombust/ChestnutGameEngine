#pragma once


#include <string>
#include <typeindex>

namespace chestnut::engine
{
    // Utility message boxes that can display useful information to the user
    // They can be used even before initializing the engine

    void messageBoxInfo(const std::string& message, const char *title = "Error");
    bool messageBoxYesNo(const std::string& message, const char *title);


    // Returns demangled name of the type

    const char * rttiTypeName(const std::type_index& typeIndex);
    const char * rttiTypeName(const std::type_info& typeInfo);
    
} // namespace chestnut::engine
