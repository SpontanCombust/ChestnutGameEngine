#include "misc_tests.hpp"

#include "engine/misc/timers/auto_timer.hpp"
#include "engine/misc/timers/locked_auto_timer.hpp"
#include "engine/misc/timers/manual_timer.hpp"
#include "engine/misc/timers/locked_manual_timer.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
namespace test
{
    void timerTest()
    {
        CAutoTimer autoTimer = CAutoTimer(0);
        CLockedAutoTimer lockedAutoTimer = CLockedAutoTimer(1, 0.1f, true);
        CManualTimer manualTimer = CManualTimer(2);
        CLockedManualTimer lockedManualTimer = CLockedManualTimer(3, 1.f, true);


        LOG_CHANNEL( "TEST", "<<Auto timer test>>" );
        {
            autoTimer.start();
            while( autoTimer.getCurrentTimeInMiliseconds() < 5000 )
            {
                if( autoTimer.tick() )
                {
                    LOG_CHANNEL( "TEST", "Auto timer: " << autoTimer.getCurrentTimeInSeconds() << "; " << autoTimer.getDeltaTime() );
                }
            }
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Locked auto timer test>>" );
        {
            lockedAutoTimer.start();

            while( lockedAutoTimer.getCurrentTimeInMiliseconds() < 5000 )
            {
                if( lockedAutoTimer.tick() )
                {
                    LOG_CHANNEL( "TEST", "Locked auto timer: " << lockedAutoTimer.getCurrentTimeInSeconds() << "; " << lockedAutoTimer.getDeltaTime() );
                }
            }

            lockedAutoTimer.toggleThreadWaitingForTimerInterval( true );

            while( lockedAutoTimer.getCurrentTimeInMiliseconds() < 10000 )
            {
                if( lockedAutoTimer.tick() )
                {
                    LOG_CHANNEL( "TEST", "Locked auto timer: " << lockedAutoTimer.getCurrentTimeInSeconds() << "; " << lockedAutoTimer.getDeltaTime() );
                }
            }
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Manual timer test>>" );
        {
            autoTimer.reset();
            manualTimer.start();

            while( manualTimer.getCurrentTimeInMiliseconds() < 5000 )
            {
                if( autoTimer.tick() )
                {
                    if( manualTimer.tick( autoTimer.getDeltaTime() ) )
                    {
                        LOG_CHANNEL( "TEST", "Manual timer: " << manualTimer.getCurrentTimeInSeconds() << "; " << manualTimer.getDeltaTime() );
                    }
                }
            }
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<<Locked manual timer test>>" );
        {
            autoTimer.reset();
            lockedManualTimer.start();

            while( lockedManualTimer.getCurrentTimeInMiliseconds() < 5000 )
            {
                if( autoTimer.tick() )
                {
                    if( lockedManualTimer.tick( autoTimer.getDeltaTime() ) )
                    {
                        LOG_CHANNEL( "TEST", "Locked manual timer: " << lockedManualTimer.getCurrentTimeInSeconds() << "; " << lockedManualTimer.getDeltaTime() );
                    }
                }
            }
        }
        LOG_CHANNEL( "TEST", "" );
    }

} // namespace test

} // namespace chestnut
