#ifndef __CHESTNUT_RENDERING_SYSTEM_H__
#define __CHESTNUT_RENDERING_SYSTEM_H__

#include "component_system.hpp"
#include "../components/transform_component.hpp"
#include "../components/texture_component.hpp"
#include "engine/graphics/shader_program.hpp"
#include "engine/graphics/sprite_renderer.hpp"

namespace chestnut
{
    class CRenderingSystem : public IComponentSystem
    {
    private:
        CShaderProgram m_spriteShader;
        CSpriteRenderer *m_renderer;

        std::vector< CComponentBatch * > m_renderableBatches;

    public:
        CRenderingSystem();
        ~CRenderingSystem();

        void submitBatch( CComponentBatch *batch ) override;
        void clearBatches() override;
        void update( uint32_t deltaTime ) override;
        void draw();

    private:
        void drawTextures();
    };

} // namespace chestnut

#endif // __CHESTNUT_RENDERING_SYSTEM_H__