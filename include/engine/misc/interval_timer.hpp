#ifndef __CHESTNUT_INTERVAL_TIMER_H__
#define __CHESTNUT_INTERVAL_TIMER_H__

#include "timer.hpp"

namespace chestnut
{
    class CIntervalTimer : public CTimer
    {
    private:
        typedef CTimer super;

    protected:
        // inner state vars //

        // tick when last time alarm was activated
        uint32_t m_lastAlarmTick;

        bool m_isAlarmOnCurrentTick;


        // user defined, constant properties //

        // timer alarm interval in seconds
        const float m_alarmInterval;
        // whether alarm should be raised multiple times
        const bool m_isRepeating;

    public:
        // alarmInterval in ms
        CIntervalTimer( int id, float alarmInterval, bool isRepeating = false );

        virtual void reset( bool init = false ) override;

        virtual bool update() override;

        bool isAlarmOnCurrentTick();
    };

} // namespace chestnut

#endif // __CHESTNUT_INTERVAL_TIMER_H__