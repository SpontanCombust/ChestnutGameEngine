#include "engine/graphics/texture.hpp"

#define DEF_FORMAT SDL_PIXELFORMAT_RGBA8888
#define DEF_ACCESS SDL_TEXTUREACCESS_TARGET

namespace engine { namespace graphics {

    CTexture::CTexture( int w, int h, SDL_Renderer *renderer ) 
    {
        m_sdlTexture = SDL_CreateTexture( renderer, DEF_FORMAT, DEF_ACCESS, w, h );
        m_isResourceInstance = false;

        m_srcRect = { 0, 0, w, h };
        m_dstRect = { 0.f, 0.f, (float)w, (float)h };
        m_rotPoint = { (float)w / 2.f, (float)h / 2.f };
        m_angleDeg = 0.f;
        m_flip = SDL_FLIP_NONE;
    }

    CTexture::CTexture( const CTextureResource *texture ) 
    {
        m_sdlTexture = texture->m_sdlTexture;
        m_isResourceInstance = true;

        vector::Vector2i size = texture->getSize();
        m_srcRect = { 0, 0, size.x, size.y };
        m_dstRect = { 0.f, 0.f, (float)size.x, (float)size.y };
        m_rotPoint = { (float)size.x / 2.f, (float)size.y / 2.f };
        m_angleDeg = 0.f;
        m_flip = SDL_FLIP_NONE;
    }
    
    CTexture::~CTexture()
    {
        if( !m_isResourceInstance )
        {
            SDL_DestroyTexture( m_sdlTexture );
            m_sdlTexture = nullptr;
        }
    }

    void CTexture::setClippingRect( int x, int y, int w, int h ) 
    {
        m_srcRect = { x, y, w, h };
    }

    void CTexture::setScale( float sx, float sy ) 
    {
        m_dstRect = { m_srcRect.w * sx, m_srcRect.h * sy };
    }
    
    void CTexture::setRotation( float angleDeg ) 
    {
        m_angleDeg = angleDeg;
    }
  
    void CTexture::setRotationPoint( float rx, float ry ) 
    {
        m_rotPoint = { rx, ry };
    }
  
    void CTexture::setFlip( SDL_RendererFlip flip ) 
    {
        m_flip = flip;
    }

    void CTexture::render( SDL_Renderer *r, float x, float y ) 
    {
        SDL_RenderCopyExF( r, m_sdlTexture, &m_srcRect, &m_dstRect, m_angleDeg, &m_rotPoint, m_flip );
    }
}}