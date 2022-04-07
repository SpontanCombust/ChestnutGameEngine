#ifndef __CHESTNUT_ENGINE_MATERIAL_H__
#define __CHESTNUT_ENGINE_MATERIAL_H__

#include "opengl/texture2d.hpp"

namespace chestnut::engine
{
    enum class ETextureMapType
    {
        DIFFUSE,
        SPECULAR,
        NORMAL
    };

    struct SMaterial
    {
        CTexture2D diffuse;
        CTexture2D specular;
        CTexture2D normal;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_MATERIAL_H__