#ifndef __CHESTNUT_RENDERING_COMPONENT_SYSTEM_H__
#define __CHESTNUT_RENDERING_COMPONENT_SYSTEM_H__

#include "engine/ecs/component_system.hpp"
#include "engine/ecs/components/transform_component.hpp"
#include "engine/ecs/components/texture_component.hpp"

namespace chestnut
{
    class CRenderingComponentSystem : public IComponentSystem
    {
    private:
        std::unordered_map< uint64_t, STransformComponent* > m_transformCompMap;
        std::unordered_map< uint64_t, STextureComponent* > m_textureCompMap;

    public:
        virtual bool needsComponents( const std::vector< std::string > compTypeStrings ) override;
        virtual void fetchComponents( const CComponentDatabase& dbRef ) override;
        virtual void manageCurrentComponents() override;

    private:
        void transformTextures();
        void drawTextures() const;
    };

} // namespace chestnut

#endif // __CHESTNUT_RENDERING_COMPONENT_SYSTEM_H__