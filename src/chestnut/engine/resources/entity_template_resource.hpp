#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/resource.hpp"

#include <chestnut/ecs/types.hpp>
#include <nlohmann/json.hpp>


namespace chestnut::engine
{
    class CHESTNUT_API CEntityTemplateResource : public IResource
    {
    public:
        inline static const std::vector<std::string> SUPPORTED_FILE_EXTENSIONS = {
            "ent", "entity"
        };

        nlohmann::json m_entJson;

    public:
        static tl::expected<std::shared_ptr<CEntityTemplateResource>, std::string> 
        load(std::filesystem::path location) noexcept;


        // If comes accross an error will return error message value
        tl::expected<ecs::entityid_t, std::string> createEntity() const;


    private:
        CEntityTemplateResource(
            std::filesystem::path location,
            nlohmann::json entJson
        ) noexcept;
    };

} // namespace chestnut::engine
