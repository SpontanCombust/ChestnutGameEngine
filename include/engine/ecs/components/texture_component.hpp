#ifndef __CHESTNUT_TEXTURE_COMPONENT_H__
#define __CHESTNUT_TEXTURE_COMPONENT_H__

#include "engine/ecs/component.hpp"
#include "engine/graphics/texture.hpp"

namespace chestnut
{
    struct STextureComponent : IComponent
    {
        CTexture *texture;

        STextureComponent() = delete;
        STextureComponent( CTexture *textureInstance );

        static const std::string getTypeStringStatic();
        inline virtual const std::string getTypeString() override { return getTypeStringStatic(); };
    };

} // namespace chestnut 


#endif // __CHESTNUT_TEXTURE_COMPONENT_H__