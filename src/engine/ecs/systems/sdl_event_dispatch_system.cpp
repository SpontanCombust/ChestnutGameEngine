#include "sdl_event_dispatch_system.hpp"

#include "engine/event_system/events/events.hpp"

namespace chestnut
{      
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
                    SKeyboardEvent *keyboardEvent = new SKeyboardEvent();
                    keyboardEvent->isPressed = ( sdlEvent.key.type == SDL_KEYDOWN ) ? true : false;
                    keyboardEvent->button = sdlEvent.key.keysym.sym;
                    keyboardEvent->modifiers = sdlEvent.key.keysym.mod;
                    m_localEventQueue.push( keyboardEvent );
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
                    m_localEventQueue.push( mouseBtnEvent );
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
                    m_localEventQueue.push( mouseWheelEvent );
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
                    m_localEventQueue.push( mouseMotionEvent );
                    break;
                }

                case SDL_QUIT:
                {
                    SQuitRequestEvent *quitRequestEvent = new SQuitRequestEvent();
                    m_localEventQueue.push( quitRequestEvent );
                    break;
                }

                default:
                {
                    SMiscSDLEvent *miscEvent = new SMiscSDLEvent();
                    miscEvent->sdlEvent = sdlEvent;
                    m_localEventQueue.push( miscEvent );
                }
            }
        }
    }


} // namespace chestnut
