#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/misc/timer.hpp"
#include "chestnut/engine/types.hpp"

namespace chestnut::engine
{
    /**
     * @brief A timer class which objects get updated (ticked) using std::chrono functionality
     * 
     * @details
     * The timer counts time starting from the point of calling start(). To update it call tick().
     * If it returns true, the timer ticked.
     * Total timer time here is the sum of all delta times provided (until reset() is called).
     */
    class CHESTNUT_API CAutoTimer : public ITimer
    {
    protected:
        // tick value when timer was started
        uint64_t m_startAbsoluteTick;
        
    public:
        CAutoTimer( timerid_t id );

        void reset() override;

        // Returns true if managed to perform a tick
        // here it's true if timer was started
        virtual bool tick();

    protected:
        uint64_t getAbsoluteTimeInMicroseconds() const;
    };
    
} // namespace chestnut::engine

