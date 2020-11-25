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

        // if current update is successful and timer reached its interval moment
        bool m_isAlarmOnCurrentUpdate;


        // user defined, constant properties //

        // timer alarm interval in seconds
        const float m_alarmInterval;
        // whether alarm should be raised multiple times
        const bool m_isRepeating;

    public:
        // alarmInterval in seconds
        CIntervalTimer( int id, float alarmInterval, bool isRepeating = false );

        void reset( bool init = false ) override;

        bool update() override;

        bool isAlarmOnCurrentTick();
    };

} // namespace chestnut

#endif // __CHESTNUT_INTERVAL_TIMER_H__