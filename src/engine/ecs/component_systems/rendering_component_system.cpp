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
                textureComp->texture.setScale( textureComp->scaleOffset + transformComp->scale );

                switch( textureComp->anchor )
                {
                    case ETextureAnchor::UPPER_LEFT:
                        textureComp->texture.setPosition( transformComp->position );
                        textureComp->texture.setRotationPoint( Vector2lf( 0.f, 0.f ) );
                        break;
                    case ETextureAnchor::UP:
                        textureComp->texture.setPosition( transformComp->position - Vector2f( textureComp->texture.getSize().x * 0.5f, 0.f ) );
                        textureComp->texture.setRotationPoint( Vector2lf( 0.5f, 0.f ) );
                        break;
                    case ETextureAnchor::UPPER_RIGHT:
                        textureComp->texture.setPosition( transformComp->position - Vector2f( textureComp->texture.getSize().x, 0.f ) );
                        textureComp->texture.setRotationPoint( Vector2lf( 1.f, 0.f ) );
                        break;
                    case ETextureAnchor::LEFT:
                        textureComp->texture.setPosition( transformComp->position - Vector2f( 0.f, textureComp->texture.getSize().y * 0.5f ) );
                        textureComp->texture.setRotationPoint( Vector2lf( 0.f, 0.5f ) );
                        break;
                    case ETextureAnchor::RIGHT:
                        textureComp->texture.setPosition( transformComp->position - Vector2f( textureComp->texture.getSize().x, textureComp->texture.getSize().y * 0.5f ) );
                        textureComp->texture.setRotationPoint( Vector2lf( 1.f, 0.5f ) );
                        break;
                    case ETextureAnchor::LOWER_LEFT:
                        textureComp->texture.setPosition( transformComp->position - Vector2f( 0.f, textureComp->texture.getSize().y ) );
                        textureComp->texture.setRotationPoint( Vector2lf( 0.f, 1.f ) );
                        break;
                    case ETextureAnchor::DOWN:
                        textureComp->texture.setPosition( transformComp->position - Vector2f( textureComp->texture.getSize().x * 0.5f, textureComp->texture.getSize().y ) );
                        textureComp->texture.setRotationPoint( Vector2lf( 0.5f, 1.f ) );
                        break;
                    case ETextureAnchor::LOWER_RIGHT:
                        textureComp->texture.setPosition( transformComp->position - textureComp->texture.getSize() );
                        textureComp->texture.setRotationPoint( Vector2lf( 1.f, 1.f ) );
                        break;
                    default:
                        textureComp->texture.setPosition( transformComp->position - textureComp->texture.getSize() * 0.5f );
                        textureComp->texture.setRotationPoint( Vector2lf( 0.5f, 0.5f ) );
                }

                textureComp->texture.setRotation( transformComp->rotation );
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

