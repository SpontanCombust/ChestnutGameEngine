#ifndef __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__
#define __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__

#include "../system.hpp"

namespace chestnut
{
    class CSDLEventDispatchSystem : public ISystem
    {
    public:
        CSDLEventDispatchSystem( CEngine& engine );

        void update( uint32_t deltaTime ) override;   
    };

} // namespace chestnut

#endif // __CHESTNUT_SDL_EVENT_DISPATCH_SYSTEM_H__