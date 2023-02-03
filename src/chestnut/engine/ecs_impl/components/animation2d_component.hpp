#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/animation2d_resource.hpp"

namespace chestnut::engine
{
    struct CAnimation2DComponent
    {
        std::shared_ptr<CAnimation2DResource> animationResource;

        float animSpeedMultiplier = 1.f;
        int remainingAnimLoops = -1; // -1 for infinite loops

        std::string currentAnimName = "";
        bool isAnimPlaying = false;
        bool isAnimPaused = false;
        float elapsedAnimTimeSec = 0.f;


        // Checks if animation with that name exits, changes component state only if it exists
        // If any animation is currently played, cancels it
        CHESTNUT_API void playAnimation(const char *animationName);
        CHESTNUT_API void pauseAnimation();
        CHESTNUT_API void resumeAnimation();
        CHESTNUT_API void stopAnimation();
    };

} // namespace chestnut::engine
