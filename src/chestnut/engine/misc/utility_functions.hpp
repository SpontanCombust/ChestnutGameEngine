#pragma once


#include <filesystem>
#include <string>
#include <tuple>
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

    // Takes a path and turns it into path relative to the assets directory
    // First tuple element is the transformed path, 
    // second tuple element is bool value indicating whether path is pointing to element somewhere inside assets folder
    std::tuple<std::filesystem::path, bool> assetPathFromAbsolute(const std::filesystem::path& path);
    // Turns a relative asset path into real, absolute path on the system
    std::filesystem::path assetPathToAbsolute(const std::filesystem::path& path);
    
    std::string makeNFDFiltersList(const std::vector<std::string>& vecExtensions);
    
} // namespace chestnut::engine
