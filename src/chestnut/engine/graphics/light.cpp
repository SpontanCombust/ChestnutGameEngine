#include "chestnut/engine/graphics/light.hpp"

namespace chestnut::engine
{    
    CLight::CLight()
    : m_ambient(0.0f, 0.0f, 0.0f), m_diffuse(0.0f, 0.0f, 0.0f), m_specular(0.0f, 0.0f, 0.0f)
    {

    }

    CDirectionalLight::CDirectionalLight()
    : m_direction(1.0f, 0.0f, 0.0f)
    {

    }

    CPointLight::CPointLight()
    : m_position(0.0f, 0.0f, 0.0f), m_constant(1.0f), m_linear(1.0f), m_quadratic(1.0f)
    {

    }

    CSpotLight::CSpotLight()
    : m_direction(1.0f, 0.0f, 0.0f), m_cutoffInner(0.f), m_cutoffOuter(0.0f)
    {

    }

} // namespace chestnut::engine
