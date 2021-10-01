#include <catch2/catch.hpp>

#include "../src/chestnut/engine/misc/auto_timer.hpp"
#include "../src/chestnut/engine/misc/locked_auto_timer.hpp"
#include "../src/chestnut/engine/misc/manual_timer.hpp"
#include "../src/chestnut/engine/misc/locked_manual_timer.hpp"

#include <chrono>
#include <thread>


using namespace chestnut::engine;

TEST_CASE( "Auto timer test" )
{
    SECTION( "Default state" )
    {
        CAutoTimer timer = CAutoTimer(1);

        REQUIRE( timer.getID() == 1 );
        REQUIRE( timer.getElapsedTimeInMicroseconds() == 0 );
        REQUIRE( timer.getElapsedTimeInMiliseconds() == 0 );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(0.f).margin(0.001) );
        REQUIRE_FALSE( timer.tick() );
    }

    SECTION( "Single time measure" )
    {
        CAutoTimer timer = CAutoTimer(0);

        timer.start();

        std::this_thread::sleep_for( std::chrono::milliseconds(100) );

        REQUIRE( timer.tick() );
        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(100).margin(1) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.1f).margin(0.1) );
    }

    SECTION( "Multiple ticks before the measure" )
    {
        CAutoTimer timer = CAutoTimer(0);

        timer.start();

        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        REQUIRE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(100) );
        REQUIRE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(200) );
        REQUIRE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(500) );
        REQUIRE( timer.tick() );

        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(850).margin(2) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.85f).margin(0.002) );
        REQUIRE( timer.getDeltaTime() == Approx(0.5f).margin(0.002) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.5f).margin(0.1) );
    }

    SECTION( "Resetting the timer" )
    {
        CAutoTimer timer = CAutoTimer(0);

        timer.start();

        std::this_thread::sleep_for( std::chrono::milliseconds(17) );
        REQUIRE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(17) );
        REQUIRE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(17) );
        REQUIRE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(17) );
        REQUIRE( timer.tick() );

        timer.reset();
        REQUIRE( timer.getElapsedTimeInMiliseconds() == 0 );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == 0 );
        REQUIRE( timer.getUpdatesPerSec() == Approx(0.f).margin(0.001) );

        timer.reset();
        std::this_thread::sleep_for( std::chrono::milliseconds(17) );
        REQUIRE( timer.tick() );
        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(17).margin(1) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.017f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.017f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.017f).margin(0.5) );
    }
}


TEST_CASE( "Locked auto timer test" )
{
    SECTION( "Default state" )
    {
        auto timer = CLockedAutoTimer(1, 1.f);

        REQUIRE( timer.getID() == 1 );
        REQUIRE( timer.getElapsedTimeInMicroseconds() == 0 );
        REQUIRE( timer.getElapsedTimeInMiliseconds() == 0 );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getUpdateIntervalInSeconds() == Approx(1.f).margin(0.001) );
        REQUIRE( timer.getIsRepeating() == false );
        REQUIRE_FALSE( timer.tick() );
    }

    SECTION( "Single time measure without thread waiting" )
    {
        auto timer = CLockedAutoTimer(1, 0.1f);

        timer.start();

        std::this_thread::sleep_for( std::chrono::milliseconds(25) );
        REQUIRE_FALSE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(25) );
        REQUIRE_FALSE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(25) );
        REQUIRE_FALSE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(25) );
        REQUIRE( timer.tick() );

        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(100).margin(1) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.1f).margin(0.1) );
    }

    SECTION( "Multiple time measures with non-repeating timer" )
    {
        auto timer = CLockedAutoTimer(1, 0.1f, false);

        timer.start();

        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        REQUIRE_FALSE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        REQUIRE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        REQUIRE_FALSE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        REQUIRE_FALSE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        REQUIRE_FALSE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        REQUIRE_FALSE( timer.tick() );

        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(100).margin(2) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.1f).margin(0.002) );
        REQUIRE( timer.getDeltaTime() == Approx(0.1f).margin(0.002) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.1f).margin(0.1) );
    }

    SECTION( "Multiple time measures with repeating timer" )
    {
        auto timer = CLockedAutoTimer(1, 0.1f, true);

        timer.start();

        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        REQUIRE_FALSE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        REQUIRE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        REQUIRE_FALSE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        REQUIRE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        REQUIRE_FALSE( timer.tick() );
        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        REQUIRE( timer.tick() );

        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(300).margin(2) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.3f).margin(0.002) );
        REQUIRE( timer.getDeltaTime() == Approx(0.1f).margin(0.002) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.1f).margin(0.1) );
    }

    SECTION( "Single time measure with thread sleeping" )
    {
        auto timer = CLockedAutoTimer(1, 0.1f);

        timer.toggleThreadWaitingForTimerInterval( true );
        timer.start();

        auto start = std::chrono::steady_clock::now();
        REQUIRE( timer.tick() );
        auto end = std::chrono::steady_clock::now();

        REQUIRE( std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() == 100 );

        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(100).margin(1) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.1f).margin(0.1) );
    }

    SECTION( "Multiple time measures with thread sleeping" )
    {
        auto timer = CLockedAutoTimer(1, 0.1f, true);

        timer.toggleThreadWaitingForTimerInterval( true );
        timer.start();

        auto start = std::chrono::steady_clock::now();
        REQUIRE( timer.tick() );
        REQUIRE( timer.tick() );
        REQUIRE( timer.tick() );
        REQUIRE( timer.tick() );
        REQUIRE( timer.tick() );
        auto end = std::chrono::steady_clock::now();

        REQUIRE( std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() == 500 );

        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(500).margin(1) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.5f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.1f).margin(0.1) );
    }

    SECTION( "Resetting the timer" )
    {
        auto timer = CLockedAutoTimer(1, 0.1f, true);

        timer.toggleThreadWaitingForTimerInterval( true );
        timer.start();

        REQUIRE( timer.tick() );
        REQUIRE( timer.tick() );
        REQUIRE( timer.tick() );
        
        timer.reset();
        REQUIRE( timer.getElapsedTimeInMiliseconds() == 0 );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(0.f).margin(0.001) );

        REQUIRE( timer.tick() );
        REQUIRE( timer.tick() );
        REQUIRE( timer.tick() );

        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(300).margin(1) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.3f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.1f).margin(0.1) );
    }
}


