#ifndef __CHESTNUT_ENGINE_ANIMATION_FINISH_EVENT_H__
#define __CHESTNUT_ENGINE_ANIMATION_FINISH_EVENT_H__

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

#endif // __CHESTNUT_ENGINE_ANIMATION_FINISH_EVENT_H__