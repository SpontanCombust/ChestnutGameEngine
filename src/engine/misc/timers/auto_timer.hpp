#ifndef __CHESTNUT_AUTO_TIMER_H__
#define __CHESTNUT_AUTO_TIMER_H__

#include "timer.hpp"
#include "engine/types.hpp"

#include <SDL2/SDL_timer.h>

namespace chestnut
{
    // Timer which gets updated using SDL timer functionality
    class CAutoTimer : public ITimer
    {
    protected:
        // tick value when timer was started
        uint32_t m_startTick;
        
    public:
        CAutoTimer( timerid_t id );

        void reset( bool init = false ) override;

        // Returns true if managed to perform a tick (here: if timer was started)
        virtual bool tick();
    };
    
} // namespace chestnut

#endif // __CHESTNUT_AUTO_TIMER_H__