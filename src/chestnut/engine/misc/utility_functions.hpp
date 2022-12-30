#pragma once

#include "chestnut/engine/macros.hpp"

#include <filesystem>
#include <string>
#include <tuple>
#include <typeindex>

namespace chestnut::engine
{
    // Utility message boxes that can display useful information to the user
    // They can be used even before initializing the engine
    CHESTNUT_API void messageBoxInfo(const std::string& message, const char *title = "Error");
    CHESTNUT_API bool messageBoxYesNo(const std::string& message, const char *title);

    // Returns demangled name of the type
    CHESTNUT_API const char * rttiTypeName(const std::type_index& typeIndex);
    CHESTNUT_API const char * rttiTypeName(const std::type_info& typeInfo);

    // Takes a path and turns it into path relative to the assets directory
    // First tuple element is the transformed path, 
    // second tuple element is bool value indicating whether path is pointing to element somewhere inside assets folder
    CHESTNUT_API std::tuple<std::filesystem::path, bool> assetPathFromAbsolute(const std::filesystem::path& path);
    // Turns a relative asset path into real, absolute path on the system
    CHESTNUT_API std::filesystem::path assetPathToAbsolute(const std::filesystem::path& path);
    
    CHESTNUT_API std::string makeNFDFiltersList(const std::vector<std::string>& vecExtensions);
    
} // namespace chestnut::engine
