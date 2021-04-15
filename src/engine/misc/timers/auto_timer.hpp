#ifndef __CHESTNUT_AUTO_TIMER_H__
#define __CHESTNUT_AUTO_TIMER_H__

#include "timer.hpp"
#include "engine/types.hpp"

#include <SDL2/SDL_timer.h>

namespace chestnut
{
    /**
     * @brief A timer class which objects get updated (ticked) using SDL timer functionality
     * 
     * @details
     * The timer counts time starting from the point of calling start(). To update it call tick().
     * If it returns true, the timer ticked.
     * Total timer time here is the sum of all delta times provided (until reset() is called).
     */
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