#ifndef __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__
#define __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__

#include "../system_bases/updatable_system.hpp"
#include "../system_bases/event_raising_system.hpp"
#include "engine/event_system/event_manager.hpp"

namespace chestnut
{
    class CSDLEventDispatchSystem : public IUpdatableSystem, public CEventRaisingSystem
    {
    public:
        void update( float deltaTime ) override;   
    };

} // namespace chestnut

#endif // __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__