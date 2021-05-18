#ifndef __CHESTNUT_POLYGON_CANVAS_COMPONENT_H__
#define __CHESTNUT_POLYGON_CANVAS_COMPONENT_H__

#include "../component.hpp"
#include "engine/graphics/colored_polygon2d.hpp"

#include <vector>

namespace chestnut
{
    struct SPolygonCanvasComponent : IComponent
    {
        std::vector< CColoredPolygon2D > vecPolygons;
        vec2f origin;

        SPolygonCanvasComponent() = default;
    };

} // namespace chestnut

#endif // __CHESTNUT_POLYGON_CANVAS_COMPONENT_H__