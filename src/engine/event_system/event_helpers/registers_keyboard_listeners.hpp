#ifndef __CHESTNUT_REGISTERS_KEYBOARD_EVENTS_H__
#define __CHESTNUT_REGISTERS_KEYBOARD_EVENTS_H__

#include "../event_manager.hpp"
#include "event_constraint_functor_creators.hpp"
#include "engine/misc/tindex.hpp"

#include <unordered_map>
#include <vector>

namespace chestnut
{
    class CRegistersKeyboardListeners
    {
    private:
        CEventManager& m_eventManagerRef;
        std::vector< listenerid_t > m_vecListeners;

    public:
        CRegistersKeyboardListeners( CEventManager& eventManager );

    protected:
        template< class T >
        listenerid_t registerKeyboardListener( event_function ( T::*membFunc )( const SKeyboardEvent& ),
                                               SDL_Keycode button, 
                                               bool checkIfPressedDown = true, 
                                               bool shouldBePressedDown = true, 
                                               bool checkModifiers = false, 
                                               uint16_t modifiers = KMOD_NONE );

        void unregisterKeyboardListener( listenerid_t id );

        virtual ~CRegistersKeyboardListeners();
    };
    
} // namespace chestnut


#include "registers_keyboard_listeners.tpp"


#endif // __CHESTNUT_REGISTERS_KEYBOARD_EVENTS_H__