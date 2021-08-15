#ifndef __CHESTNUT_RENDERING_SYSTEM_H__
#define __CHESTNUT_RENDERING_SYSTEM_H__

#include "../component_system.hpp"
#include "../components/transform_component.hpp"
#include "../components/texture_component.hpp"
#include "../components/polygon_canvas_component.hpp"
#include "../../graphics/sprite_renderer.hpp"
#include "../../graphics/colored_polygon2d_renderer.hpp"

namespace chestnut
{
    class CRenderingSystem : public IComponentSystem
    {
    private:
        ecs::SEntityQuery m_textureQuery;
        ecs::SEntityQuery m_polygonQuery;

        CSpriteRenderer m_spriteRenderer;
        CColoredPolygon2DRenderer m_polygonRenderer;

    public:
        CRenderingSystem();

        void initQueries() override;

        void update( uint32_t deltaTime ) override;

        void render();

    private:
        void renderTextures();
        void renderColoredPolygons();
    };

} // namespace chestnut

#endif // __CHESTNUT_RENDERING_SYSTEM_H__