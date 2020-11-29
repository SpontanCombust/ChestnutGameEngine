#include "engine/graphics/texture.hpp"

#include "engine/maths/angles.hpp"
#include "engine/debug/debug.hpp"
#include "engine/graphics/renderer.hpp"

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
        m_flip = ETextureFlip::NONE;
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
        m_flip = ETextureFlip::NONE;
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
        m_flip = ETextureFlip::NONE;
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

    void CTexture::setClippingRect( Vector2i position, Vector2i dimensions ) 
    {
        m_clippingRectPos = position;
        m_clippingRectSize = dimensions;
    }
    
    const Vector2i& CTexture::getClippingRectPos() const 
    {
        return m_clippingRectPos;
    }

    const Vector2i& CTexture::getClippingRectSize() const
    {
        return m_clippingRectSize;
    }

    void CTexture::setPosition( float x, float y ) 
    {
        m_position = { x, y };
    }

    void CTexture::setPosition( Vector2f position ) 
    {
        m_position = position;
    }

    const Vector2f& CTexture::getPosition() const
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

    void CTexture::setScale( Vector2f scale ) 
    {
        m_size = 
        { 
            scale.x * m_clippingRectSize.x,
            scale.y * m_clippingRectSize.y 
        };
    }

    const Vector2f CTexture::getScale() const
    {
        return Vector2f( 
            m_size.x / m_clippingRectSize.x,
            m_size.y / m_clippingRectSize.y
        );
    }

    void CTexture::setSizeDirectly( float w, float h ) 
    {
        m_size = { w, h };
    }

    void CTexture::setSizeDirectly( Vector2f size ) 
    {
        m_size = { size.x, size.y };
    }

    const Vector2f& CTexture::getSize() const 
    {
        return m_size;
    }

    void CTexture::setRotation( float angleRad ) 
    {
        m_rotationRad = angleRad;
    }

    void CTexture::setRotation( Vector2f rotationVec ) 
    {
        // 0 radians is equivalent to vector [1;0]
        m_rotationRad = unitVector2fToAngle( vec2GetNormalized( rotationVec ) );
    }
    
    const float& CTexture::getRotationRad() const
    {
        return m_rotationRad;
    }

    const Vector2f CTexture::getRotationVec() const
    {
        return angleToUnitVector2f( m_rotationRad );
    }

    void CTexture::setRotationPoint( double rx, double ry ) 
    {
        m_rotationPoint = { rx, ry };
    }

    void CTexture::setRotationPoint( Vector2<double> rotPoint ) 
    {
        m_rotationPoint = rotPoint;
    }

    void CTexture::setRotationPointToCenter() 
    {
        m_rotationPoint = { 0.5f, 0.5f };
    }

    const Vector2<double>& CTexture::getRotationPoint() const
    {
        return m_rotationPoint;
    }

    void CTexture::setFlip( ETextureFlip flip ) 
    {
        m_flip = flip;
    }

    const ETextureFlip& CTexture::getFlip() const
    {
        return m_flip;
    }

    SDL_Texture* CTexture::getSDLTexturePtr() const
    {
        return m_sdlTexture;
    }

} // namespace chestnut