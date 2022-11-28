#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/graphics/animation2d.hpp"

namespace chestnut::engine
{
    //TODO refactor the component
    struct CAnimation2DComponent
    {
        SAnimation2DSet animSet;

        bool isAnimPlaying = false;
        bool isAnimPaused = false;
        std::string currentAnimName = "";
        float elapsedAnimTimeSec = 0.f;
        int remainingAnimLoops = -1;
        float animSpeedMultiplier = 1.f;


        // Checks if animation with that name exits, changes component state only if it exists
        // -1 for infinite loops
        // If any animation is currently played, cancels it
        CHESTNUT_API void playAnimation( const char *animationName, int loops = -1, float speedMult = 1.f );
        CHESTNUT_API void pauseAnimation();
        CHESTNUT_API void resumeAnimation();
        CHESTNUT_API void stopAnimation();
    };

} // namespace chestnut::engine
