#ifndef __CHESTNUT_RENDERING_SYSTEM_H__
#define __CHESTNUT_RENDERING_SYSTEM_H__

#include "component_system.hpp"
#include "../components/transform_component.hpp"
#include "../components/texture_component.hpp"
#include "engine/graphics/sprite_renderer.hpp"
#include "../components/polygon_canvas_component.hpp"
#include "engine/graphics/colored_polygon2d_renderer.hpp"

namespace chestnut
{
    class CRenderingSystem : public IComponentSystem
    {
    private:
        CSpriteRenderer *m_spriteRenderer;
        CColoredPolygon2DRenderer *m_polygonRenderer;

        std::vector< STransformComponent * > m_vecTransformForTextureComps;
        std::vector< STextureComponent * > m_vecTextureComps;
        std::vector< STransformComponent * > m_vecTransformForPolygonCanvasComps;
        std::vector< SPolygonCanvasComponent * > m_vecPolygonCanvasComps;

    public:
        CRenderingSystem();
        ~CRenderingSystem();

        void submitComponents( CComponentBatch *batch ) override;
        void clearComponents() override;
        void update( uint32_t deltaTime ) override;
        void render();

    private:
        void renderTextures();
        void renderColoredPolygons();
    };

} // namespace chestnut

#endif // __CHESTNUT_RENDERING_SYSTEM_H__