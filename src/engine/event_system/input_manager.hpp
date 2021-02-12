#ifndef __CHESTNUT_INPUT_MANAGER_H__
#define __CHESTNUT_INPUT_MANAGER_H__

#include "engine/event_system/event_manager.hpp"
#include "engine/event_system/events/keyboard_event.hpp"

namespace chestnut
{
    class CInputManager
    {
    private:
        CEventManager *m_eventManagerPtr;

    public:
        CInputManager( CEventManager *eventManagerPtr );

        template< class T >
        eventListener_id_t registerKeyboardListener( T *objPtr, event_function ( T::*membFunc )( const SKeyboardEvent& ), SDL_Keycode key, uint16_t modifiers = KMOD_NONE );

        void unregisterKeyboardListener( eventListener_id_t id );
    };

    template< class T >
    eventListener_id_t CInputManager::registerKeyboardListener( T *objPtr, event_function ( T::*membFunc )( const SKeyboardEvent& ), SDL_Keycode key, uint16_t modifiers ) 
    {
        eventListener_id_t id;

        id = m_eventManagerPtr->registerListener( objPtr, membFunc );

        m_eventManagerPtr->constrainListenerByID<SKeyboardEvent>( id,

            [=]( const SKeyboardEvent& event ) -> bool
            {
                if( modifiers != KMOD_NONE )
                {
                    return event.keycode == key && event.modifiers == modifiers;
                }
                else
                {
                    return event.keycode == key;
                }
            }

        );

        return id;
    }
    

} // namespace chestnut

#endif // __CHESTNUT_INPUT_MANAGER_H__