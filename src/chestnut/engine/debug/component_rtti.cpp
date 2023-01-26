#include "chestnut/engine/debug/component_rtti.hpp"

#include <string>

namespace chestnut::engine::debug
{
    static std::unordered_map<std::type_index, SComponentRTTI> s_registry;
    static std::unordered_map<std::string, std::type_index> s_mapTypeNameToIndex;

    const std::unordered_map<std::type_index, SComponentRTTI> &chestnut::engine::debug::getComponentRTTIRegistry()
    {
        return s_registry;
    }

    void registerComponentRTTI(std::type_index typeIndex, SComponentRTTI&& traits)
    {
        s_registry[typeIndex] = std::forward<SComponentRTTI>(traits);
        s_mapTypeNameToIndex.insert({traits.name, typeIndex}); // can't use bracket operator as std::type_index is not default constructible
    }

    SComponentRTTI *getComponentRTTIByTypeIndex(std::type_index typeIndex)
    {
        auto it = s_registry.find(typeIndex);
        if(it != s_registry.end())
        {
            return &it->second;
        }

        return nullptr;
    }

    SComponentRTTI *getComponentRTTIByTypeName(const char *typeName)
    {
        auto it = s_mapTypeNameToIndex.find(typeName);
        if(it != s_mapTypeNameToIndex.end())
        {
            return &s_registry[it->second];
        }

        return nullptr;
    }

} // namespace chestnut::engine::debug
