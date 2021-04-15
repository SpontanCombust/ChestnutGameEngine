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
                    SKeyboardEvent *keyboardEvent = new SKeyboardEvent();
                    keyboardEvent->isPressed = ( sdlEvent.key.type == SDL_KEYDOWN ) ? true : false;
                    keyboardEvent->button = sdlEvent.key.keysym.sym;
                    keyboardEvent->modifiers = sdlEvent.key.keysym.mod;
                    theEventManager.raiseEvent( keyboardEvent );
                    break;
                }

                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                {
                    SMouseButtonEvent *mouseBtnEvent = new SMouseButtonEvent();
                    mouseBtnEvent->isPressed = ( sdlEvent.button.type == SDL_MOUSEBUTTONDOWN ) ? true : false;
                    mouseBtnEvent->button = sdlEvent.button.button;
                    mouseBtnEvent->clickPos = Vector2i( sdlEvent.button.x, sdlEvent.button.y );
                    mouseBtnEvent->clicksNum = sdlEvent.button.clicks;
                    theEventManager.raiseEvent( mouseBtnEvent );
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

                    SMouseWheelEvent *mouseWheelEvent = new SMouseWheelEvent();
                    mouseWheelEvent->scrollAmount = Vector2i( sdlEvent.wheel.x, sdlEvent.wheel.y );
                    theEventManager.raiseEvent( mouseWheelEvent );
                    break;
                }

                case SDL_MOUSEMOTION:
                {
                    // same as with mouse wheel event
                    if( sdlEvent.motion.xrel < -10000 || sdlEvent.motion.xrel > 10000 || sdlEvent.motion.yrel < -10000 || sdlEvent.motion.yrel > 10000 )
                    {
                        break;
                    }

                    SMouseMotionEvent *mouseMotionEvent = new SMouseMotionEvent();
                    mouseMotionEvent->pos = Vector2i( sdlEvent.motion.x, sdlEvent.motion.y );
                    mouseMotionEvent->motion = Vector2i( sdlEvent.motion.xrel, sdlEvent.motion.yrel );
                    theEventManager.raiseEvent( mouseMotionEvent );
                    break;
                }

                case SDL_QUIT:
                {
                    SQuitRequestEvent *quitRequestEvent = new SQuitRequestEvent();
                    theEventManager.raiseEvent( quitRequestEvent );
                    break;
                }

                default:
                {
                    SMiscSDLEvent *miscEvent = new SMiscSDLEvent();
                    miscEvent->sdlEvent = sdlEvent;
                    theEventManager.raiseEvent( miscEvent );
                }
            }
        }
    }


} // namespace chestnut
