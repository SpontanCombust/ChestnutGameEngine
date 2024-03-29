#include "chestnut/engine/main/window.hpp"

#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/misc/exception.hpp"
#include "chestnut/engine/init.hpp"

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <SDL.h>
#include <glad/glad.h>
#include <SDL_opengl.h>

#include <cassert>

namespace chestnut::engine
{
    static unsigned char s_activeCount = 0;


    CWindow::CWindow( const char *title, int width, int height, EWindowDisplayMode displayMode, int x, int y, bool showAfterCreating, bool useVsync ) 
    {
        assert(chestnutWasInit() && "Can't create a window without first initializing the dependency libraries! Use chestnutInit() first!");

        // ========= Create window and context ========= //

        // if x and/or y are lesser than 0 se the position at the center of the screen
        Uint32 windowFlags = SDL_WINDOW_OPENGL;
        if( !showAfterCreating )
        {
            windowFlags |= SDL_WINDOW_HIDDEN;
        }
        if( displayMode == EWindowDisplayMode::WINDOWED_BORDLERLESS )
        {
            windowFlags |= SDL_WINDOW_BORDERLESS;
        }
        else if( displayMode == EWindowDisplayMode::FULLSCREEN )
        {
            windowFlags |= SDL_WINDOW_FULLSCREEN;
        }


        x = ( x < 0 ) ? SDL_WINDOWPOS_CENTERED : x;
        y = ( y < 0 ) ? SDL_WINDOWPOS_CENTERED : y;


        LOG_INFO("Creating the window...");

        SDL_Window *window = SDL_CreateWindow( title, x, y, width, height, windowFlags );
        if( !window )
        {
            LOG_ERROR( "Failed to create window. Error: " << SDL_GetError() );
            throw ChestnutException("SDL_CreateWindow() failure");
        }


        LOG_INFO("Creating OpenGL context for the window...");

        SDL_GLContext context = SDL_GL_CreateContext( window );
        if( !context )
        {
            LOG_ERROR( "Failed to create OpenGL context for the window. Error: " << SDL_GetError() );
            SDL_DestroyWindow( window );
            throw ChestnutException("SDL_GL_CreateContext() failure");
        }



        // ========= Init OpenGL ========= //

        LOG_INFO("Initializing GLAD...");

        if(gladLoadGLLoader(SDL_GL_GetProcAddress) == 0)
        {
            LOG_ERROR( "Failed to initialize GLAD!" );
            SDL_GL_DeleteContext( context );
            SDL_DestroyWindow( window );
            throw ChestnutException("gladLoadGLLoader() failure");
        }

        glViewport( 0, 0, width, height );

        glEnable( GL_TEXTURE_2D );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        //disabled until actually needed
        //glEnable( GL_DEPTH_TEST );

        int interval = useVsync ? 1 : 0;
        SDL_GL_SetSwapInterval( interval );



    #ifdef CHESTNUT_DEBUG
        // ========= Init ImGui ========= //

        LOG_INFO("Initializing ImGui...");

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(window, context);
        ImGui_ImplOpenGL3_Init("#version 330");
    #endif      



        m_sdlWindow = window;
        m_sdlGLContext = context;

        m_framebuffer = new CFramebuffer( width, height );
        m_framebuffer->setClearColor( vec4f{ 0.f, 0.f, 0.f, 1.f } );

        s_activeCount++;
    }

    CWindow::CWindow(CWindowAttribs attribs)
    : CWindow(
        attribs.m_title.c_str(),
        attribs.m_width,
        attribs.m_height,
        attribs.m_displayMode,
        attribs.m_position.x,
        attribs.m_position.y,
        attribs.m_show,
        attribs.m_vsync)
    {

    }

    CWindow::~CWindow() 
    {
    #ifdef CHESTNUT_DEBUG
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    #endif

        delete m_framebuffer;
        SDL_GL_DeleteContext( m_sdlGLContext );
        SDL_DestroyWindow( m_sdlWindow );

        s_activeCount--;
    }

    void CWindow::setTitle( const std::string& title ) 
    {
        SDL_SetWindowTitle( m_sdlWindow, title.c_str() );
    }

    void CWindow::setTitle( const char *title ) 
    {
        SDL_SetWindowTitle( m_sdlWindow, title );
    }

    const char *CWindow::getTitle() const 
    {
        return SDL_GetWindowTitle( m_sdlWindow );
    }

    void CWindow::setDisplayMode( EWindowDisplayMode displayMode ) 
    {
        switch( displayMode )
        {
            case EWindowDisplayMode::WINDOWED:
                SDL_SetWindowFullscreen( m_sdlWindow, 0 );
                SDL_SetWindowBordered( m_sdlWindow, SDL_TRUE );
                break;
            case EWindowDisplayMode::WINDOWED_BORDLERLESS:
                SDL_SetWindowFullscreen( m_sdlWindow, 0 );
                SDL_SetWindowBordered( m_sdlWindow, SDL_FALSE );
                break;
            case EWindowDisplayMode::FULLSCREEN:
                SDL_SetWindowFullscreen( m_sdlWindow, SDL_WINDOW_FULLSCREEN );
                break;
            default:
                SDL_SetWindowFullscreen( m_sdlWindow, 0 );
        }
    }

