#include "chestnut/engine/ecs_impl/components/animation2d_component.hpp"

namespace chestnut::engine
{    
    CAnimation2DComponent::CAnimation2DComponent() 
    {
        isAnimPlaying = false;
        isAnimPaused = false;
        currentAnimName = "";
        elapsedAnimTimeSec = 0.f;
        remainingAnimLoops = 0;
        animSpeedMultiplier = 1.f;
    }

    void CAnimation2DComponent::playAnimation( const char *animationName, int loops, float speedMult ) 
    {
        auto it = animSet.mapAnimNameToAnimData.find( animationName );
        if( it != animSet.mapAnimNameToAnimData.end() )
        {
            isAnimPlaying = true;
            isAnimPaused = false;
            currentAnimName = animationName;
            elapsedAnimTimeSec = 0.f;
            remainingAnimLoops = loops;
            animSpeedMultiplier = speedMult;
        }
    }

    void CAnimation2DComponent::pauseAnimation() 
    {
        isAnimPaused = true;
    }

    void CAnimation2DComponent::resumeAnimation() 
    {
        isAnimPaused = false;
    }

    void CAnimation2DComponent::stopAnimation() 
    {
        isAnimPlaying = false;
        isAnimPaused = false;
        currentAnimName = "";
        elapsedAnimTimeSec = 0.f;
        remainingAnimLoops = 0;
        animSpeedMultiplier = 1.f;
    }
} // namespace chestnut::engine
