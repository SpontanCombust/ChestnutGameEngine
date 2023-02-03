#pragma once


#include "chestnut/engine/maths/vector3.hpp"

namespace chestnut::engine
{
    class CLight
    {
    public:
        vec3f m_ambient  {0.0f, 0.0f, 0.0f};
        vec3f m_diffuse  {0.0f, 0.0f, 0.0f};
        vec3f m_specular {0.0f, 0.0f, 0.0f};

    protected: // so it can't be instantiated
        CLight() = default;
        virtual ~CLight() = default;
    };


    class CDirectionalLight : public CLight
    {
    public:
        vec3f m_direction {1.0f, 0.0f, 0.0f};
    };


    class CPointLight : public CLight
    {
    public:
        vec3f m_position  {0.0f, 0.0f, 0.0f};
        float m_constant  {1.0f};
        float m_linear    {1.0f};
        float m_quadratic {1.0f};
    };


    class CSpotLight : public CPointLight
    {
    public:
        vec3f m_direction   {1.0f, 0.0f, 0.0f};
        float m_cutoffInner {0.0f};
        float m_cutoffOuter {0.0f};
    };
    
} // namespace chestnut::engine

