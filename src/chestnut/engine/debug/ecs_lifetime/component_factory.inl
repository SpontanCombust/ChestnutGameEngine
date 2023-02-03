#include "chestnut/engine/main/engine.hpp"

namespace chestnut::engine::debug
{
    template<class C>
    bool CComponentFactory<C>::create(ecs::entityid_t entity) 
    {
        return (bool)CEngine::getInstance()
        .getEntityWorld()
        .createComponent<C>(entity);
    }

    template<class C>
    void CComponentFactory<C>::dispose(ecs::entityid_t entity) 
    {
        CEngine::getInstance()
        .getEntityWorld()
        .destroyComponent<C>(entity);
    }

} // namespace chestnut::engine::debug
