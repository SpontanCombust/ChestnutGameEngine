#ifndef __CHESTNUT_RENDERING_SYSTEM_H__
#define __CHESTNUT_RENDERING_SYSTEM_H__

#include "component_system.hpp"
#include "../components/transform_component.hpp"
#include "../components/texture_component.hpp"

namespace chestnut
{
    class CRenderingSystem : public IComponentSystem
    {
    private:
        std::vector< CComponentBatch * > m_rendnerableBatches;

    public:
        void submitBatch( CComponentBatch *batch ) override;
        void clearBatches() override;
        void update( uint32_t deltaTime ) override;
        void draw() const;

    private:
        void transformTextures();
        void drawTextures() const;
    };

} // namespace chestnut

#endif // __CHESTNUT_RENDERING_SYSTEM_H__