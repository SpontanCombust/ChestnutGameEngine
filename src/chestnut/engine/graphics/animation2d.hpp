#ifndef __CHESTNUT_ENGINE_ANIMATION2D_H__
#define __CHESTNUT_ENGINE_ANIMATION2D_H__

#include "chestnut/engine/macros.hpp"
#include "../maths/rectangle.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace chestnut::engine
{
    struct CHESTNUT_API SAnimationData2D
    {
        std::string name;
        float framesPerSec;
   
        // Sequence of indices identifying specific clipping rectangles for each animation frame
        // Index corresponds to a clipping rectangle in animation set
        // Indices can repeat in an animation of course, which simplifies the process of setting up an animation
        std::vector< unsigned int > vecFrameIndices;

        SAnimationData2D();
    };

    struct CHESTNUT_API SAnimationSet2D
    {
        // Clipping rectangles of animation keyframes in the spritesheet
        std::vector< SRectangle > vecKeyFrameClipRects;

        std::unordered_map< std::string, SAnimationData2D > mapAnimNameToAnimData;
        // A default animation frame to be used when animation expires or isn't played at all (like T-pose in 3D graphics)
        unsigned int defaultAnimFrameIndex;

        SAnimationSet2D();
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_ANIMATION2D_H__