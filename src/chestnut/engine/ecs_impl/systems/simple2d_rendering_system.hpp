#ifndef __CHESTNUT_ENGINE_SIMPLE2D_RENDERING_SYSTEM_H__
#define __CHESTNUT_ENGINE_SIMPLE2D_RENDERING_SYSTEM_H__

#include "../rendering_system.hpp"
#include "../../graphics/sprite_renderer.hpp"
#include "../../graphics/colored_polygon2d_renderer.hpp"
#include "../../graphics/text_renderer.hpp"

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

    class CSimple2DRenderingSystem : public IRenderingSystem
    {
    private:
        ecs::queryid_t m_textureQueryID;
        ecs::queryid_t m_layerTextureQueryID;
        ecs::queryid_t m_textureModelQueryID;
        ecs::queryid_t m_layerTextureModelQueryID;

        CSpriteRenderer m_spriteRenderer;
        CColoredPolygon2DRenderer m_polygonRenderer;
        CTextRenderer m_textRenderer;

        EDefaultRenderOrder m_defaultRenderOrder;


    public:
        CSimple2DRenderingSystem( CEngine& engine );
        ~CSimple2DRenderingSystem();

        void update( float deltaTime ) override;

        void render() override;


        CSpriteRenderer& getSpriteRenderer();

        CColoredPolygon2DRenderer& getColoredPolygonRenderer();

        CTextRenderer& getTextRenderer();


        void setDefaultRenderOrder( EDefaultRenderOrder order );
        EDefaultRenderOrder getDefaultRenderOrder() const;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_SIMPLE2D_RENDERING_SYSTEM_H__