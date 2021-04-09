#include "rendering_system.hpp"

#include "engine/maths/angles.hpp"
#include "engine/graphics/renderer.hpp"
#include "engine/misc/tindex.hpp"

#include <algorithm>

namespace chestnut
{
    void CRenderingSystem::submitBatch( CComponentBatch *batch ) 
    {
        SComponentSetSignature signature;

        signature = batch->getSignature();

        if( signature.includes<STransformComponent>() && signature.includes<STextureComponent>() )
        {
            m_rendnerableBatches.push_back( batch );
        }
    }
        
    void CRenderingSystem::clearBatches() 
    {
        m_rendnerableBatches.clear();
    }

    void CRenderingSystem::update( float deltaTime ) 
    {
        transformTextures();
    }

    void CRenderingSystem::draw() const
    {
        CRenderer::renderClear();
        
        drawTextures();

        CRenderer::renderPresent();
    }

    void CRenderingSystem::transformTextures() 
    {
        std::vector< STransformComponent * > vecTransfComps;
        std::vector< STextureComponent * > vecTextureComps;
        STransformComponent *transfComp;
        STextureComponent *textureComp;

        for( CComponentBatch *renderBatch : m_rendnerableBatches )
        {
            vecTransfComps = renderBatch->getComponents<STransformComponent>();
            vecTextureComps = renderBatch->getComponents<STextureComponent>();

            for( int i = 0; i < renderBatch->getEntityCount(); i++ )
            {
                transfComp = vecTransfComps[i];
                textureComp = vecTextureComps[i];

                textureComp->texture.setScale( textureComp->scaleOffset + transfComp->scale );

                switch( textureComp->anchor )
                {
                    case ETextureAnchor::UPPER_LEFT:
                        textureComp->texture.setPosition( transfComp->position );
                        textureComp->texture.setRotationPoint( Vector2lf( 0.f, 0.f ) );
                        break;
                    case ETextureAnchor::UP:
                        textureComp->texture.setPosition( transfComp->position - Vector2f( textureComp->texture.getSize().x * 0.5f, 0.f ) );
                        textureComp->texture.setRotationPoint( Vector2lf( 0.5f, 0.f ) );
                        break;
                    case ETextureAnchor::UPPER_RIGHT:
                        textureComp->texture.setPosition( transfComp->position - Vector2f( textureComp->texture.getSize().x, 0.f ) );
                        textureComp->texture.setRotationPoint( Vector2lf( 1.f, 0.f ) );
                        break;
                    case ETextureAnchor::LEFT:
                        textureComp->texture.setPosition( transfComp->position - Vector2f( 0.f, textureComp->texture.getSize().y * 0.5f ) );
                        textureComp->texture.setRotationPoint( Vector2lf( 0.f, 0.5f ) );
                        break;
                    case ETextureAnchor::RIGHT:
                        textureComp->texture.setPosition( transfComp->position - Vector2f( textureComp->texture.getSize().x, textureComp->texture.getSize().y * 0.5f ) );
                        textureComp->texture.setRotationPoint( Vector2lf( 1.f, 0.5f ) );
                        break;
                    case ETextureAnchor::LOWER_LEFT:
                        textureComp->texture.setPosition( transfComp->position - Vector2f( 0.f, textureComp->texture.getSize().y ) );
                        textureComp->texture.setRotationPoint( Vector2lf( 0.f, 1.f ) );
                        break;
                    case ETextureAnchor::DOWN:
                        textureComp->texture.setPosition( transfComp->position - Vector2f( textureComp->texture.getSize().x * 0.5f, textureComp->texture.getSize().y ) );
                        textureComp->texture.setRotationPoint( Vector2lf( 0.5f, 1.f ) );
                        break;
                    case ETextureAnchor::LOWER_RIGHT:
                        textureComp->texture.setPosition( transfComp->position - textureComp->texture.getSize() );
                        textureComp->texture.setRotationPoint( Vector2lf( 1.f, 1.f ) );
                        break;
                    default:
                        textureComp->texture.setPosition( transfComp->position - textureComp->texture.getSize() * 0.5f );
                        textureComp->texture.setRotationPoint( Vector2lf( 0.5f, 0.5f ) );
                }

                textureComp->texture.setRotation( transfComp->rotation );
            }
        }
    }

    void CRenderingSystem::drawTextures() const
    {
        std::vector< STextureComponent * > vecTextureComps;
        
        for( CComponentBatch *renderBatch : m_rendnerableBatches )
        {
            vecTextureComps = renderBatch->getComponents<STextureComponent>();
            for( STextureComponent *textureComp : vecTextureComps )
            {
                CRenderer::renderTexture( textureComp->texture );
            }
        }
    }

} // namespace chestnut

