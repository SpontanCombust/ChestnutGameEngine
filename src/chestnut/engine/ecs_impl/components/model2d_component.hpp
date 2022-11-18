#pragma once


#include "chestnut/engine/maths/vector2.hpp"

namespace chestnut::engine
{
    // Component acting as a base for other visual components (e.g. texture)
    struct CModel2DComponent
    {
        // Model is always a simple rectangle
        vec2f size;

        // Informs which point in the model is its 'point zero'
        // This can be for example the upper left corner or just the centre
        // Values should be normalized, clamped in range (0;1) where:
        //   x = 0 is left side, x = 1 is right side
        //   y = 0 is top side,  y = 1 is bottom side 
        // Defaults to the centre of model
        vec2f origin { 0.5f, 0.5f };
    };

} // namespace chestnut::engine
