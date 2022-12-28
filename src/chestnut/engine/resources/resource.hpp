#pragma once


#include "chestnut/engine/macros.hpp"

#include <tl/expected.hpp>
#include <tl/optional.hpp>

#include <filesystem>
#include <memory>
#include <tuple>
#include <vector>


namespace chestnut::engine
{
    class CHESTNUT_API IResource
    {
    public:
        // Resource should be able to get identified by some unqiue, abstract "location"
        // Usually this location is path to a file on a disk, but it doesn't have to be exactly that
        // If resource is not loaded from a file this stay as nullopt
        tl::optional<std::filesystem::path> m_location = tl::nullopt;

    public:
        virtual ~IResource() = default;

        // Resources should passed around using (smart) pointers and not be trivially copied
        IResource(const IResource&) = delete;
        IResource& operator=(const IResource&) = delete;
        IResource(IResource&&) = delete;
        IResource& operator=(IResource&&) = delete;

        // Signature of a static method to base off resource loading methods in derived classes.
        // It should return tl::expected instead of throwing an exception.
        // Method takes one argument that denotes a path to a single file that contains all the information needed to load a resource.
        // It is mandatory to implement this static method in a resource class if you want to use it with CResourceManager.
        static tl::expected<std::shared_ptr<IResource>, std::string> 
        load(std::filesystem::path location) noexcept = delete;


        bool wasLoadedFromFile() const noexcept;
        tl::optional<size_t> locationHash() const noexcept;

    protected:
        // Resources should be constructed only using a static "from" method
        IResource(tl::optional<std::filesystem::path> location) noexcept;

        // Returns file's extension and whether it is included in supported extensions 
        static std::tuple<std::string, bool> isExtensionSupported(
            const std::filesystem::path& path, 
            const std::vector<std::string>& supportedExtensions) noexcept;
    };

} // namespace chestnut::engine

