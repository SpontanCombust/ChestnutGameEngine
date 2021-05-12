#ifndef __CHESTNUT_RENDERING_SYSTEM_H__
#define __CHESTNUT_RENDERING_SYSTEM_H__

#include "component_system.hpp"
#include "engine/graphics/sprite_renderer.hpp"
#include "../components/transform_component.hpp"
#include "../components/texture_component.hpp"

namespace chestnut
{
    class CRenderingSystem : public IComponentSystem
    {
    private:
        CSpriteRenderer *m_renderer;

        std::vector< STransformComponent * > m_vecTransformComps;
        std::vector< STextureComponent * > m_vecTextureComps;

    public:
        CRenderingSystem();
        ~CRenderingSystem();

        void submitComponents( CComponentBatch *batch ) override;
        void clearComponents() override;
        void update( uint32_t deltaTime ) override;
        void draw();

    private:
        void drawTextures();
    };

} // namespace chestnut

#endif // __CHESTNUT_RENDERING_SYSTEM_H__