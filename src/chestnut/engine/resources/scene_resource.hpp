#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/resource.hpp"

#include <nlohmann/json.hpp>
#include <tl/optional.hpp>

#include <string>

namespace chestnut::engine
{
    class CSceneResource : public IResource
    {
    public:
        inline static const std::vector<std::string> SUPPORTED_FILE_EXTENSIONS = {
            "scene"
        };

        nlohmann::json m_sceneJson;

    public:
        static tl::expected<std::shared_ptr<CSceneResource>, std::string> 
        loadFromFile(std::filesystem::path filePath) noexcept;

        // Serialize all entities in engine's entity world
        static tl::expected<std::shared_ptr<CSceneResource>, std::string> 
        loadFromEntityWorld() noexcept;

        // Calls loadFromFile
        static tl::expected<std::shared_ptr<CSceneResource>, std::string> 
        load(std::filesystem::path location) noexcept;


        // If comes accross an error will return error message value
        tl::optional<std::string> parseAndTransferToScene() const;

        // If comes accross an error will return error message value
        tl::optional<std::string> saveToFile(const char *filePath) const;


    private:
        CSceneResource(tl::optional<std::filesystem::path> location) noexcept;
    };

} // namespace chestnut::engine
