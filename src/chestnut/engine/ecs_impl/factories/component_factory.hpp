#pragma once


#include <chestnut/ecs/types.hpp>

namespace chestnut::engine
{
    // These are not your textbook definitions of factories, but their purpose is the same   

    template<class C>
    class CComponentFactory
    {
    public:
        static bool create(ecs::entityid_t entity);
        static void dispose(ecs::entityid_t entity);
    };

    typedef bool (*ComponentFactoryCreateCallback)(ecs::entityid_t);
    typedef void (*ComponentFactoryDisposeCallback)(ecs::entityid_t);

} // namespace chestnut::engine

#include "component_factory.inl"