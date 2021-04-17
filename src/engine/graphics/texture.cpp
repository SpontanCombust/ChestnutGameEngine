#include "texture.hpp"

#include "engine/maths/angles.hpp"
#include "engine/debug/debug.hpp"
#include "renderer.hpp"

#define DEF_FORMAT SDL_PIXELFORMAT_RGBA8888
#define DEF_ACCESS SDL_TEXTUREACCESS_TARGET

namespace chestnut 
{

    CTexture::CTexture() 
    {
        m_sdlTexture = nullptr;
        m_isResourceInstance = false;

        m_clippingRectPos = { 0, 0 };
        m_clippingRectSize = { 0, 0 };
        m_position = { 0.f, 0.f };
        m_size = { 0.f, 0.f };
        m_rotationRad = 0.f;
        m_rotationPoint = { 0.f, 0.f };
        m_flip = SDL_FLIP_NONE;
    }

    CTexture::CTexture( int w, int h ) 
    {
        m_sdlTexture = SDL_CreateTexture( CRenderer::getSDLRenderer(), DEF_FORMAT, DEF_ACCESS, w, h );
        m_isResourceInstance = false;

        m_clippingRectPos = { 0, 0 };
        m_clippingRectSize = { w, h };
        m_position = { 0.f, 0.f };
        m_size = { (float)w, (float)h };
        m_rotationRad = 0.f;
        m_rotationPoint = { 0.5f, 0.5f };
        m_flip = SDL_FLIP_NONE;
    }

    CTexture::CTexture( const CTextureResource *texture ) 
    {
        m_sdlTexture = texture->getSDLTexturePtr();
        m_isResourceInstance = true;

        m_clippingRectPos = { 0, 0 };
        m_clippingRectSize = texture->getSize();
        m_position = { 0.f, 0.f };
        m_size = texture->getSize();
        m_rotationRad = 0.f;
        m_rotationPoint = { 0.5f, 0.5f };
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
        m_clippingRectPos = { x, y };
        m_clippingRectSize = { w, h };
    }

    void CTexture::setClippingRect( vec2i position, vec2i dimensions ) 
    {
        m_clippingRectPos = position;
        m_clippingRectSize = dimensions;
    }
    
    const vec2i& CTexture::getClippingRectPos() const 
    {
        return m_clippingRectPos;
    }

    const vec2i& CTexture::getClippingRectSize() const
    {
        return m_clippingRectSize;
    }

    void CTexture::setPosition( float x, float y ) 
    {
        m_position = { x, y };
    }

    void CTexture::setPosition( vec2f position ) 
    {
        m_position = position;
    }

    const vec2f& CTexture::getPosition() const
    {
        return m_position;
    }

    void CTexture::setScale( float sx, float sy ) 
    {
        m_size = 
        { 
            sx * m_clippingRectSize.x,
            sy * m_clippingRectSize.y 
        };
    }

    void CTexture::setScale( vec2f scale ) 
    {
        m_size = 
        { 
            scale.x * m_clippingRectSize.x,
            scale.y * m_clippingRectSize.y 
        };
    }

    const vec2f CTexture::getScale() const
    {
        return vec2f( 
            m_size.x / m_clippingRectSize.x,
            m_size.y / m_clippingRectSize.y
        );
    }

    void CTexture::setSizeDirectly( float w, float h ) 
    {
        m_size = { w, h };
    }

    void CTexture::setSizeDirectly( vec2f size ) 
    {
        m_size = { size.x, size.y };
    }

    const vec2f& CTexture::getSize() const 
    {
        return m_size;
    }

    void CTexture::setRotation( float angleRad ) 
    {
        m_rotationRad = angleRad;
    }

    void CTexture::setRotation( vec2f rotationVec ) 
    {
        // 0 radians is equivalent to vector [1;0]
        m_rotationRad = unitVec2fToAngle( vec2Normalized( rotationVec ) );
    }
    
    const float& CTexture::getRotationRad() const
    {
        return m_rotationRad;
    }

    const vec2f CTexture::getRotationVec() const
    {
        return angleToUnitVec2f( m_rotationRad );
    }

    void CTexture::setRotationPoint( float rx, float ry ) 
    {
        m_rotationPoint = { rx, ry };
    }

    void CTexture::setRotationPoint( vec2f rotPoint ) 
    {
        m_rotationPoint = rotPoint;
    }

    void CTexture::setRotationPointToCenter() 
    {
        m_rotationPoint = { 0.5f, 0.5f };
    }

    const vec2f& CTexture::getRotationPoint() const
    {
        return m_rotationPoint;
    }

    void CTexture::setFlip( SDL_RendererFlip flip ) 
    {
        m_flip = flip;
    }

    const SDL_RendererFlip& CTexture::getFlip() const
    {
        return m_flip;
    }

    SDL_Texture* CTexture::getSDLTexturePtr() const
    {
        return m_sdlTexture;
    }

} // namespace chestnut