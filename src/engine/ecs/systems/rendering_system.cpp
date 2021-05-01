#include "rendering_system.hpp"

#include "engine/maths/angles.hpp"
#include "engine/misc/tindex.hpp"
#include "engine/globals.hpp"

#include <cassert>
#include <algorithm>

namespace chestnut
{
    CRenderingSystem::CRenderingSystem()
    {
        m_spriteShader = theResourceManager.loadShaderProgram( "../assets/shaders/sprite.vert", "../assets/shaders/sprite.frag" );
        assert( m_spriteShader.isValid() );

        m_renderer = new CSpriteRenderer( m_spriteShader );
        m_renderer->setShaderVariableNames( "aPos", "aTexCoord", "uModel", "uView", "uProjection", "uTexClip" );
    }

    CRenderingSystem::~CRenderingSystem() 
    {
        delete m_renderer;
    }

    void CRenderingSystem::submitBatch( CComponentBatch *batch ) 
    {
        SComponentSetSignature signature;

        signature = batch->getSignature();

        if( signature.includes<STransformComponent>() && signature.includes<STextureComponent>() )
        {
            m_renderableBatches.push_back( batch );
        }
    }
        
    void CRenderingSystem::clearBatches() 
    {
        m_renderableBatches.clear();
    }

    void CRenderingSystem::update( uint32_t deltaTime ) 
    {
        /* NOP */
    }

    void CRenderingSystem::draw()
    {
        theWindow.clear();
        
        drawTextures();

        theWindow.flipBuffer();
    }

    void CRenderingSystem::drawTextures()
    {
        int entCount;
        std::vector< STransformComponent * > vecTransfComps;
        std::vector< STextureComponent * > vecTextureComps;

        m_renderer->setViewMatrix( mat4f() );
        m_renderer->setProjectionMatrix( matMakeOrthographic<float>( 0.f, theWindow.getWidth(), theWindow.getHeight(), 0.f, 1.f, -1.f ) );
        
        for( CComponentBatch *renderBatch : m_renderableBatches )
        {
            entCount = renderBatch->getEntityCount();
            vecTransfComps = renderBatch->getComponents<STransformComponent>();
            vecTextureComps = renderBatch->getComponents<STextureComponent>();

            STransformComponent *transfComp;
            STextureComponent *texComp;
            for (int i = 0; i < entCount; i++)
            {
                transfComp = vecTransfComps[i];
                texComp = vecTextureComps[i];

                if( texComp->texture.isValid() )
                {
                    m_renderer->renderSprite( texComp->texture, transfComp->position, transfComp->scale, transfComp->rotation );
                }
            }
        }
    }

} // namespace chestnut