    EWindowDisplayMode CWindow::getDisplayMode() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_sdlWindow );

        if( ( flags & SDL_WINDOW_FULLSCREEN ) > 0 )
        {
            return EWindowDisplayMode::FULLSCREEN;
        }
        else if( ( flags & SDL_WINDOW_BORDERLESS ) > 0 )
        {
            return EWindowDisplayMode::WINDOWED_BORDLERLESS;
        }
        else
        {
            return EWindowDisplayMode::WINDOWED;
        }
    }

    void CWindow::setResizable( bool resizable ) 
    {
        SDL_SetWindowResizable( m_sdlWindow, resizable ? SDL_TRUE : SDL_FALSE );
    }

    bool CWindow::isResizable() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_sdlWindow );

        return ( flags & SDL_WINDOW_RESIZABLE ) > 0;
    }

    int CWindow::getWidth() const
    {
        return m_framebuffer->getWidth();
    }

    void CWindow::setWidth(int w) 
    {
        int h = getHeight();
        SDL_SetWindowSize(m_sdlWindow, w, h);
        *m_framebuffer = std::move(CFramebuffer(w, h));
    }

    int CWindow::getHeight() const
    {
        return m_framebuffer->getHeight();
    }

    void CWindow::setHeight(int h) 
    {
        int w = getWidth();
        SDL_SetWindowSize(m_sdlWindow, w, h);
        *m_framebuffer = std::move(CFramebuffer(w, h));
    }

    vec2i CWindow::getSize() const
    {
        return {
            m_framebuffer->getWidth(),
            m_framebuffer->getHeight()
        };
    }

    void CWindow::setSize(vec2i size) 
    {
        SDL_SetWindowSize(m_sdlWindow, size.x, size.y);
        *m_framebuffer = std::move(CFramebuffer(size.x, size.y));
    }

    void CWindow::setPosition( int x, int y ) 
    {
        SDL_SetWindowPosition( m_sdlWindow, x, y );
    }

    int CWindow::getPositionX() const
    {
        int x;
        SDL_GetWindowPosition( m_sdlWindow, &x, NULL );
        return x;
    }

    int CWindow::getPositionY() const
    {
        int y;
        SDL_GetWindowPosition( m_sdlWindow, NULL, &y );
        return y;
    }

    void CWindow::minimize() 
    {
        SDL_MinimizeWindow( m_sdlWindow );
    }

    bool CWindow::isMinimized() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_sdlWindow );

        return ( flags & SDL_WINDOW_MINIMIZED ) > 0;
    }

    void CWindow::maximize() 
    {
        SDL_MaximizeWindow( m_sdlWindow );
    }

    bool CWindow::isMaximized() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_sdlWindow );

        return ( flags & SDL_WINDOW_MAXIMIZED ) > 0;
    }

    void CWindow::restore() 
    {
        SDL_RestoreWindow( m_sdlWindow );
    }

    void CWindow::toggleVsync( bool toggle ) 
    {
        if( toggle )
        {
            SDL_GL_SetSwapInterval(1);
        }
        else
        {
            SDL_GL_SetSwapInterval(0);
        }
    }

    void CWindow::show() 
    {
        SDL_ShowWindow( m_sdlWindow );
    }

    bool CWindow::isShown() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_sdlWindow );

        return ( flags & SDL_WINDOW_SHOWN ) > 0;
    }

    void CWindow::hide() 
    {
        SDL_HideWindow( m_sdlWindow );
    }

    bool CWindow::isHidden() const
    {
        Uint32 flags = SDL_GetWindowFlags( m_sdlWindow );

        return ( flags & SDL_WINDOW_HIDDEN ) > 0;
    }

    const CFramebuffer& CWindow::getFramebuffer() const
    {
        return *m_framebuffer;
    }

    void CWindow::clear() 
    {
        m_framebuffer->bind();
        m_framebuffer->clear();
    }

    void CWindow::flipBuffer() 
    {
        SDL_GL_SwapWindow( m_sdlWindow );
    }

    bool CWindow::isAnyActive()
    {
        return s_activeCount > 0;
    }






    CWindowAttribs::CWindowAttribs(const std::string& title) noexcept
    : m_title(title)
    {

    }
    
    CWindowAttribs& CWindowAttribs::title(const std::string& t) noexcept
    {
        m_title = t;
        return *this;
    }

    CWindowAttribs& CWindowAttribs::width(int w) noexcept
    {
        m_width = w;
        return *this;
    }

    CWindowAttribs& CWindowAttribs::height(int h) noexcept
    {
        m_height = h;
        return *this;
    }

    CWindowAttribs& CWindowAttribs::displayMode(EWindowDisplayMode mode) noexcept
    {
        m_displayMode = mode;
        return *this;
    }

    CWindowAttribs& CWindowAttribs::position(vec2i p) noexcept
    {
        m_position = p;
        return *this;
    }

    CWindowAttribs& CWindowAttribs::show(bool b) noexcept
    {
        m_show = b;
        return *this;
    }

    CWindowAttribs& CWindowAttribs::vsync(bool b) noexcept
    {
        m_vsync = b;
        return *this;
    }

} // namespace chestnut::engine