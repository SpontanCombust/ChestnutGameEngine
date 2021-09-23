#ifndef __CHESTNUT_WINDOW_H__
#define __CHESTNUT_WINDOW_H__

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <memory>
#include <string>

namespace chestnut
{
    struct SWindowProperties
    {
        int sdlWindowFlags;
        int sdlGLContextVersionMajor;
        int sdlGLContextVersionMinor;
        int sdlGLContextFlags;
        int sdlGLContextProfileMask;

        SWindowProperties() = default;
        SWindowProperties( int glVersionMajor, int glVersionMinor );
    };


    enum class EWindowDisplayMode
    {
        WINDOWED,
        WINDOWED_BORDLERLESS,
        FULLSCREEN
    };


    class CWindow
    {
    private:
        SDL_Window *m_sdlWindow;
        SDL_GLContext m_sdlGLContext;

    public:
        CWindow( SDL_Window *window, SDL_GLContext context );
        ~CWindow();

        void setTitle( const std::string& title );
        std::string getTitle();

        void setDisplayMode( EWindowDisplayMode displayMode );
        EWindowDisplayMode getDisplayMode() const;

        void setResizable( bool resizable );
        bool isResizable() const;

        void setSize( int w, int h );
        int getSizeWidth();
        int getSizeHeight();

        void setPosition( int x, int y );
        int getPositionX();
        int getPositionY();

        void toggleVsync( bool toggle );

        void clear();
        void flipBuffer();
    };

    // -1 for x and/or y to position the window on the center of the screen
    std::shared_ptr<CWindow> createWindow( const SWindowProperties& windowProperties, const std::string& title, int width = 800, int height = 600, int x = -1, int y = -1, bool useVsync = false );


} // namespace chestnut

#endif // __CHESTNUT_WINDOW_H__
