#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"

using namespace chestnut::engine;

TEST_CASE( "Window - Creating without initializing libraries" )
{
    CWindow window( "Window test - this window should not be created" );
    REQUIRE_FALSE( window.isValid() );
}

TEST_CASE( "Window - Default state" )
{
    REQUIRE( chestnutInit() );
    CWindow window( "Window test - Default state", 800, 600, EWindowDisplayMode::WINDOWED, 500, 400 );

    REQUIRE( window.isValid() );
    REQUIRE( window.getTitle() == "Window test - Default state" );
    REQUIRE( window.getDisplayMode() == EWindowDisplayMode::WINDOWED );
    REQUIRE( window.getSizeWidth() == 800 );
    REQUIRE( window.getSizeHeight() == 600 );
    REQUIRE( window.getPositionX() == 500 );
    REQUIRE( window.getPositionY() == 400 );
    REQUIRE( window.isResizable() == false );
    REQUIRE( window.isMinimized() == false );
    REQUIRE( window.isMaximized() == false );
    REQUIRE( window.isShown() == true );
    REQUIRE( window.isHidden() == false );

    chestnutQuit();
}

TEST_CASE( "Window - Changing title", "[interactive]" )
{
    std::string windowTitle = "Window test - Changing title";
    std::string newWindowTitle = "Window test - this is the other title";

    chestnutInit();
    CWindow window( windowTitle );

    showInfoMessageBox( windowTitle.c_str(), "Click to change the title of the window" );

    window.setTitle( newWindowTitle ); 
    REQUIRE( window.getTitle() == newWindowTitle );

    REQUIRE( showConfirmMessageBox( windowTitle.c_str() ) );

    chestnutQuit();
}

TEST_CASE( "Window - Changing display mode", "[interactive]" )
{
    const char *testName = "Window test - changing display mode";

    chestnutInit();

    SECTION( "Windowed to windowed-borderless" )
    {
        CWindow window( testName, 800, 600, EWindowDisplayMode::WINDOWED );

        showInfoMessageBox( testName, "Click to change display type from windowed to windowed-borderless" );

        window.setDisplayMode( EWindowDisplayMode::WINDOWED_BORDLERLESS );
        REQUIRE( window.getDisplayMode() == EWindowDisplayMode::WINDOWED_BORDLERLESS );
        
        REQUIRE( showConfirmMessageBox( testName ) );   
    }

    SECTION( "Windowed-borderless to fullscreen" )
    {
        CWindow window( testName, 800, 600, EWindowDisplayMode::WINDOWED_BORDLERLESS );

        showInfoMessageBox( testName, "Click to change display type from windowed-borderless to fullscreen" );    

        window.setDisplayMode( EWindowDisplayMode::FULLSCREEN );
        REQUIRE( window.getDisplayMode() == EWindowDisplayMode::FULLSCREEN );

        REQUIRE( showConfirmMessageBox( testName ) );
    }

    SECTION( "Fullscreen to windowed" )
    {
        CWindow window( testName, 800, 600, EWindowDisplayMode::FULLSCREEN );

        showInfoMessageBox( testName, "Click to change display type from fullscreen to windowed" );    

        window.setDisplayMode( EWindowDisplayMode::WINDOWED );
        REQUIRE( window.getDisplayMode() == EWindowDisplayMode::WINDOWED );

        REQUIRE( showConfirmMessageBox( testName ) );   
    }

    chestnutQuit();
    sleepFor(1000);
}

TEST_CASE( "Window - Changing resizable", "[interactive]" )
{
    const char *testName = "Window test - changing resizable";

    chestnutInit();
    CWindow window( testName );

    showInfoMessageBox( testName, "Click to make the window resizable" );

    window.setResizable(true);
    REQUIRE( window.isResizable() );

    REQUIRE( showConfirmMessageBox( testName ) );

    chestnutQuit();
}

TEST_CASE( "Window - Changing window size", "[interactive]" )
{
    const char *testName = "Window test - changing window size";

    chestnutInit();
    CWindow window( testName );

    showInfoMessageBox( testName, "Click to make the window 2 times smaller" );

    int w = window.getSizeWidth();
    int h = window.getSizeHeight();
    
    window.setSize( w / 2, h / 2 );
    REQUIRE( window.getSizeWidth() == w / 2 );
    REQUIRE( window.getSizeHeight() == h / 2 );

    REQUIRE( showConfirmMessageBox( testName ) );

    chestnutQuit();
}

TEST_CASE( "Window - Changing window posititon", "[interactive]" )
{
    const char *testName = "Window test - changing window position";

    chestnutInit();
    CWindow window( testName );

    showInfoMessageBox( testName, "Click to move the window upper left corner" );
    
    window.setPosition( 0, 0 );
    REQUIRE( window.getPositionX() == 0 );
    REQUIRE( window.getPositionY() == 0 );

    REQUIRE( showConfirmMessageBox( testName ) );

    chestnutQuit();
}

TEST_CASE( "Window - Minimizing and maximizing the window", "[interactive]" )
{
    const char *testName = "Window test - minimizing and maximizing the window";

    chestnutInit();   

    SECTION( "Minimizing" )
    {
        CWindow window( testName );

        showInfoMessageBox( testName, "Click to minimize the window" );
        window.minimize();

        REQUIRE( showConfirmMessageBox( testName ) );
        REQUIRE( window.isMinimized() ); //FIXME Seems not to be working on Ubuntu 20.04
    }

    SECTION( "Restoring from minimized" )
    {
        CWindow window( testName );

        window.minimize();

        showInfoMessageBox( testName, "Click to restore window from minimized state" );

        window.restore();

        REQUIRE( showConfirmMessageBox( testName ) ); //FIXME Seems not to be working on Ubuntu 20.04
        REQUIRE_FALSE( window.isMinimized() );
    }

    SECTION( "Maximizing" )
    {
        CWindow window( testName );
        window.setResizable(true);

        showInfoMessageBox( testName, "Click to maximize the window" );

        window.maximize();

        REQUIRE( showConfirmMessageBox( testName ) );
        REQUIRE( window.isMaximized() );
    }

    SECTION( "Restoring from maximized" )
    {
        CWindow window( testName );

        window.setResizable(true);
        window.maximize();

        showInfoMessageBox( testName, "Click to restore window from maximized state" );

        window.restore();

        REQUIRE( showConfirmMessageBox( testName ) );
        REQUIRE_FALSE( window.isMaximized() );
    }

    chestnutQuit();
    sleepFor(1000);
}

TEST_CASE( "Window - Hiding and showing the window", "[interactive]" )
{
    const char *testName = "Window test - hiding and showing the window";

    chestnutInit();

    SECTION( "Hiding" )
    {
        CWindow window( testName, 800, 600, EWindowDisplayMode::WINDOWED, -1, -1, true );

        showInfoMessageBox( testName, "Click to hide the window" );

        window.hide();

        REQUIRE_FALSE( window.isShown() );
        REQUIRE( window.isHidden() );
        REQUIRE( showConfirmMessageBox( testName ) );
    }

    SECTION( "Showing" )
    {
        CWindow window( testName, 800, 600, EWindowDisplayMode::WINDOWED, -1, -1, false );

        showInfoMessageBox( testName, "Click to show the window" );

        window.show();

        REQUIRE( window.isShown() );
        REQUIRE_FALSE( window.isHidden() );
        REQUIRE( showConfirmMessageBox( testName ) );
    }

    chestnutQuit();
    sleepFor(1000);
}