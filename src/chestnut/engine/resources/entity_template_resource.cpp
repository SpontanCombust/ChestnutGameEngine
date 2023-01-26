#include "entity_template_resource.hpp"

#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/debug/component_rtti.hpp"
#include "chestnut/engine/main/engine.hpp"

#include <fstream>

namespace chestnut::engine
{    
    CEntityTemplateResource::CEntityTemplateResource(
        std::filesystem::path location,
        nlohmann::json entJson
    ) noexcept
    : IResource(location), m_entJson(entJson)
    {

    }

    tl::expected<std::shared_ptr<CEntityTemplateResource>, std::string> 
    CEntityTemplateResource::load(std::filesystem::path location) noexcept
    {
        LOG_INFO("Loading entity template resource from file " << location << "...");

        if(!std::filesystem::exists(location))
        {
            return tl::make_unexpected("File does not exist");
        }

        auto [ext, supported] = isExtensionSupported(location, SUPPORTED_FILE_EXTENSIONS);
        if(!supported)
        {
            return tl::make_unexpected("File type not supported: " + ext);
        }

        try
        {
            std::ifstream f(location);
            if(!f)
            {
                return tl::make_unexpected("Failed to load the file");
            }

            auto j = nlohmann::json::parse(f);
            auto resource = std::shared_ptr<CEntityTemplateResource>(new CEntityTemplateResource(location, j));

            return resource;
        }
        catch(const std::exception& e)
        {
            return tl::make_unexpected(e.what());
        }
    }

    tl::expected<ecs::entityid_t, std::string> CEntityTemplateResource::createEntity() const
    {
        auto& w = CEngine::getInstance().getEntityWorld();

        ecs::entityid_t ent = w.createEntity();

        try
        {
            for(const auto& [componentName, componentJson] : m_entJson.items())
            {
                const auto rtti = debug::getComponentRTTIByTypeName(componentName.c_str());
                if(!rtti)
                {
                    LOG_WARNING("Unknown component type parsed: " << componentName);
                    continue;
                }
                
                rtti->deserializer(componentJson, ent);
            }
        }
        catch(const std::exception& e)
        {
            w.destroyEntity(ent);
            return tl::make_unexpected(e.what());
        }

        return ent;
    }

} // namespace chestnut::engine
