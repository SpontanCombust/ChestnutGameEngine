#include "rendering_system.hpp"

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

    void CRenderingSystem::submitComponents( CComponentBatch *batch ) 
    {
        SComponentSetSignature signature;

        signature = batch->getSignature();

        if( signature.includes<STransformComponent>() && signature.includes<STextureComponent>() )
        {
            batch->getComponentsAppendToVec( m_vecTransformComps );
            batch->getComponentsAppendToVec( m_vecTextureComps );
        }
    }
        
    void CRenderingSystem::clearComponents() 
    {
        m_vecTransformComps.clear();
        m_vecTextureComps.clear();
    }

    void CRenderingSystem::update( uint32_t deltaTime ) 
    {
        STransformComponent *transfComp;
        STextureComponent *texComp;

        m_renderer->clear();
        
        size_t entityCount = m_vecTransformComps.size();
        for (size_t i = 0; i < entityCount; i++)
        {
            transfComp = m_vecTransformComps[i];
            texComp = m_vecTextureComps[i];

            m_renderer->submitSprite( texComp->texture, texComp->origin, transfComp->position, transfComp->scale, transfComp->rotation );
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

