#include "sdl_event_dispatch_system.hpp"

#include "engine/event_system/events/events.hpp"
#include "engine/globals.hpp"

namespace chestnut
{      
    void CSDLEventDispatchSystem::update( uint32_t deltaTime ) 
    {
        SDL_Event sdlEvent;

        while( SDL_PollEvent( &sdlEvent ) )
        {
            switch( sdlEvent.type )
            {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                {
                    SKeyboardEvent *keyboardEvent = theEventManager.raiseEvent<SKeyboardEvent>();
                    keyboardEvent->isPressed = ( sdlEvent.key.type == SDL_KEYDOWN ) ? true : false;
                    keyboardEvent->button = sdlEvent.key.keysym.sym;
                    keyboardEvent->modifiers = sdlEvent.key.keysym.mod;
                    break;
                }

                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                {
                    SMouseButtonEvent *mouseBtnEvent = theEventManager.raiseEvent<SMouseButtonEvent>();
                    mouseBtnEvent->isPressed = ( sdlEvent.button.type == SDL_MOUSEBUTTONDOWN ) ? true : false;
                    mouseBtnEvent->button = sdlEvent.button.button;
                    mouseBtnEvent->clickPos = vec2i( sdlEvent.button.x, sdlEvent.button.y );
                    mouseBtnEvent->clicksNum = sdlEvent.button.clicks;
                    break;
                }

                case SDL_MOUSEWHEEL:
                {
                    // checking for events coming from other devices that produce incorrect data
                    // numbers used here are arbitrary
                    if( sdlEvent.wheel.x < -10000 || sdlEvent.wheel.x > 10000 || sdlEvent.wheel.y < -10000 || sdlEvent.wheel.y > 10000 )
                    {
                        break;
                    }

                    SMouseWheelEvent *mouseWheelEvent = theEventManager.raiseEvent<SMouseWheelEvent>();
                    mouseWheelEvent->scrollAmount = vec2i( sdlEvent.wheel.x, sdlEvent.wheel.y );
                    break;
                }

                case SDL_MOUSEMOTION:
                {
                    // same as with mouse wheel event
                    if( sdlEvent.motion.xrel < -10000 || sdlEvent.motion.xrel > 10000 || sdlEvent.motion.yrel < -10000 || sdlEvent.motion.yrel > 10000 )
                    {
                        break;
                    }

                    SMouseMotionEvent *mouseMotionEvent = theEventManager.raiseEvent<SMouseMotionEvent>();
                    mouseMotionEvent->pos = vec2i( sdlEvent.motion.x, sdlEvent.motion.y );
                    mouseMotionEvent->motion = vec2i( sdlEvent.motion.xrel, sdlEvent.motion.yrel );
                    break;
                }

                case SDL_QUIT:
                {
                    theEventManager.raiseEvent<SQuitRequestEvent>();
                    break;
                }

                default:
                {
                    SMiscSDLEvent *miscEvent = theEventManager.raiseEvent<SMiscSDLEvent>();
                    miscEvent->sdlEvent = sdlEvent;
                }
            }
        }
    }


} // namespace chestnut
