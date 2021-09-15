#ifndef __CHESTNUT_EVENT_MANAGER_H__
#define __CHESTNUT_EVENT_MANAGER_H__

#include "event_listener.hpp"

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace chestnut
{
    class CEventManager
    {
    private:
        std::unordered_map< std::type_index, std::vector< std::weak_ptr<IEventListener> > > m_mapEventTypeToVecListeners;

    public:
        ~CEventManager() = default;


        void registerListener( std::weak_ptr<IEventListener> listener );

        template< typename EventType >
        void raiseEvent( const EventType& event );
    };

} // namespace chestnut


#include "event_manager.tpp"


#endif // __CHESTNUT_EVENT_MANAGER_H__