#ifndef __CHESTNUT_POLYGON2D_CANVAS_COMPONENT_H__
#define __CHESTNUT_POLYGON2D_CANVAS_COMPONENT_H__

#include "../../graphics/colored_polygon2d.hpp"

#include <chestnut/ecs/component.hpp>

#include <vector>

namespace chestnut
{
    struct CPolygon2DCanvasComponent : public ecs::CComponent
    {
        std::vector< CColoredPolygon2D > vecPolygons;

        CPolygon2DCanvasComponent() = default;
    };

} // namespace chestnut

#endif // __CHESTNUT_POLYGON2D_CANVAS_COMPONENT_H__