TEST_CASE( "Manual timer test" )
{
    SECTION( "Default state" )
    {
        auto timer = CManualTimer(1);

        REQUIRE( timer.getID() == 1 );
        REQUIRE( timer.getElapsedTimeInMicroseconds() == 0 );
        REQUIRE( timer.getElapsedTimeInMiliseconds() == 0 );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(0.f).margin(0.001) );
        REQUIRE_FALSE( timer.tick(0.001f) );
    }

    SECTION( "Single tick" )
    {
        auto timer = CManualTimer(1);

        timer.start();
        REQUIRE( timer.tick(0.001f) );
        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(1) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.001f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.001f).margin(0.0001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.001f).margin(0.1) );
    }

    SECTION( "Multiple ticks" )
    {
        auto timer = CManualTimer(1);

        timer.start();
        REQUIRE( timer.tick(0.01f) );
        REQUIRE( timer.tick(0.01f) );
        REQUIRE( timer.tick(0.01f) );
        REQUIRE( timer.tick(0.02f) );
        REQUIRE( timer.tick(0.02f) );

        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(70) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.07f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.02f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.02f).margin(0.1) );
    }

    SECTION( "Resetting the timer" )
    {
        auto timer = CManualTimer(1);

        timer.start();

        REQUIRE( timer.tick(0.01f) );
        REQUIRE( timer.tick(0.01f) );
        REQUIRE( timer.tick(0.01f) );
        REQUIRE( timer.tick(0.02f) );
        REQUIRE( timer.tick(0.02f) );

        timer.reset();   
        REQUIRE( timer.getElapsedTimeInMiliseconds() == 0 );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(0.f).margin(0.001) );

        REQUIRE( timer.tick(0.01f) );
        REQUIRE( timer.tick(0.01f) );
        REQUIRE( timer.tick(0.01f) );
        REQUIRE( timer.tick(0.02f) );
        REQUIRE( timer.tick(0.02f) );

        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(70) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.07f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.02f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.02f).margin(0.1) );
    }
}


TEST_CASE( "Locked manual timer test" )
{
    SECTION( "Default state" )
    {
        auto timer = CLockedManualTimer(1, 0.1f);

        REQUIRE( timer.getID() == 1 );
        REQUIRE( timer.getIsRepeating() == false );
        REQUIRE( timer.getUpdateIntervalInSeconds() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getElapsedTimeInMicroseconds() == 0 );
        REQUIRE( timer.getElapsedTimeInMiliseconds() == 0 );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(0.f).margin(0.001) );
        REQUIRE_FALSE( timer.tick(0.001f) );
    }

    SECTION( "Single tick" )
    {
        auto timer = CLockedManualTimer(1, 0.1f);

        timer.start();
        REQUIRE_FALSE( timer.tick(0.025f) );
        REQUIRE_FALSE( timer.tick(0.025f) );
        REQUIRE_FALSE( timer.tick(0.025f) );
        REQUIRE( timer.tick(0.025f) );

        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(100).margin(1) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.1f).margin(0.1) );
    }

    SECTION( "Multiple ticks with non-repeating timer" )
    {
        auto timer = CLockedManualTimer(1, 0.1f, false);

        timer.start();
        REQUIRE_FALSE( timer.tick(0.05f) );
        REQUIRE( timer.tick(0.05f) );
        REQUIRE_FALSE( timer.tick(0.05f) );
        REQUIRE_FALSE( timer.tick(0.05f) );
        REQUIRE_FALSE( timer.tick(0.05f) );
        REQUIRE_FALSE( timer.tick(0.05f) );

        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(100).margin(1) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.1f).margin(0.1) );
    }

    SECTION( "Multiple ticks with repeating timer" )
    {
        auto timer = CLockedManualTimer(1, 0.1f, true);

        timer.start();
        REQUIRE_FALSE( timer.tick(0.05f) );
        REQUIRE( timer.tick(0.05f) );
        REQUIRE_FALSE( timer.tick(0.05f) );
        REQUIRE( timer.tick(0.05f) );
        REQUIRE_FALSE( timer.tick(0.05f) );
        REQUIRE( timer.tick(0.05f) );
        REQUIRE_FALSE( timer.tick(0.05f) );

        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(300).margin(1) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.3f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.1f).margin(0.1) );
    }

    SECTION( "Resetting the timer" )
    {
        auto timer = CLockedManualTimer(1, 0.1f, false);

        timer.start();
        REQUIRE_FALSE( timer.tick(0.05f) );
        REQUIRE( timer.tick(0.05f) );

        timer.reset();
        REQUIRE_FALSE( timer.tick(0.05f) );
        REQUIRE( timer.tick(0.05f) );
        REQUIRE_FALSE( timer.tick(0.05f) );
        REQUIRE_FALSE( timer.tick(0.05f) );

        REQUIRE( timer.getElapsedTimeInMiliseconds() == Approx(100).margin(1) );
        REQUIRE( timer.getElapsedTimeInSeconds() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getDeltaTime() == Approx(0.1f).margin(0.001) );
        REQUIRE( timer.getUpdatesPerSec() == Approx(1.f / 0.1f).margin(0.1) );
    }
}