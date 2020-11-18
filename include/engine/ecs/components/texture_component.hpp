#ifndef __CHESTNUT_TEXTURE_COMPONENT_H__
#define __CHESTNUT_TEXTURE_COMPONENT_H__

#include "engine/ecs/component.hpp"
#include "engine/graphics/texture.hpp"

namespace chestnut
{
    //TODO add some properties describing how the texture should be anchored to the entity (offset, rot center etc.)
    struct STextureComponent : IComponent
    {
        CTexture *texture;

        //TODO create "missing texture" for default constructor ASAP
        STextureComponent();
        STextureComponent( CTexture *textureInstance );
    };

} // namespace chestnut 


#endif // __CHESTNUT_TEXTURE_COMPONENT_H__