#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/maths/rectangle.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace chestnut::engine
{
    struct SAnimation2DDefinition
    {
        std::string name;
        float duration = 0.f;
   
        // Sequence of indices identifying specific clipping rectangles for each animation frame
        // Index corresponds to a clipping rectangle in animation set
        // Indices can repeat in an animation of course, which simplifies the process of setting up an animation
        std::vector< unsigned int > vecFrameIndices;
    };

    struct SAnimation2DSet
    {
        //FIXME It can't only be the rectangle, you also need to know how it should be offset at the end
        // Clipping rectangles of animation keyframes in the spritesheet
        std::vector< SRectangle > vecKeyFrameClipRects;

        std::unordered_map< std::string, SAnimation2DDefinition > mapAnimNameToAnimData;
        // A default animation frame to be used when animation expires or isn't played at all (like T-pose in 3D graphics)
        unsigned int defaultAnimFrameIndex = 0;
    };

} // namespace chestnut::engine

