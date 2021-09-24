#ifndef __CHESTNUT_ENGINE_SIMPLE2D_RENDERING_SYSTEM_H__
#define __CHESTNUT_ENGINE_SIMPLE2D_RENDERING_SYSTEM_H__

#include "../rendering_system.hpp"
#include "../../graphics/sprite_renderer.hpp"
#include "../../graphics/colored_polygon2d_renderer.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut
{
    class CSimpled2DRenderingSystem : public IRenderingSystem
    {
    private:
        ecs::SEntityQuery m_textureQuery;
        ecs::SEntityQuery m_polygonQuery;

        CSpriteRenderer m_spriteRenderer;
        CColoredPolygon2DRenderer m_polygonRenderer;

    public:
        CSimpled2DRenderingSystem( CEngine& engine );

        void update( float deltaTime ) override;

        void render() override;

    private:
        void renderTextures();
        void renderColoredPolygons();
    };

} // namespace chestnut

#endif // __CHESTNUT_ENGINE_SIMPLE2D_RENDERING_SYSTEM_H__