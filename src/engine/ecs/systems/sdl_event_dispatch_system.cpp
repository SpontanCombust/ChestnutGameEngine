#include "sdl_event_dispatch_system.hpp"

namespace chestnut
{    
    CSDLEventDispatchSystem::CSDLEventDispatchSystem(CEventManager *eventManagerPtr) 
    {
        m_eventManagerPtr = eventManagerPtr;
    }

    void CSDLEventDispatchSystem::update( float deltaTime ) 
    {
        SDL_Event sdlEvent;

        while( SDL_PollEvent( &sdlEvent ) )
        {
            switch( sdlEvent.type )
            {
                case SDL_KEYDOWN:
                {
                    SKeyboardEvent *keyboardEvent = new SKeyboardEvent();
                    keyboardEvent->isPressed = true;
                    keyboardEvent->keycode = sdlEvent.key.keysym.sym;
                    keyboardEvent->modifiers = sdlEvent.key.keysym.mod;
                    m_eventManagerPtr->raiseEvent( keyboardEvent );
                }
                    break;

                case SDL_KEYUP:
                {
                    SKeyboardEvent *keyboardEvent = new SKeyboardEvent();
                    keyboardEvent->isPressed = false;
                    keyboardEvent->keycode = sdlEvent.key.keysym.sym;
                    keyboardEvent->modifiers = sdlEvent.key.keysym.mod;
                    m_eventManagerPtr->raiseEvent( keyboardEvent );
                }
                    break;

                default:
                {
                    SMiscSDLEvent *miscEvent = new SMiscSDLEvent();
                    miscEvent->sdlEvent = sdlEvent;
                    m_eventManagerPtr->raiseEvent( miscEvent );
                }
            }
        }
    }


} // namespace chestnut
