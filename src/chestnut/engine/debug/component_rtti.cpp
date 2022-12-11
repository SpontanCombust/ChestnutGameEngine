#include "chestnut/engine/debug/component_rtti.hpp"

namespace chestnut::engine::debug
{
    static std::unordered_map<std::type_index, SComponentDebugTraits> s_registry;

    const std::unordered_map<std::type_index, SComponentDebugTraits> &chestnut::engine::debug::getComponentRTTIRegistry()
    {
        return s_registry;
    }

    void registerComponentRTTI(std::type_index typeIndex, SComponentDebugTraits&& traits)
    {
        s_registry[typeIndex] = std::forward<SComponentDebugTraits>(traits);
    }

} // namespace chestnut::engine::debug
