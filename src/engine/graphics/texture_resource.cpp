#include "engine/graphics/texture_resource.hpp"

#include "engine/debug/debug.hpp"
#include "engine/app/render_window.hpp"

namespace chestnut 
{
    CTextureResource::CTextureResource( const std::string path ) 
    {
        loadFromFile( path );
    }

    CTextureResource::~CTextureResource()
    {
        SDL_DestroyTexture( m_sdlTexture );
        m_sdlTexture = nullptr;
    }

    void CTextureResource::loadFromFile( const std::string path ) 
    {
        if( m_sdlTexture != nullptr )
            SDL_DestroyTexture( m_sdlTexture );
        
        SDL_Surface *loadedSurf = IMG_Load( path.c_str() );
        if( loadedSurf == nullptr )
        {
            //TODO create 'missing texture' dummy
            LOG( "Failed to load an image " + path );
            LOG( SDL_GetError() );
        }
        else
        {
            m_sdlTexture = SDL_CreateTextureFromSurface( CRenderWindow::getSDLRenderer(), loadedSurf );
            if( m_sdlTexture == nullptr )
            {
                LOG( "Failed to create texture from " + path );
                LOG( SDL_GetError() );
            }
            SDL_FreeSurface( loadedSurf );
        }
    }

    Vector2i CTextureResource::getSize() const
    {
        Vector2i size;
        SDL_QueryTexture( m_sdlTexture, NULL, NULL, &size.x, &size.y );
        return size;
    }

    CTexture CTextureResource::getTextureInstance() const
    {
        return CTexture(this);
    }
    
} // namespace chestnut