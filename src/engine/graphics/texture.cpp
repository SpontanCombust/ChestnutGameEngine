#include "engine/graphics/texture.hpp"

#include "engine/app/render_window.hpp"
#include "engine/core/angles.hpp"
#include "engine/debug/debug.hpp"

#define DEF_FORMAT SDL_PIXELFORMAT_RGBA8888
#define DEF_ACCESS SDL_TEXTUREACCESS_TARGET

namespace chestnut 
{
    CTexture::CTexture( int w, int h ) 
    {
        m_sdlTexture = SDL_CreateTexture( CRenderWindow::getSDLRenderer(), DEF_FORMAT, DEF_ACCESS, w, h );
        m_isResourceInstance = false;

        m_srcRect = { 0, 0, w, h };
        m_dstRect = { 0.f, 0.f, (float)w, (float)h };
        m_rotPoint = { 0.f, 0.f };
        m_angleDeg = 0.f;
        m_flip = SDL_FLIP_NONE;
    }

    CTexture::CTexture( const CTextureResource *texture ) 
    {
        m_sdlTexture = texture->getSDLTexturePtr();
        m_isResourceInstance = true;

        Vector2i size = texture->getSize();
        m_srcRect = { 0, 0, size.x, size.y };
        m_dstRect = { 0.f, 0.f, (float)size.x, (float)size.y };
        m_rotPoint = { 0.f, 0.f };
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

    void CTexture::setClippingRect( Vector2i position, Vector2i dimensions ) 
    {
        m_srcRect = { position.x, position.y, dimensions.x, dimensions.y };
    }

    void CTexture::setPosition( float x, float y ) 
    {
        m_dstRect.x = x;
        m_dstRect.y = y;
    }

    void CTexture::setPosition( Vector2f position ) 
    {
        m_dstRect.x = position.x;
        m_dstRect.y = position.y;
    }

    void CTexture::setScale( float sx, float sy ) 
    {
        m_dstRect.w = m_srcRect.w * sx;
        m_dstRect.h = m_srcRect.h * sy;
    }

    void CTexture::setScale( Vector2f scale ) 
    {
        m_dstRect.w = m_srcRect.w * scale.x;
        m_dstRect.h = m_srcRect.h * scale.y;
    }

    void CTexture::setDimensionsDirectly( float w, float h ) 
    {
        m_dstRect.w = w;
        m_dstRect.h = h;
    }

    void CTexture::setDimensionsDirectly( Vector2f dimensions ) 
    {
        m_dstRect.w = dimensions.x;
        m_dstRect.h = dimensions.y;
    }

    void CTexture::setRotation( float angleDeg ) 
    {
        m_angleDeg = angleDeg;
    }

    void CTexture::setRotation( Vector2f rotation ) 
    {   //TODO Remember it's based on traditional cartesian system (rotating clockwise = angle decreases), so it has to be adapted for SDL
        m_angleDeg = -radiansToDegrees( unitVector2fToAngle( rotation ) );
    }

    void CTexture::setRotationPoint( float rx, float ry ) 
    {
        m_rotPoint = { rx, ry };
    }

    void CTexture::setRotationPoint( Vector2f rotPoint ) 
    {
        m_rotPoint = { rotPoint.x, rotPoint.y };
    }

    void CTexture::setRotationPointToCenter() 
    {
        m_rotPoint = { m_dstRect.x / 2.f, m_dstRect.y / 2.f };
    }

    void CTexture::setFlip( SDL_RendererFlip flip ) 
    {
        m_flip = flip;
    }

    void CTexture::draw() const
    {
        SDL_RenderCopyExF( CRenderWindow::getSDLRenderer(), m_sdlTexture, &m_srcRect, &m_dstRect, m_angleDeg, &m_rotPoint, m_flip );
    }

    void CTexture::draw( float x, float y ) const
    {
        SDL_FRect dstRect = { x, y, m_dstRect.w, m_dstRect.h };
        SDL_RenderCopyExF( CRenderWindow::getSDLRenderer(), m_sdlTexture, &m_srcRect, &dstRect, m_angleDeg, &m_rotPoint, m_flip );
    }

} // namespace chestnut