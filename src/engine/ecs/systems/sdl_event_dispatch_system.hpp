#ifndef __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__
#define __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__

#include "../system.hpp"
#include "engine/event_system/event_manager.hpp"
#include "engine/event_system/events/keyboard_event.hpp"
#include "engine/event_system/events/misc_sdl_event.hpp"

namespace chestnut
{
    class CSDLEventDispatchSystem : public ISystem
    {
    private:
        CEventManager *m_eventManagerPtr;

    public:
        CSDLEventDispatchSystem( CEventManager *eventManagerPtr );
        void update( float deltaTime ) override;   
    };

} // namespace chestnut

#endif // __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__