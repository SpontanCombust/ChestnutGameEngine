#include "registers_keyboard_listeners.hpp"

namespace chestnut
{
    CRegistersKeyboardListeners::CRegistersKeyboardListeners( CEventManager& eventManager )
    : m_eventManagerRef( eventManager )
    {

    }
    
    CRegistersKeyboardListeners::~CRegistersKeyboardListeners() 
    {
        for( listenerid_t& id : m_vecListeners )
        {
            m_eventManagerRef.unregisterListenerByID<SKeyboardEvent>( id );
        }
        m_vecListeners.clear();
    }

    void CRegistersKeyboardListeners::unregisterKeyboardListener( listenerid_t id )
    {
        auto it = std::find( m_vecListeners.begin(), m_vecListeners.end(), id );
        if( it != m_vecListeners.end() )
        {
            m_vecListeners.erase( it );
            m_eventManagerRef.unregisterListenerByID<SKeyboardEvent>( id );
        }
    }

} // namespace chestnut
