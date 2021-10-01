#include <catch2/catch.hpp>

#include "test_utils.hpp"

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/main/window.hpp"

using namespace chestnut::engine;

TEST_CASE( "Window test - creating without initializing libraries" )
{
    REQUIRE_FALSE( createWindow( "Window test - this window should not be created" ) );
}

TEST_CASE( "Window test - default state" )
{
    REQUIRE( chestnutInit() );
    auto window = createWindow( "Window test - Default state", 800, 600, EWindowDisplayMode::WINDOWED, 500, 400 );

    REQUIRE( window );
    REQUIRE( window->getTitle() == "Window test - Default state" );
    REQUIRE( window->getDisplayMode() == EWindowDisplayMode::WINDOWED );
    REQUIRE( window->getSizeWidth() == 800 );
    REQUIRE( window->getSizeHeight() == 600 );
    REQUIRE( window->getPositionX() == 500 );
    REQUIRE( window->getPositionY() == 400 );
    REQUIRE( window->isResizable() == false );
    REQUIRE( window->isMinimized() == false );
    REQUIRE( window->isMaximized() == false );
    REQUIRE( window->isShown() == true );
    REQUIRE( window->isHidden() == false );

    chestnutQuit();
}

TEST_CASE( "Window test - changing title", "[interactive]" )
{
    std::string windowTitle = "Window test - Changing title";
    std::string newWindowTitle = "Window test - this is the other title";

    chestnutInit();
    auto window = createWindow( windowTitle );

    showRunTestMessageBox( windowTitle.c_str(), "Click to change the title of the window" );

    window->setTitle( newWindowTitle ); 
    REQUIRE( window->getTitle() == newWindowTitle );

    REQUIRE( showConfirmTestMessageBox( windowTitle.c_str() ) );

    chestnutQuit();
}

TEST_CASE( "Window test - changing display mode", "[interactive]" )
{
    const char *testName = "Window test - changing display mode";

    chestnutInit();

    SECTION( "Windowed to windowed-borderless" )
    {
        auto window = createWindow( testName, 800, 600, EWindowDisplayMode::WINDOWED );

        showRunTestMessageBox( testName, "Click to change display type from windowed to windowed-borderless" );

        window->setDisplayMode( EWindowDisplayMode::WINDOWED_BORDLERLESS );
        REQUIRE( window->getDisplayMode() == EWindowDisplayMode::WINDOWED_BORDLERLESS );
        
        REQUIRE( showConfirmTestMessageBox( testName ) );   
    }

    SECTION( "Windowed-borderless to fullscreen" )
    {
        auto window = createWindow( testName, 800, 600, EWindowDisplayMode::WINDOWED_BORDLERLESS );

        showRunTestMessageBox( testName, "Click to change display type from windowed-borderless to fullscreen" );    

        window->setDisplayMode( EWindowDisplayMode::FULLSCREEN );
        REQUIRE( window->getDisplayMode() == EWindowDisplayMode::FULLSCREEN );

        REQUIRE( showConfirmTestMessageBox( testName ) );
    }

    SECTION( "Fullscreen to windowed" )
    {
        auto window = createWindow( testName, 800, 600, EWindowDisplayMode::FULLSCREEN );

        showRunTestMessageBox( testName, "Click to change display type from fullscreen to windowed" );    

        window->setDisplayMode( EWindowDisplayMode::WINDOWED );
        REQUIRE( window->getDisplayMode() == EWindowDisplayMode::WINDOWED );

        REQUIRE( showConfirmTestMessageBox( testName ) );   
    }

    chestnutQuit();
    sleepFor(1000);
}

TEST_CASE( "Window test - changing resizable", "[interactive]" )
{
    const char *testName = "Window test - changing resizable";

    chestnutInit();
    auto window = createWindow( testName );

    showRunTestMessageBox( testName, "Click to make the window resizable" );

    window->setResizable(true);
    REQUIRE( window->isResizable() );

    REQUIRE( showConfirmTestMessageBox( testName ) );

    chestnutQuit();
}

