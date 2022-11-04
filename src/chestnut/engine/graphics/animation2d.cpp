#include "chestnut/engine/graphics/animation2d.hpp"

namespace chestnut::engine
{    
    SAnimationData2D::SAnimationData2D() 
    {
        framesPerSec = 1.f;
    }

    SAnimationSet2D::SAnimationSet2D() 
    {
        defaultAnimFrameIndex = 0;
    }

} // namespace chestnut::engine
