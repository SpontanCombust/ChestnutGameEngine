#include "engine/graphics/texture_resource.hpp"

#include "engine/debug/debug.hpp"

namespace chestnut 
{
    CTextureResource::CTextureResource( const std::string path, SDL_Renderer *renderer ) 
    {
        loadFromFile( path, renderer );
    }

    CTextureResource::~CTextureResource()
    {
        SDL_DestroyTexture( m_sdlTexture );
        m_sdlTexture = nullptr;
    }

    void CTextureResource::loadFromFile( const std::string path, SDL_Renderer *renderer ) 
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
            m_sdlTexture = SDL_CreateTextureFromSurface( renderer, loadedSurf );
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