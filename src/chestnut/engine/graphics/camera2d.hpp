#ifndef __CHESTNUT_ENGINE_CAMERA2D_H__
#define __CHESTNUT_ENGINE_CAMERA2D_H__

#include "../maths/vector2.hpp"
#include "../maths/matrix4.hpp"

namespace chestnut::engine
{
    class CCamera2D
    {
    private:
        mat4f m_viewMatrix;
        mat4f m_projMatrix;

    public:
        vec2f m_position;
        vec2f m_dimensions;
        float m_zoom;


    public:
        CCamera2D();

        void calculateMatrices();

        const mat4f& getViewMatrix() const;
        const mat4f& getProjectionMatrix() const;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_CAMERA2D_H__