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
        tl::optional<std::string> m_sceneFilePath;
        nlohmann::json m_sceneJson;

    public:
        static tl::expected<std::shared_ptr<CSceneResource>, std::string> 
        loadFromFile(const char *filePath) noexcept;

        // Serialize all entities in engine's entity world
        static tl::expected<std::shared_ptr<CSceneResource>, std::string> 
        loadFromEntityWorld() noexcept;


        // If comes accross an error will return error message value
        tl::optional<std::string> parseAndTransferToScene() const;

        // If comes accross an error will return error message value
        tl::optional<std::string> saveToFile(const char *filePath) const;
    };

} // namespace chestnut::engine
