#ifndef __CHESTNUT_RENDERING_SYSTEM_H__
#define __CHESTNUT_RENDERING_SYSTEM_H__

#include "../system_interfaces/updatable_system.hpp"
#include "../system_interfaces/component_fetching_system.hpp"
#include "../components/transform_component.hpp"
#include "../components/texture_component.hpp"

namespace chestnut
{
    class CRenderingSystem : public IUpdatableSystem, public IComponentFetchingSystem
    {
    private:
        std::unordered_map< guid_t, STransformComponent* > m_transformCompMap;
        std::unordered_map< guid_t, STextureComponent* > m_textureCompMap;

    public:
        bool needsAnyOfComponents( const std::list< std::type_index >& compTypeIndexes ) override;
        void fetchComponents( const CComponentDatabase& dbRef ) override;
        void update( float deltaTime ) override;
        void draw() const;

    private:
        void transformTextures();
        void drawTextures() const;
    };

} // namespace chestnut

#endif // __CHESTNUT_RENDERING_SYSTEM_H__