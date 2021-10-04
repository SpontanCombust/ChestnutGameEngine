#ifndef __CHESTNUT_ENGINE_POLYGON2D_CANVAS_COMPONENT_H__
#define __CHESTNUT_ENGINE_POLYGON2D_CANVAS_COMPONENT_H__

#include "../../graphics/colored_polygon2d.hpp"

#include <chestnut/ecs/component.hpp>

#include <vector>

namespace chestnut::engine
{
    struct CPolygon2DCanvasComponent : public ecs::CComponent
    {
        std::vector< SColoredPolygon2D > vecPolygons;

        CPolygon2DCanvasComponent() = default;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_POLYGON2D_CANVAS_COMPONENT_H__