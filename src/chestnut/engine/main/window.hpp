#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/graphics/opengl/framebuffer.hpp"
#include "chestnut/engine/maths/vector2.hpp"

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


    class CHESTNUT_API CWindowAttribs
    {
    public:
        std::string m_title;
        int m_width = 800;
        int m_height = 600;
        EWindowDisplayMode m_displayMode = EWindowDisplayMode::WINDOWED;
        vec2i m_position = {0, 0};
        bool m_show = true;
        bool m_vsync = false;

    public:
        CWindowAttribs(const std::string& title) noexcept;

        CWindowAttribs& title(const std::string& t) noexcept;
        CWindowAttribs& width(int w) noexcept;
        CWindowAttribs& height(int h) noexcept;
        CWindowAttribs& displayMode(EWindowDisplayMode mode) noexcept;
        CWindowAttribs& position(vec2i p) noexcept;
        CWindowAttribs& show(bool b) noexcept;
        CWindowAttribs& vsync(bool b) noexcept;
    };


    class CHESTNUT_API CWindow
    {
    private:
        SDL_Window *m_sdlWindow;
        SDL_GLContext m_sdlGLContext;
        CFramebuffer *m_framebuffer; // for now just a dummy with no texture bound

    public:
        // Says whether any window is running in the program
        // If so this means, among other things, that an OpenGL context is available
        static bool isAnyActive();


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

        CWindow(CWindowAttribs attribs);

        ~CWindow();

        void setTitle( const std::string& title );
        void setTitle( const char *title );
        const char *getTitle() const;

        void setDisplayMode( EWindowDisplayMode displayMode );
        EWindowDisplayMode getDisplayMode() const;

        void setResizable( bool resizable );
        bool isResizable() const;

        int getWidth() const;
        void setWidth(int w);
        int getHeight() const;
        void setHeight(int h);
        vec2i getSize() const;
        void setSize(vec2i size);

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

