#pragma once

#include <chestnut/ecs/types.hpp>
#include <nlohmann/json.hpp>

namespace chestnut::engine::debug
{
    template<class C>
    class CComponentSerializerProvider
    {
    public:
        static void serialize(nlohmann::json& j, ecs::entityid_t entity);
        static void deserialize(const nlohmann::json& j, ecs::entityid_t entity);
    };

    typedef void (*ComponentSerializerCallback)(nlohmann::json& j, ecs::entityid_t entity);
    typedef void (*ComponentDeserializerCallback)(const nlohmann::json& j, ecs::entityid_t entity);

} // namespace chestnut::engine::debug

#include "component_serializer_provider.inl"