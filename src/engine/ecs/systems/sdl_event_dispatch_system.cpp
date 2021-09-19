#include "sdl_event_dispatch_system.hpp"

#include "../events/keyboard_event.hpp"
#include "../events/mouse_button_event.hpp"
#include "../events/mouse_wheel_event.hpp"
#include "../events/mouse_motion_event.hpp"
#include "../events/quit_request_event.hpp"
#include "../events/misc_sdl_event.hpp"

namespace chestnut
{      
    CSDLEventDispatchSystem::CSDLEventDispatchSystem( CEngine& engine ) : ISystem( engine )
    {

    }

    void CSDLEventDispatchSystem::update( float deltaTime ) 
    {
        SDL_Event sdlEvent;

        while( SDL_PollEvent( &sdlEvent ) )
        {
            switch( sdlEvent.type )
            {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                {
                    SKeyboardEvent keyboardEvent;
                    keyboardEvent.isPressed = ( sdlEvent.key.type == SDL_KEYDOWN ) ? true : false;
                    keyboardEvent.button = sdlEvent.key.keysym.sym;
                    keyboardEvent.modifiers = sdlEvent.key.keysym.mod;
                    getEngine().getEventManager().raiseEvent( keyboardEvent );
                    break;
                }

                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                {
                    SMouseButtonEvent mouseBtnEvent;
                    mouseBtnEvent.isPressed = ( sdlEvent.button.type == SDL_MOUSEBUTTONDOWN ) ? true : false;
                    mouseBtnEvent.button = sdlEvent.button.button;
                    mouseBtnEvent.clickPos = vec2i( sdlEvent.button.x, sdlEvent.button.y );
                    mouseBtnEvent.clicksNum = sdlEvent.button.clicks;
                    getEngine().getEventManager().raiseEvent( mouseBtnEvent );
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

                    SMouseWheelEvent mouseWheelEvent;
                    mouseWheelEvent.scrollAmount = vec2i( sdlEvent.wheel.x, sdlEvent.wheel.y );
                    getEngine().getEventManager().raiseEvent( mouseWheelEvent );
                    break;
                }

                case SDL_MOUSEMOTION:
                {
                    // same as with mouse wheel event
                    if( sdlEvent.motion.xrel < -10000 || sdlEvent.motion.xrel > 10000 || sdlEvent.motion.yrel < -10000 || sdlEvent.motion.yrel > 10000 )
                    {
                        break;
                    }

                    SMouseMotionEvent mouseMotionEvent;
                    mouseMotionEvent.pos = vec2i( sdlEvent.motion.x, sdlEvent.motion.y );
                    mouseMotionEvent.motion = vec2i( sdlEvent.motion.xrel, sdlEvent.motion.yrel );
                    getEngine().getEventManager().raiseEvent( mouseMotionEvent );
                    break;
                }

                case SDL_QUIT:
                {
                    getEngine().getEventManager().raiseEvent( SQuitRequestEvent() );
                    break;
                }

                default:
                {
                    SMiscSDLEvent miscEvent;
                    miscEvent.sdlEvent = sdlEvent;
                    getEngine().getEventManager().raiseEvent( miscEvent );
                }
            }
        }
    }


} // namespace chestnut