TEST_CASE( "Window test - changing window size", "[interactive]" )
{
    const char *testName = "Window test - changing window size";

    chestnutInit();
    auto window = createWindow( testName );

    showRunTestMessageBox( testName, "Click to make the window 2 times smaller" );

    int w = window->getSizeWidth();
    int h = window->getSizeHeight();
    
    window->setSize( w / 2, h / 2 );
    REQUIRE( window->getSizeWidth() == w / 2 );
    REQUIRE( window->getSizeHeight() == h / 2 );

    REQUIRE( showConfirmTestMessageBox( testName ) );

    chestnutQuit();
}

TEST_CASE( "Window test - changing window posititon", "[interactive]" )
{
    const char *testName = "Window test - changing window position";

    chestnutInit();
    auto window = createWindow( testName );

    showRunTestMessageBox( testName, "Click to move the window upper left corner" );
    
    window->setPosition( 0, 0 );
    REQUIRE( window->getPositionX() == 0 );
    REQUIRE( window->getPositionY() == 0 );

    REQUIRE( showConfirmTestMessageBox( testName ) );

    chestnutQuit();
}

TEST_CASE( "Window test - minimizing and maximizing the window", "[interactive]" )
{
    const char *testName = "Window test - minimizing and maximizing the window";

    chestnutInit();   

    SECTION( "Minimizing" )
    {
        auto window = createWindow( testName );

        showRunTestMessageBox( testName, "Click to minimize the window" );
        window->minimize();

        REQUIRE( showConfirmTestMessageBox( testName ) );
        REQUIRE( window->isMinimized() ); //FIXME Seems not to be working on Ubuntu 20.04
    }

    SECTION( "Restoring from minimized" )
    {
        auto window = createWindow( testName );

        window->minimize();

        showRunTestMessageBox( testName, "Click to restore window from minimized state" );

        window->restore();

        REQUIRE( showConfirmTestMessageBox( testName ) ); //FIXME Seems not to be working on Ubuntu 20.04
        REQUIRE_FALSE( window->isMinimized() );
    }

    SECTION( "Maximizing" )
    {
        auto window = createWindow( testName );
        window->setResizable(true);

        showRunTestMessageBox( testName, "Click to maximize the window" );

        window->maximize();

        REQUIRE( showConfirmTestMessageBox( testName ) );
        REQUIRE( window->isMaximized() );
    }

    SECTION( "Restoring from maximized" )
    {
        auto window = createWindow( testName );

        window->setResizable(true);
        window->maximize();

        showRunTestMessageBox( testName, "Click to restore window from maximized state" );

        window->restore();

        REQUIRE( showConfirmTestMessageBox( testName ) );
        REQUIRE_FALSE( window->isMaximized() );
    }

    chestnutQuit();
    sleepFor(1000);
}

TEST_CASE( "Window test - hiding and showing the window", "[interactive]" )
{
    const char *testName = "Window test - hiding and showing the window";

    chestnutInit();

    SECTION( "Hiding" )
    {
        auto window = createWindow( testName, 800, 600, EWindowDisplayMode::WINDOWED, -1, -1, true );

        showRunTestMessageBox( testName, "Click to hide the window" );

        window->hide();

        REQUIRE_FALSE( window->isShown() );
        REQUIRE( window->isHidden() );
        REQUIRE( showConfirmTestMessageBox( testName ) );
    }

    SECTION( "Showing" )
    {
        auto window = createWindow( testName, 800, 600, EWindowDisplayMode::WINDOWED, -1, -1, false );

        showRunTestMessageBox( testName, "Click to show the window" );

        window->show();

        REQUIRE( window->isShown() );
        REQUIRE_FALSE( window->isHidden() );
        REQUIRE( showConfirmTestMessageBox( testName ) );
    }

    chestnutQuit();
    sleepFor(1000);
}