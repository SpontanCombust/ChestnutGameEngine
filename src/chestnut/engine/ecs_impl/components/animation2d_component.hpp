#ifndef __CHESTNUT_ENGINE_ANIMATION2D_COMPONENT_H__
#define __CHESTNUT_ENGINE_ANIMATION2D_COMPONENT_H__

#include "chestnut/engine/macros.hpp"
#include "../../graphics/animation2d.hpp"

namespace chestnut::engine
{
    struct CHESTNUT_API CAnimation2DComponent
    {
        SAnimationSet2D animSet;

        bool isAnimPlaying;
        bool isAnimPaused;
        std::string currentAnimName;
        float elapsedAnimTimeSec;
        int remainingAnimLoops;
        float animSpeedMultiplier;


        CAnimation2DComponent();

        // Checks if animation with that name exits, changes component state only if it exists
        // -1 for infinite loops
        // If any animation is currently played, cancels it
        void playAnimation( const char *animationName, int loops = -1, float speedMult = 1.f );
        void pauseAnimation();
        void resumeAnimation();
        void stopAnimation();
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_ANIMATION2D_COMPONENT_H__