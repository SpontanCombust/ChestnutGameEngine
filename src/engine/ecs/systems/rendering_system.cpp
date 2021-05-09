#include "rendering_system.hpp"

#include "../components/transform_component.hpp"
#include "../components/texture_component.hpp"
#include "engine/globals.hpp"

namespace chestnut
{
    CRenderingSystem::CRenderingSystem()
    {
        m_renderer = new CSpriteRenderer( theResourceManager.loadShaderProgram( "../assets/shaders/sprite.vert", "../assets/shaders/sprite.frag" ) );

        m_renderer->bindShader();
        m_renderer->setViewMatrix( mat4f() );
        m_renderer->setProjectionMatrix( matMakeOrthographic<float>( 0.f, theWindow.getWidth(), theWindow.getHeight(), 0.f, 1.f, -1.f ) );
        m_renderer->unbindShader();
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
        int entCount;
        std::vector< STransformComponent * > vecTransfComps;
        std::vector< STextureComponent * > vecTextureComps;

        m_renderer->clear();
        
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
                    m_renderer->submitSprite( texComp->texture, transfComp->position, transfComp->scale, transfComp->rotation );
                }
            }
        }
    }

    void CRenderingSystem::draw()
    {
        theWindow.clear();
        
        drawTextures();

        theWindow.flipBuffer();
    }

    void CRenderingSystem::drawTextures()
    {
        m_renderer->bindShader();
        m_renderer->render();
        m_renderer->unbindShader();
    }

} // namespace chestnut

