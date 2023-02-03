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
        // Position of the center of the camera
        vec2f m_position;
        // Size of virtual camera screen
        vec2f m_dimensions;
        // The greater the bigger are objects on screen
        float m_zoom;


    public:
        CCamera2D();

        void calculateMatrices();

        const mat4f& getViewMatrix() const;
        const mat4f& getProjectionMatrix() const;
    };

} // namespace chestnut::engine

