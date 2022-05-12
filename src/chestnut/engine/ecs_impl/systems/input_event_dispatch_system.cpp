#include "input_event_dispatch_system.hpp"

#include "../../main/engine.hpp"

#include <SDL_events.h>

namespace chestnut::engine
{      
    CInputEventDispatchSystem::CInputEventDispatchSystem( CEngine& engine ) : ISystem( engine )
    {

    }

    void CInputEventDispatchSystem::update( float deltaTime ) 
    {
        CEventManager& eventManager = getEngine().getEventManager();

        SDL_Event sdlEvent;

        while( SDL_PollEvent( &sdlEvent ) )
        {
            switch( sdlEvent.type )
            {
                case SDL_CONTROLLERAXISMOTION:
                    eventManager.raiseEvent( sdlEvent.caxis );
                    break;
                case SDL_CONTROLLERBUTTONDOWN:
                case SDL_CONTROLLERBUTTONUP:
                    eventManager.raiseEvent( sdlEvent.cbutton );
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    eventManager.raiseEvent( sdlEvent.key );
                    break;
                case SDL_MOUSEMOTION:
                    eventManager.raiseEvent( sdlEvent.motion );
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    eventManager.raiseEvent( sdlEvent.button );
                    break;
                case SDL_MOUSEWHEEL:
                    eventManager.raiseEvent( sdlEvent.wheel );
                    break;
                case SDL_WINDOWEVENT:
                    eventManager.raiseEvent( sdlEvent.window );
                    break;
                case SDL_QUIT:
                    eventManager.raiseEvent( sdlEvent.quit );
                    break;
                default:
                    break;
            }
        }
    }


} // namespace chestnut::engine
