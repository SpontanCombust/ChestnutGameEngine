#ifndef __CHESTNUT_TEXTURE_COMPONENT_H__
#define __CHESTNUT_TEXTURE_COMPONENT_H__

#include "engine/ecs/component.hpp"
#include "engine/graphics/texture.hpp"

namespace chestnut
{
    struct STextureComponent : SComponent
    {
        CTexture *texture;

        STextureComponent();

        static const std::string getTypeStatic();
        inline virtual const std::string getType() { return getTypeStatic(); };
    };

} // namespace chestnut 


#endif // __CHESTNUT_TEXTURE_COMPONENT_H__