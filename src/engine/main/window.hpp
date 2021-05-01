#ifndef __CHESTNUT_WINDOW_H__
#define __CHESTNUT_WINDOW_H__

#include "engine/maths/vector2.hpp"
#include "engine/libs.hpp"

namespace chestnut
{
    class CWindow
    {
    private:
        SDL_Window *m_sdlWindow;

    public:
        CWindow();
        ~CWindow();

        bool create( const char *title, int width = 800, int height = 600, int x = 0, int y = 0 );

        void destroy();

        void setTitle( const char *title );
        const char *getTitle();

        void setSize( int w, int h );
        int getWidth();
        int getHeight();

        void setPosition( int x, int y );
        int getPositionX();
        int getPositionY();

        void clear();
        void flipBuffer();
    };

} // namespace chestnut

#endif // __CHESTNUT_WINDOW_H__
