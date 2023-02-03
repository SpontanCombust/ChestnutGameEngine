#include "chestnut/engine/resources/resource.hpp"

#include <algorithm>

namespace chestnut::engine
{
    IResource::IResource(tl::optional<std::filesystem::path> location) noexcept
    {
        if(location.has_value())
        {
            *location = std::filesystem::absolute(*location);
        }

        m_location = location;
    }

    bool IResource::wasLoadedFromFile() const noexcept
    {
        return m_location.has_value();
    }

    tl::optional<size_t> IResource::locationHash() const noexcept
    {
        return m_location.map([](auto p) { return std::filesystem::hash_value(p); });
    }

    std::tuple<std::string, bool> IResource::isExtensionSupported(
        const std::filesystem::path& path, 
        const std::vector<std::string> &supportedExtensions) noexcept
    {
        std::string ext = path.extension().string();
        if(ext == "")
        {
            return {ext, false};
        }

        // get rid of the dot at the beginning
        ext = ext.substr(1);

        // make all lowercase
        std::transform(ext.begin(), ext.end(), ext.begin(),
            [](unsigned char c) {
                return std::tolower(c);
            }
        );

        // check if extension is among those supported
        bool isSupported = std::any_of(
            supportedExtensions.begin(), 
            supportedExtensions.end(),
            [&ext](auto v) { return v == ext; }
        );

        if(!isSupported)
        {
            return {ext, false};
        }

        return {ext, true};
    }

} // namespace chestnut::engine
