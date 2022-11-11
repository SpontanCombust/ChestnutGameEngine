#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/ecs_impl/rendering_system.hpp"
#include "chestnut/engine/graphics/renderers/sprite_renderer.hpp"
#include "chestnut/engine/graphics/renderers/colored_polygon2d_renderer.hpp"
#include "chestnut/engine/graphics/renderers/text_renderer.hpp"
#include "chestnut/engine/graphics/camera2d.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut::engine
{
    // Enum that tells the simple2D rendering system how it should handle ordering objects
    // when they don't have render layer data or are on the same layer
    enum class EDefaultRenderOrder
    {
        TOP_TO_BOTTOM,
        BOTTOM_TO_TOP,
        LEFT_TO_RIGHT,
        RIGHT_TO_LEFT
    };

    class CHESTNUT_API CSimple2DRenderingSystem : public IRenderingSystem
    {
    private:
        ecs::CEntityQuery *m_spriteQuery;
        ecs::CEntityQuery *m_layerSpriteQuery;
        ecs::CEntityQuery *m_spriteModelQuery;
        ecs::CEntityQuery *m_layerSpriteModelQuery;

        CSpriteRenderer m_spriteRenderer;
        CColoredPolygon2DRenderer m_polygonRenderer;
        CTextRenderer m_textRenderer;

        EDefaultRenderOrder m_defaultRenderOrder;

        CCamera2D m_camera;


    public:
        CSimple2DRenderingSystem() = default;
        CSimple2DRenderingSystem(systempriority_t priority);
        ~CSimple2DRenderingSystem();


        void render() override;


        CSpriteRenderer& getSpriteRenderer();

        CColoredPolygon2DRenderer& getColoredPolygonRenderer();

        CTextRenderer& getTextRenderer();


        void setDefaultRenderOrder( EDefaultRenderOrder order );
        EDefaultRenderOrder getDefaultRenderOrder() const;


        const CCamera2D& getCamera() const;
        CCamera2D& getCamera();

    private:
        void updateQueries();
    };

} // namespace chestnut::engine

