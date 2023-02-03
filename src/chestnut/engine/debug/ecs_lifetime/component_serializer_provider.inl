#include "chestnut/engine/main/engine.hpp"

namespace chestnut::engine::debug
{
    template <class C>
    inline void CComponentSerializerProvider<C>::serialize(nlohmann::json &j, ecs::entityid_t entity)
    {
        ecs::CComponentHandle<C> handle = CEngine::getInstance()
        .getEntityWorld()
        .getComponent<C>(entity);

        to_json(j, handle.get());
    }

    template <class C>
    inline void CComponentSerializerProvider<C>::deserialize(const nlohmann::json &j, ecs::entityid_t entity)
    {
        ecs::CComponentHandle<C> handle = CEngine::getInstance()
        .getEntityWorld()
        .createComponent<C>(entity); // if already exists it will return that

        from_json(j, handle.get());
    }

} // namespace chestnut::engine::debug
