#ifndef __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__
#define __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__

#include "../system_interfaces/updatable_system.hpp"
#include "../system_interfaces/event_raising_system.hpp"
#include "engine/event_system/event_manager.hpp"

#include <queue>

namespace chestnut
{
    class CSDLEventDispatchSystem : public IUpdatableSystem, public IEventRaisingSystem
    {
    private:
        std::queue< SEvent* > m_localEventQueue;

    public:
        bool needsToRaiseEvents() override;
        void raiseEvents( CEventManager& eventManagerRef ) override;
        void update( float deltaTime ) override;   
    };

} // namespace chestnut

#endif // __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__