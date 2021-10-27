#ifndef __CHESTNUT_ENGINE_TEXTURE2D_COMPONENT_H__
#define __CHESTNUT_ENGINE_TEXTURE2D_COMPONENT_H__

#include "../../maths/vector2.hpp"
#include "../../graphics/texture2d.hpp"

namespace chestnut::engine
{
    enum class EModel2DTextureAdjust
    {
        NONE, // texture doesn't adjust to the model
        SCALED, // scale up/down keeping the aspect ratio to fit inside the model
        SPANNED, // scale up/down without keeping the aspect ratio to fit the entire surface area of the model 
        ZOOMED // scale up/down keeping the aspect ratio to fit the entire surface area of the model and possibly going beyond the shape
    };

    struct CTexture2DComponent
    {
        CTexture2D texture;
        EModel2DTextureAdjust adjust;

        CTexture2DComponent();
    };

} // namespace chestnut::engine 

#endif // __CHESTNUT_ENGINE_TEXTURE2D_COMPONENT_H__