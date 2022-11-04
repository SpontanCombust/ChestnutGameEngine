#pragma once


#include <SDL_messagebox.h>

#include <thread>


// minimalistic setup for interactive tests using the messagebox functionality supplied by SDL2

static const SDL_MessageBoxButtonData runTestButtons[] =
{
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Continue" }
};

static const SDL_MessageBoxButtonData confirmTestButtons[] =
{
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Yes" },
    { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "No" }
};

// Shows a message box informing a tester of what should happen when they hit "Run!"
inline void showInfoMessageBox( const char *testTitle, const char *testMessage )
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

// Shows a message box about test passing confirmation. Returns tester's verdict on whether test passed.
inline bool showConfirmMessageBox( const char *testTitle )
{
    SDL_MessageBoxData data;
    data.flags          = SDL_MESSAGEBOX_INFORMATION;
    data.window         = nullptr;
    data.title          = testTitle;
    data.message        = "Did it work properly?";
    data.numbuttons     = SDL_arraysize( confirmTestButtons );
    data.buttons        = confirmTestButtons;
    data.colorScheme    = nullptr;

    int btn;
    if( SDL_ShowMessageBox( &data, &btn ) < 0)
    {
        return false;
    }

    return btn == 0; // YES
}

inline void sleepFor( unsigned int miliseconds )
{
    std::this_thread::sleep_for( std::chrono::milliseconds(miliseconds) );
}

