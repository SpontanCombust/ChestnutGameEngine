#include <catch2/catch.hpp>

#include "../src/engine/main/window.hpp"

#include <SDL2/SDL_video.h>


// minimalistic setup for interactive tests using the messagebox functionality supplied by SDL2

static const SDL_MessageBoxButtonData runTestButtons[] =
{
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Run!" }
};

const char YES = 0; 
const char NO  = 1; 
static const SDL_MessageBoxButtonData confirmTestButtons[] =
{
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, YES, "Yes" },
    { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, NO, "No" }
};

void showRunTestMessageBox( const char *testTitle, const char *testMessage )
{
    SDL_MessageBoxData data;
    data.flags          = SDL_MESSAGEBOX_INFORMATION;
    data.window         = nullptr;
    data.title          = testTitle;
    data.message        = testMessage;
    data.numbuttons     = SDL_arraysize( runTestButtons );
    data.buttons        = runTestButtons;
    data.colorScheme    = nullptr;
    
    int btn;
    SDL_ShowMessageBox( &data, &btn );
}

bool showConfirmTestMessageBox( const char *testTitle )
{
    SDL_MessageBoxData data;
    data.flags          = SDL_MESSAGEBOX_INFORMATION;
    data.window         = nullptr;
    data.title          = testTitle;
    data.message        = "Did it work?";
    data.numbuttons     = SDL_arraysize( confirmTestButtons );
    data.buttons        = confirmTestButtons;
    data.colorScheme    = nullptr;

    int btn;
    if( SDL_ShowMessageBox( &data, &btn ) < 0)
    {
        return false;
    }

    return btn == YES;
}


// Making these seperate cases, because I want to launch these tests seperately one-by-one and actually see the results //

using namespace chestnut;

TEST_CASE( "Window test - Default state" )
{
    auto window = createWindow( SWindowProperties( 3, 1 ), "Window test - Default state", 800, 600, 500, 400 );

    REQUIRE( window );
    REQUIRE( window->getTitle() == "Window test - Default state" );
    REQUIRE( window->getDisplayMode() == EWindowDisplayMode::WINDOWED );
    REQUIRE( window->getSizeWidth() == 800 );
    REQUIRE( window->getSizeHeight() == 600 );
    REQUIRE( window->getPositionX() == 500 );
    REQUIRE( window->getPositionY() == 400 );
    REQUIRE( window->isResizable() == false );
}

TEST_CASE( "Window test - Changing title", "[interactive]" )
{
    std::string windowTitle = "Window test - Changing title";
    std::string newWindowTitle = "Window test - this is the other title";

    auto window = createWindow( SWindowProperties( 3, 1 ), windowTitle );

    showRunTestMessageBox( windowTitle.c_str(), "Click to change the title of the window" );

    window->setTitle( newWindowTitle ); 
    REQUIRE( window->getTitle() == newWindowTitle );

    REQUIRE( showConfirmTestMessageBox( windowTitle.c_str() ) );
}

TEST_CASE( "Window test - changing display mode", "[interactive]" )
{
    const char *testName = "Window test - changing display mode";
    auto window = createWindow( SWindowProperties( 3, 1 ), testName );


    SECTION( "Windowed to windowed-borderless" )
    {
        showRunTestMessageBox( testName, "Click to change display type from windowed to windowed-borderless" );

        window->setDisplayMode( EWindowDisplayMode::WINDOWED_BORDLERLESS );
        REQUIRE( window->getDisplayMode() == EWindowDisplayMode::WINDOWED_BORDLERLESS );
        
        REQUIRE( showConfirmTestMessageBox( testName ) );
    }
    
    SECTION( "Windowed-borderless to fullscreen" )
    {
        showRunTestMessageBox( testName, "Click to change display type from windowed to fullscreen" );    

        window->setDisplayMode( EWindowDisplayMode::FULLSCREEN );
        REQUIRE( window->getDisplayMode() == EWindowDisplayMode::FULLSCREEN );

        REQUIRE( showConfirmTestMessageBox( testName ) );
    }

    SECTION( "windowed-borderless to windowed" )
    {
        window->setDisplayMode( EWindowDisplayMode::WINDOWED_BORDLERLESS );
        showRunTestMessageBox( testName, "Click to change display type from windowed-borderless to windowed" );    

        window->setDisplayMode( EWindowDisplayMode::WINDOWED );
        REQUIRE( window->getDisplayMode() == EWindowDisplayMode::WINDOWED );

        REQUIRE( showConfirmTestMessageBox( testName ) );    
    }
}

TEST_CASE( "Window test - changing resizable", "[interactive]" )
{
    const char *testName = "Window test - changing resizable";
    auto window = createWindow( SWindowProperties( 3, 1 ), testName );

    showRunTestMessageBox( testName, "Click to make the window resizable" );

    window->setResizable(true);
    REQUIRE( window->isResizable() );

    REQUIRE( showConfirmTestMessageBox( testName ) );
}

TEST_CASE( "Window test - changing window size", "[interactive]" )
{
    const char *testName = "Window test - changing window size";
    auto window = createWindow( SWindowProperties( 3, 1 ), testName );

    showRunTestMessageBox( testName, "Click to make the window 2 times smaller" );

    int w = window->getSizeWidth();
    int h = window->getSizeHeight();
    
    window->setSize( w / 2, h / 2 );
    REQUIRE( window->getSizeWidth() == w / 2 );
    REQUIRE( window->getSizeHeight() == h / 2 );

    REQUIRE( showConfirmTestMessageBox( testName ) );
}

TEST_CASE( "Window test - changing window posititon", "[interactive]" )
{
    const char *testName = "Window test - changing window position";
    auto window = createWindow( SWindowProperties( 3, 1 ), testName );

    showRunTestMessageBox( testName, "Click to move the window upper left corner" );
    
    window->setPosition( 0, 0 );
    REQUIRE( window->getPositionX() == 0 );
    REQUIRE( window->getPositionY() == 0 );

    showConfirmTestMessageBox( testName );
}