#ifndef __CHESTNUT_ENGINE_LIGHT_H__
#define __CHESTNUT_ENGINE_LIGHT_H__

#include "chestnut/engine/macros.hpp"
#include "../maths/vector3.hpp"


namespace chestnut::engine
{
    class CHESTNUT_API CLight
    {
    public:
        vec3f m_ambient;
        vec3f m_diffuse;
        vec3f m_specular;

    protected: // so it can't be instantiated
        CLight();
        virtual ~CLight() = default;
    };


    class CHESTNUT_API CDirectionalLight : public CLight
    {
    public:
        vec3f m_direction;

    public:
        CDirectionalLight();
    };


    class CHESTNUT_API CPointLight : public CLight
    {
    public:
        vec3f m_position;
        float m_constant;
        float m_linear;
        float m_quadratic;

    public:
        CPointLight();
    };


    class CHESTNUT_API CSpotLight : public CPointLight
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