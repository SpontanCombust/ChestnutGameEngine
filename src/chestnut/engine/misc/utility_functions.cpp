#include "chestnut/engine/misc/utility_functions.hpp"

#include <SDL_messagebox.h>

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>
#else
#include <cstring>
#endif

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





    const char *chestnut::engine::rttiTypeName(const std::type_index &typeIndex)
    {
        const char *name = typeIndex.name();

        // https://stackoverflow.com/questions/281818/unmangling-the-result-of-stdtype-infoname
        #ifdef __GNUG__
            int status = -4; // some arbitrary value to eliminate the compiler warning

            std::unique_ptr<char, void(*)(void*)> res {
                abi::__cxa_demangle(name, NULL, NULL, &status),
                std::free
            };

            if(status == 0)
            {
                name = res.get();
            }
        #else
            // MSVC prefixes these names with "struct" and "class"

            if(strncmp(name, "struct", 6) == 0)
            {
                // move the pointer by 7 chars, past "struct "
                name += 7;
            }
            else if(strncmp(name, "class", 5) == 0)
            {
                // move the pointer by 6 chars, past "class " 
                name += 6;
            }
        #endif
        
        return name;        
    }

    const char *chestnut::engine::rttiTypeName(const std::type_info& typeInfo)
    {
        return rttiTypeName(std::type_index(typeInfo));
    }

} // namespace chestnut::engine
