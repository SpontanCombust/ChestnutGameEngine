#pragma once


#include "chestnut/engine/macros.hpp"
#include "auto_timer.hpp"

namespace chestnut::engine
{
    /**
     * @brief A timer class which objects get updated (ticked) using std::chrono functionality and tick only in given tick interval.
     * 
     * @details
     * The timer counts time starting from the point of calling start(). To update it call tick().
     * If it returns true, timer time reached the next interval and timer ticked.
     * Timer time here is a multiple of timer interval (until reset() is called).
     * 
     * toggleThreadWaitingForTimerInterval() allows for automatic thread sleeping until the full interval has passed when calling tick()
     */
    class CHESTNUT_API CLockedAutoTimer : public CAutoTimer
    {
    protected:
        // planned next interval tick of the timer
        uint64_t m_nextRelativeTick;


        // user defined, constant properties //

        // desired interval between ticks in seconds
        float m_updateIntervalInSeconds;
        // desired interval between ticks in microseconds
        uint32_t m_updateIntervalInMicroseconds;
        // a flag to tell whether user wants this timer to tick only once or more
        bool m_isRepeating;
        // whether thread should be put to sleep when calling tick() until the interval is reached
        bool m_shouldThreadWaitForTimer;

    public:
        /**
         * @brief Construct a new CLockedAutoTimer object
         * 
         * @param id identifier of the timer
         * @param updateIntervalInSeconds timer's tick interval in seconds
         * @param isRepeating whether timer should tick only once or unlimited times
         */
        CLockedAutoTimer( timerid_t id, float updateIntervalInSeconds, bool isRepeating = false );

        float getUpdateIntervalInSeconds();
        bool getIsRepeating();

        void toggleThreadWaitingForTimerInterval( bool toggle );

        void reset() override;

        /* Returns true if the tick test was successful i.e. if timer
         * was started
         * AND
         * is a repeating timer OR isn't repeating, but there hasn't been a successful tick yet 
         * AND
         * the time since the previous successful tick is equal to or greater than the timer interval
         * 
         * This method is potentially temporarily thread-blocking if ThreadWaitingForTimerInterval is turned on
         */
        bool tick() override;
    };
    
} // namespace chestnut::engine

