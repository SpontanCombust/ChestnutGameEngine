#include "sprite.hpp"

namespace chestnut::engine
{    
    CSprite::CSprite()
    {
        m_clipRect = { 0, 0, 0, 0 };
        m_tint = { 1.f, 1.f, 1.f };
        m_tintFactor = 0.f;
    }

    CSprite::CSprite(std::shared_ptr<CTexture2DResource> resource)
    : CTexture2D(resource)
    {
        m_clipRect = { 0.f, 0.f, (float)resource->m_width, (float)resource->m_height };
        m_tint = { 1.f, 1.f, 1.f };
        m_tintFactor = 0.f;
    }

    SRectangle CSprite::getClippingRect() const
    {
        return m_clipRect;
    }

    void CSprite::setClippingRect(const SRectangle& rect)
    {
        m_clipRect = rect;
    }

    const vec3f& CSprite::getTint() const
    {
        return m_tint;
    }

    void CSprite::setTint(const vec3f& tint)
    {
        m_tint = tint;
    }

    float CSprite::getTintFactor() const
    {
        return m_tintFactor;
    }

    void CSprite::setTintFactor(float factor)
    {
        m_tintFactor = factor;
    }

} // namespace chestnut::engine
