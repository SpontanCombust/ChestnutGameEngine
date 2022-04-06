#ifndef __CHESTNUT_ENGINE_MATERIAL_H__
#define __CHESTNUT_ENGINE_MATERIAL_H__

#include "../resources/texture2d_resource.hpp"

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
        std::shared_ptr<CTexture2DResource> diffuse;
        std::shared_ptr<CTexture2DResource> specular;
        std::shared_ptr<CTexture2DResource> normal;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_MATERIAL_H__