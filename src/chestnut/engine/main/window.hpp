#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/graphics/opengl/framebuffer.hpp"

#include <string>

struct SDL_Window;
typedef void * SDL_GLContext;

namespace chestnut::engine
{
    enum class EWindowDisplayMode
    {
        WINDOWED,
        WINDOWED_BORDLERLESS,
        FULLSCREEN
    };

    class CHESTNUT_API CWindow
    {
    private:
        SDL_Window *m_sdlWindow;
        SDL_GLContext m_sdlGLContext;
        CFramebuffer *m_framebuffer; // for now just a dummy with no texture bound

    public:
        // Make sure to call chestnutInit() before creating a window
        // To configure more aspects of how OpenGL will behave use SDL_GL_SetAttribute() after chestnutInit()
        // See https://wiki.libsdl.org/SDL_GL_SetAttribute
        // -1 for x and/or y to position the window on the center of the screen
        CWindow( const char *title, 
                 int width = 800, 
                 int height = 600, 
                 EWindowDisplayMode displayMode = EWindowDisplayMode::WINDOWED, 
                 int x = -1, 
                 int y = -1, 
                 bool showAfterCreating = true, 
                 bool useVsync = false );

        ~CWindow();

        bool isValid() const;

        void setTitle( const std::string& title );
        void setTitle( const char *title );
        const char *getTitle() const;

        void setDisplayMode( EWindowDisplayMode displayMode );
        EWindowDisplayMode getDisplayMode() const;

        void setResizable( bool resizable );
        bool isResizable() const;

        void setSize( int w, int h );
        int getSizeWidth() const;
        int getSizeHeight() const;

        void setPosition( int x, int y );
        int getPositionX() const;
        int getPositionY() const;

        void minimize();
        bool isMinimized() const;
        void maximize(); // requires the window to be resizable
        bool isMaximized() const;
        void restore(); // restore the windowed from minimized or maximized state

        void toggleVsync( bool toggle );

        void show();
        bool isShown() const;
        void hide();
        bool isHidden() const;

        const CFramebuffer& getFramebuffer() const;

        void clear();
        void flipBuffer();
    };

} // namespace chestnut::engine

