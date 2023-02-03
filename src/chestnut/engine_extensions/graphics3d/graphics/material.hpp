#pragma once


#include "chestnut/engine/graphics/opengl/texture2d.hpp"

namespace chestnut::engine
{
    enum class ETextureMapType
    {
        DIFFUSE,
        SPECULAR,
        NORMAL,
        SHININESS
    };

    struct SMaterial
    {
        CTexture2D diffuse;
        CTexture2D specular;
        CTexture2D normal;
        CTexture2D shininess;
    };

} // namespace chestnut::engine

