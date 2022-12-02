#include "simple2d_animation_system.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/ecs_impl/components/sprite_component.hpp"
#include "chestnut/engine/ecs_impl/components/animation2d_component.hpp"
#include "chestnut/engine/ecs_impl/events/animation_finish_event.hpp"

#include <cmath>

namespace chestnut::engine
{
    CSimple2DAnimationSystem::CSimple2DAnimationSystem(systempriority_t priority)
    : ILogicSystem(priority) 
    {
        m_animatedTextureQuery = CEngine::getInstance().getEntityWorld().createQuery(
            ecs::makeEntitySignature<CSpriteComponent, CAnimation2DComponent>()
        );
    }

    void CSimple2DAnimationSystem::update( float dt ) 
    {
        CEngine::getInstance().getEntityWorld().queryEntities( m_animatedTextureQuery );

        auto it = m_animatedTextureQuery->begin<CSpriteComponent, CAnimation2DComponent>();
        auto end = m_animatedTextureQuery->end<CSpriteComponent, CAnimation2DComponent>();
        for(; it != end; it++)
        {
            auto [texture, animation] = *it;

            if(!animation.animationResource)
            {
                continue;
            }

            SAnimation2DSet& animSet = animation.animationResource->m_animationSet;

            if(animSet.vecKeyFrameClipRects.empty())
            {
                continue;
            }

            auto animDataIt = animSet.mapAnimNameToAnimData.find(animation.currentAnimName);
            SRectangle clipRect;

            if(animDataIt == animSet.mapAnimNameToAnimData.end() || !animation.isAnimPlaying)
            {
                clipRect = animSet.vecKeyFrameClipRects[ animSet.defaultAnimFrameIndex ];
            }
            else
            {
                const SAnimation2DDefinition& animData = animDataIt->second;

                float animProgression = animation.elapsedAnimTimeSec / animData.duration;
                int loopsDone = (int)animProgression;

                animation.elapsedAnimTimeSec = std::fmod(animation.elapsedAnimTimeSec, animData.duration);
                animProgression -= loopsDone;
                
                // index in the vector of indices inside animation data, couldn't come up with a better name :)
                unsigned int frameIndexIndex = std::clamp(
                    (unsigned int)( animProgression * (float)animData.vecFrameIndices.size() ),
                    0U,
                    (unsigned int)animData.vecFrameIndices.size() - 1
                );

                unsigned int frameIndex = std::clamp(
                    animData.vecFrameIndices[ frameIndexIndex ],
                    0U,
                    (unsigned int)animSet.vecKeyFrameClipRects.size() - 1
                );

                // update loops to be done only if they're not specified to be infinite
                if(!animation.isAnimPaused && animation.remainingAnimLoops != 0)
                {
                    animation.elapsedAnimTimeSec += dt * animation.animSpeedMultiplier;

                    if(animation.remainingAnimLoops > 0)
                    {
                        // even if animation is paused loopsDone should be 0 then, so it won't change the count
                        animation.remainingAnimLoops = std::max(0, animation.remainingAnimLoops - loopsDone);

                    }
                }
                
                if( animation.remainingAnimLoops == 0 )
                {
                    SAnimationFinishEvent event;
                    event.animName = animation.currentAnimName;
                    event.entity = it.entityId();
                    CEngine::getInstance().getEventManager().raiseEvent( event );

                    animation.stopAnimation();
                }

                clipRect = animSet.vecKeyFrameClipRects[frameIndex];
            }

            texture.sprite.setClippingRect( clipRect );
        }
    }
    
} // namespace chestnut::engine
