#ifndef __CHESTNUT_ENGINE_MODEL2D_COMPONENT_H__
#define __CHESTNUT_ENGINE_MODEL2D_COMPONENT_H__

#include "chestnut/engine/macros.hpp"
#include "../../maths/vector2.hpp"

namespace chestnut::engine
{
    // Component acting as a base for other visual components (e.g. texture)
    struct CHESTNUT_API CModel2DComponent
    {
        // Model is always a simple rectangle
        vec2f size;

        // Informs which point in the model is its 'point zero'
        // This can be for example the upper left corner or just the centre
        // Values should be normalized, clamped in range (0;1) where:
        //   x = 0 is left side, x = 1 is right side
        //   y = 0 is top side,  y = 1 is bottom side 
        // Defaults to the centre of model
        vec2f origin; 

        CModel2DComponent();
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_MODEL2D_COMPONENT_H__