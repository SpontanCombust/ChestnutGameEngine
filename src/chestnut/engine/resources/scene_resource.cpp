#include "chestnut/engine/resources/scene_resource.hpp"
#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/debug/component_rtti.hpp"

#include <fstream>

namespace chestnut::engine
{
    tl::expected<std::shared_ptr<CSceneResource>, std::string> 
    CSceneResource::loadFromFile(const char *filePath) noexcept
    {
        LOG_INFO("Loading scene resource from file " << filePath << "...");

        try
        {
            std::ifstream f(filePath);
            if(!f)
            {
                return tl::make_unexpected("Failed to load the file");
            }

            auto j = nlohmann::json::parse(f);
            if(!j.contains("entities") || !j.at("entities").is_array())
            {
                return tl::make_unexpected("No entities array found in the file");
            }

            auto resource = std::make_shared<CSceneResource>();
            resource->m_sceneFilePath = filePath;
            resource->m_sceneJson = j;

            return resource;
        }
        catch(const std::exception& e)
        {
            return tl::make_unexpected(e.what());
        }
    }

    tl::expected<std::shared_ptr<CSceneResource>, std::string>
    CSceneResource::loadFromEntityWorld() noexcept
    {
        const auto& world = CEngine::getInstance().getEntityWorld();

        auto entitiesArrayJson = nlohmann::json::array();

        try
        {
            auto it = world.entityIterator.cbegin();
            auto end = world.entityIterator.cend();
            for(; it != end; ++it)
            {
                auto entityJson = nlohmann::json::object();
                auto sign = it.signature();

                for(const std::type_index& typeIndex : sign.m_setComponentTypes)
                {
                    const auto rtti = debug::getComponentRTTIByTypeIndex(typeIndex);
                    if(rtti)
                    {
                        nlohmann::json componentJson;
                        rtti->serializer(componentJson, it.id());

                        entityJson[rtti->name] = componentJson;
                    }
                }

                entitiesArrayJson.push_back(entityJson);
            }   
        }
        catch(const std::exception& e)
        {
            return tl::make_unexpected(e.what());
        }  

        auto resource = std::make_shared<CSceneResource>();
        resource->m_sceneFilePath = tl::nullopt;
        resource->m_sceneJson = {
            {"entities", entitiesArrayJson}
        };

        return resource;
    }

    tl::optional<std::string> CSceneResource::parseAndTransferToScene() const
    {
        auto& world = CEngine::getInstance().getEntityWorld();
        
        try
        {
            auto entitiesArrayJson = m_sceneJson.at("entities");

            for(const auto& entityJson : entitiesArrayJson)
            {
                ecs::entityid_t entity = world.createEntity();

                for(const auto& [componentName, componentJson] : entityJson.items())
                {
                    const auto rtti = debug::getComponentRTTIByTypeName(componentName.c_str());
                    if(!rtti)
                    {
                        LOG_WARNING("Unknown component type parsed: " << componentName);
                        continue;
                    }
                    
                    rtti->deserializer(componentJson, entity);
                }
            }
        }
        catch(const std::exception& e)
        {
            return tl::make_optional(e.what());
        }
        
        return tl::nullopt;
    }

    tl::optional<std::string> CSceneResource::saveToFile(const char *filePath) const
    {
        LOG_INFO("Saving scene resource to file " << filePath << "...");

        std::ofstream f(filePath);
        if(!f)
        {
            return tl::make_optional("Failed to open file");
        }

        f << m_sceneJson.dump(4) << std::endl;

        return tl::nullopt;
    }

} // namespace chestnut::engine
