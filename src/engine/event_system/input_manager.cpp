#include "input_manager.hpp"

namespace chestnut
{    
    CInputManager::CInputManager(CEventManager *eventManagerPtr) 
    {
        m_eventManagerPtr = eventManagerPtr;
    }

    void CInputManager::unregisterKeyboardListener( eventListener_id_t id ) 
    {
        m_eventManagerPtr->unregisterListenerByID< SKeyboardEvent >( id );
    }


} // namespace chestnut
