#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/maths/vector2.hpp"
#include "chestnut/engine/maths/matrix4.hpp"

namespace chestnut::engine
{
    class CHESTNUT_API CCamera2D
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

