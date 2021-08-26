#ifndef __CHESTNUT_POLYGON_CANVAS_COMPONENT_H__
#define __CHESTNUT_POLYGON_CANVAS_COMPONENT_H__

#include "../../graphics/colored_polygon2d.hpp"

#include <chestnut/ecs/component.hpp>

#include <vector>

namespace chestnut
{
    struct CPolygonCanvasComponent : public ecs::CComponent
    {
        std::vector< CColoredPolygon2D > vecPolygons;

        CPolygonCanvasComponent() = default;
    };

} // namespace chestnut

#endif // __CHESTNUT_POLYGON_CANVAS_COMPONENT_H__