#include "application.hpp"

#include "engine/globals.hpp"

namespace chestnut
{
    CApplication *CApplication::m_instance = nullptr;


    CApplication::CApplication( float renderInterval ) 
    {
        m_updateInterval = -1.f;
        m_renderInterval = renderInterval;

        // set this instance as theApp
        if( !m_instance )
        {
            m_instance = this;
        }
    }

    CApplication::CApplication( float renderInterval, float updateInterval ) 
    {
        m_updateInterval = updateInterval;
        m_renderInterval = renderInterval;

        // set this instance as theApp
        if( !m_instance )
        {
            m_instance = this;
        }
    }

    CApplication::~CApplication() 
    {
        if( m_instance == this )
        {
            m_instance = nullptr;
        }
    }

    bool CApplication::onCreate()
    {
        SWindowProperties properties = windowPropertiesDefault( 3, 3 );

        if( !window.create( properties, "Chestnut App", 800, 600, 0, 0 ) )
        {
            return false;
        }

        engine.init( m_renderInterval, m_updateInterval );

        return true;
    }

    void CApplication::onStart()
    {
        engine.start();
    }

    void CApplication::onEnd()
    {
        window.destroy();
    }

    void CApplication::setInstance( CApplication *app ) 
    {
        if( app )
        {
            m_instance = app;
        }
    }

    CApplication* CApplication::getInstance() 
    {
        return m_instance;
    }

    void CApplication::setWindowParams( const char *title, int width, int height, int x, int y ) 
    {
        window.setTitle( title );
        window.setSize( width, height );
        window.setPosition( x, y );
    }

} // namespace chestnut
