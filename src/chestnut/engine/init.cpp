#include "chestnut/engine/init.hpp"

#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/resources/resource_manager.hpp"
#include "chestnut/engine/debug/component_rtti.hpp"
#include "chestnut/engine/ecs_impl/components/animation2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/collision2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/identity_component.hpp"
#include "chestnut/engine/ecs_impl/components/kinematics2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/model2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/render_layer_component.hpp"
#include "chestnut/engine/ecs_impl/components/sprite_component.hpp"
#include "chestnut/engine/ecs_impl/components/tag_component.hpp"
#include "chestnut/engine/ecs_impl/components/timer_component.hpp"
#include "chestnut/engine/ecs_impl/components/transform2d_component.hpp"
#include "chestnut/engine/serialization/serializers_ecs_impl/serializers_components.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_animation2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_collision2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_identity_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_kinematics2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_model2d_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_render_layer_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_sprite_component_view.hpp"
#include "chestnut/engine/debug/editor/component_views/gui_transform2d_component_view.hpp"

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


namespace chestnut::engine
{
    bool wasInit = false;

    bool chestnutInit( int glVerMajor, int glVerMinor, bool glAllowOnlyCoreProfile )
    {
        int flags;


        LOG_INFO("Initializing SDL2...");

        flags = SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS | SDL_INIT_AUDIO;
        if( SDL_Init( flags ) < 0 )
        {
            LOG_ERROR( "SDL failed to initialize! " << SDL_GetError() );
            return false;
        }


        LOG_INFO("Initializing SDL_TTF...");

        if( TTF_Init() < 0 )
        {
            LOG_ERROR( "SDL_ttf failed to initialize!" << TTF_GetError() );
            SDL_Quit();
            return false;
        }



        LOG_INFO("Initializing SDL_Mixer...");

        flags = MIX_INIT_FLAC | MIX_INIT_MID | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_OPUS;
        if( Mix_Init(flags) == 0 )
        {
            LOG_ERROR( "SDL_mixer failed to initialize!" << Mix_GetError() );
            TTF_Quit();
            SDL_Quit();
            return false;
        }

        LOG_INFO("Supported audio formats:");
        if((flags & MIX_INIT_FLAC) > 0) LOG_INFO("FLAC");
        if((flags & MIX_INIT_MID) > 0) LOG_INFO("MID");
        if((flags & MIX_INIT_MP3) > 0) LOG_INFO("MP3");
        if((flags & MIX_INIT_OGG) > 0) LOG_INFO("OGG");

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            LOG_ERROR( "SDL_mixer failed to opem audio device!" << Mix_GetError() );
            TTF_Quit();
            SDL_Quit();
            return false;
        }

        if( SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, glVerMajor ) < 0 )
        {
            LOG_WARNING( "Failed to set OpenGL major version!" );
            LOG_WARNING( TTF_GetError() );
            Mix_CloseAudio();
            TTF_Quit();
            SDL_Quit();
            return false;
        }
        if( SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, glVerMinor ) < 0 )
        {
            LOG_WARNING( "Failed to set OpenGL minor version!" );
            LOG_WARNING( TTF_GetError() );
            Mix_CloseAudio();
            TTF_Quit();
            SDL_Quit();
            return false;
        }

        if( glAllowOnlyCoreProfile )
        {
            SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
        }
        else
        {
            SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY );
        }


        LOG_INFO("Preparing debug RTTI...");

        debug::registerComponentRTTI<CAnimation2DComponent>();
        debug::registerComponentRTTI<CCollision2DComponent>();
        debug::registerComponentRTTI<CIdentityComponent>();
        debug::registerComponentRTTI<CKinematics2DComponent>();
        debug::registerComponentRTTI<CModel2DComponent>();
        debug::registerComponentRTTI<CRenderLayerComponent>();
        debug::registerComponentRTTI<CSpriteComponent>();
        debug::registerComponentRTTI<CTagComponent>();
        debug::registerComponentRTTI<CTransform2DComponent>();

        wasInit = true;

        return true;
    }

    bool chestnutWasInit() 
    {
        return wasInit;
    }

    void chestnutQuit()
    {
        if( wasInit )
        {
            Mix_CloseAudio();
            TTF_Quit();
            SDL_Quit();

            wasInit = false;
        }
    }

} // namespace chestnut::engine
