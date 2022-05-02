#ifndef __CHESTNUT_ENGINE_LIGHT_H__
#define __CHESTNUT_ENGINE_LIGHT_H__

#include "../maths/vector3.hpp"


namespace chestnut::engine
{
    class CLight
    {
    public:
        vec3f m_ambient;
        vec3f m_diffuse;
        vec3f m_specular;

    protected: // so it can't be instantiated
        CLight();
        virtual ~CLight() = default;
    };


    class CDirectionalLight : public CLight
    {
    public:
        vec3f m_direction;

    public:
        CDirectionalLight();
    };


    class CPointLight : public CLight
    {
    public:
        vec3f m_position;
        float m_constant;
        float m_linear;
        float m_quadratic;

    public:
        CPointLight();
    };


    class CSpotLight : public CPointLight
    {
    public:
        vec3f m_direction;
        float m_cutoffInner;
        float m_cutoffOuter;
    
    public:
        CSpotLight();
    };
    
} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_LIGHT_H__