#include "chestnut/engine/graphics/camera2d.hpp"

namespace chestnut::engine
{    
    CCamera2D::CCamera2D() 
    {
        m_zoom = 1.f;
    }

    void CCamera2D::calculateMatrices() 
    {
        m_viewMatrix = matMakeTranslation(m_dimensions.x / 2.f, m_dimensions.y / 2.f, 0.f) 
                     * matMakeScale(m_zoom, m_zoom, 0.f) 
                     * matMakeTranslation(-m_position.x, -m_position.y, 0.f);

        m_projMatrix = matMakeOrthographic( 0.f, m_dimensions.x, m_dimensions.y, 0.f, -1.f, 1.f );
    }

    const mat4f& CCamera2D::getViewMatrix() const
    {
        return m_viewMatrix;
    }

    const mat4f& CCamera2D::getProjectionMatrix() const
    {
        return m_projMatrix;
    }

} // namespace chestnut::engine
