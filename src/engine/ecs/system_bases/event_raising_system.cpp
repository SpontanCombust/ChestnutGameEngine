#include "event_raising_system.hpp"

namespace chestnut
{    
    bool CEventRaisingSystem::needsToRaiseEvents() 
    {
        return !m_localEventQueue.empty();
    }

    void CEventRaisingSystem::raiseEvents( CEventManager& eventManagerRef ) 
    {
        SEvent *event;
        while( !m_localEventQueue.empty() )
        {
            event = m_localEventQueue.front();
            m_localEventQueue.pop();
            eventManagerRef.raiseEvent( event );
        }
    }

} // namespace chestnut
