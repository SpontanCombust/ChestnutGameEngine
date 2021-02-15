#ifndef __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__
#define __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__

#include "event_driven_system.hpp"
#include "engine/event_system/event_manager.hpp"

namespace chestnut
{
    class CSDLEventDispatchSystem : public IEventDrivenSystem
    {
    public:
        bool needsToRaiseEvents() override;
        void raiseEvents( CEventManager& eventManagerRef ) override;
        void update( float deltaTime ) override;   
    };

} // namespace chestnut

#endif // __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__