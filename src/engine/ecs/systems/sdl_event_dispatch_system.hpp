#ifndef __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__
#define __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__

#include "../system.hpp"
#include "../../event_system/event_manager.hpp"

namespace chestnut
{
    class CSDLEventDispatchSystem : public ISystem
    {
    public:
        void update( uint32_t deltaTime ) override;   
    };

} // namespace chestnut

#endif // __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__