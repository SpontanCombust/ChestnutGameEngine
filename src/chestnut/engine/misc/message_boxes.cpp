#include "chestnut/engine/misc/message_boxes.hpp"

#include <SDL_messagebox.h>

namespace chestnut::engine
{
    void messageBoxInfo(const std::string& message, const char *title)
    {
        static const SDL_MessageBoxButtonData buttons[] =
        {
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "OK" }
        };

        SDL_MessageBoxData data;
        data.flags          = SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR;
        data.window         = nullptr;
        data.title          = title;
        data.message        = message.c_str();
        data.numbuttons     = SDL_arraysize(buttons);
        data.buttons        = buttons;
        data.colorScheme    = nullptr;
        
        int btn;
        SDL_ShowMessageBox( &data, &btn );
    }

    bool messageBoxYesNo(const std::string& message, const char *title)
    {
        static const SDL_MessageBoxButtonData buttons[] =
        {
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Yes" },
            { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "No" }
        };

        SDL_MessageBoxData data;
        data.flags          = SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR;
        data.window         = nullptr;
        data.title          = "Error";
        data.message        = message.c_str();
        data.numbuttons     = SDL_arraysize(buttons);
        data.buttons        = buttons;
        data.colorScheme    = nullptr;
        
        int btn;
        SDL_ShowMessageBox( &data, &btn );

        return btn == 0;
    }

} // namespace chestnut::engine
