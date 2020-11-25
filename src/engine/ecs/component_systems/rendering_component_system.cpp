#include "engine/ecs/component_systems/rendering_component_system.hpp"

#include "engine/maths/angles.hpp"
#include "engine/graphics/renderer.hpp"

#include <algorithm>

namespace chestnut
{
    bool CRenderingComponentSystem::needsAnyOfComponents( const std::forward_list< std::type_index >& compTypeIndexes )
    {
        return std::any_of( compTypeIndexes.begin(), compTypeIndexes.end(),
            []( std::type_index tindex )
            { 
                return tindex == std::type_index( typeid( STransformComponent ) )
                    || tindex == std::type_index( typeid( STextureComponent ) );
            }
        );
    }
    
    void CRenderingComponentSystem::fetchComponents( const CComponentDatabase& dbRef )
    {
        dbRef.fillComponentMapOfType( m_transformCompMap );
        dbRef.fillComponentMapOfType( m_textureCompMap );
    }
    
    void CRenderingComponentSystem::update( float deltaTime ) 
    {
        CRenderer::renderClear();

        transformTextures();
        drawTextures();

        CRenderer::renderPresent();
    }


    void CRenderingComponentSystem::transformTextures() 
    {
        guid_t guid;
        STransformComponent *transformComp;
        STextureComponent *textureComp;
        for( auto &pair : m_transformCompMap )
        {
            guid = pair.first;
            transformComp = pair.second;

            textureComp = m_textureCompMap[guid];
            if( textureComp != nullptr )
            {
                textureComp->texture.setPosition( transformComp->position );
                textureComp->texture.setRotation( transformComp->rotation );
                textureComp->texture.setScale( transformComp->scale );
            }
        }
    }

    void CRenderingComponentSystem::drawTextures() const
    {
        STextureComponent *textureComp;
        for( const auto &pair : m_textureCompMap )
        {
            textureComp = pair.second;
            if( textureComp != nullptr )
            {
                CRenderer::renderTexture( textureComp->texture );
            }
        }
    }

} // namespace chestnut

