#include "simple2d_animation_system.hpp"

#include "../../main/engine.hpp"
#include "../components/sprite_component.hpp"
#include "../components/animation2d_component.hpp"
#include "../events/animation_finish_event.hpp"

#include <cmath>

namespace chestnut::engine
{
    CSimple2DAnimationSystem::CSimple2DAnimationSystem( CEngine& engine )
    : ISystem( engine ) 
    {
        m_animatedTextureQuery = engine.getEntityWorld().createQuery(
            ecs::makeEntitySignature<CSpriteComponent, CAnimation2DComponent>()
        );
    }

    void CSimple2DAnimationSystem::update( float dt ) 
    {
        getEngine().getEntityWorld().queryEntities( m_animatedTextureQuery );

        auto it = m_animatedTextureQuery->begin<CSpriteComponent, CAnimation2DComponent>();
        auto end = m_animatedTextureQuery->end<CSpriteComponent, CAnimation2DComponent>();
        for(; it != end; it++)
        {
            auto [texture, animation] = *it;

            SRectangle clipRect;

            if( animation.isAnimPlaying )
            {
                const SAnimationData2D& animData = animation.animSet.mapAnimNameToAnimData[ animation.currentAnimName ];

                if( !animation.isAnimPaused )
                {
                    animation.elapsedAnimTimeSec += dt * animation.animSpeedMultiplier;
                }

                float frameDuration = 1.f / animData.framesPerSec;

                // index in the vector of indices inside animation data, couldn't come up with a better name :)
                unsigned int frameIndexIndex = (unsigned int)( animation.elapsedAnimTimeSec / frameDuration );
                int loopsDone = frameIndexIndex / std::max( (size_t)1UL, animData.vecFrameIndices.size() );
                frameIndexIndex = frameIndexIndex % std::max( (size_t)1UL, animData.vecFrameIndices.size() );

                // update loops to be done only if they're not specified to be infinite
                if( animation.remainingAnimLoops > 0 )
                {
                    // even if animation is paused loopsDone should be 0 then, so it won't change the count
                    animation.remainingAnimLoops = std::max( 0, animation.remainingAnimLoops - loopsDone );

                    if( animation.remainingAnimLoops == 0 )
                    {
                        SAnimationFinishEvent event;
                        event.animName = animation.currentAnimName;
                        event.entity = it.entityId();
                        getEngine().getEventManager().raiseEvent( event );

                        animation.stopAnimation();
                    }
                }

                clipRect = animation.animSet.vecKeyFrameClipRects[ animData.vecFrameIndices[ frameIndexIndex ] ];
            }
            else
            {
                clipRect = animation.animSet.vecKeyFrameClipRects[ animation.animSet.defaultAnimFrameIndex ];
            }

            texture.sprite.setClippingRect( clipRect );
        }
    }
    
} // namespace chestnut::engine
