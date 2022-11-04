#pragma once


#include "chestnut/engine/macros.hpp"
#include "../../resources/mesh_data_resource.hpp"

#include <type_traits>


namespace chestnut::engine
{
    struct SHeightmap
    {
        float *values; // height values
        vec2i size; // size of the heightmap
    };

    // uses red channel to yield height values
    // these values are then normalized to the range [0, 1] and scaled using valueScale
    tl::expected<std::shared_ptr<SHeightmap>, const char *> 
    CHESTNUT_API
    heightmapFromFile(const char *path, float valueScale);

    // heightmap - heightmap data
    // dstSize - size in width and depth of the resulting mesh
    // valueScale - scale applied to heightmap's values after they are clamped to srcMin and srcMax 
    tl::expected<std::shared_ptr<CMeshDataResource>, const char *> 
    CHESTNUT_API
    meshDataFromHeightmap(const SHeightmap &heightmap, vec2f dstSize, float valueScale = 1.0f);
    
} // namespace chestnut::engine

