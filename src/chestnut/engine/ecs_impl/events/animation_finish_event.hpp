#pragma once

#include <chestnut/ecs/types.hpp>

#include <string>

namespace chestnut::engine
{
    struct SAnimationFinishEvent
    {
        ecs::entityid_t entity;
        std::string animName;
    };

} // namespace chestnut::engine
