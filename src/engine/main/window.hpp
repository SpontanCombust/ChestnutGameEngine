#ifndef __CHESTNUT_WINDOW_H__
#define __CHESTNUT_WINDOW_H__

#include "../libs.hpp"

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
    };

    SWindowProperties windowPropertiesDefault( int glVersionMajor, int glVersionMinor );


    class CWindow
    {
    private:
        SDL_Window *m_sdlWindow;
        SDL_GLContext m_sdlGLContext;

    public:
        CWindow();
        ~CWindow();

        bool create( const SWindowProperties& windowProperties, const std::string& title, int width, int height, int x = 0, int y = 0, bool useVsync = false );

        void destroy();

        void setTitle( const std::string& title );
        std::string getTitle();

        void setSize( int w, int h );
        int getWidth();
        int getHeight();

        void setPosition( int x, int y );
        int getPositionX();
        int getPositionY();

        void toggleVsync( bool toggle );

        void clear();
        void flipBuffer();
    };

} // namespace chestnut

#endif // __CHESTNUT_WINDOW_H__
