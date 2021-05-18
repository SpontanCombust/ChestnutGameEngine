#include "rendering_system.hpp"

#include "engine/globals.hpp"

namespace chestnut
{
    CRenderingSystem::CRenderingSystem()
    {
        CShaderProgram shader;
        mat4f projection = matMakeOrthographic<float>( 0.f, theWindow.getWidth(), theWindow.getHeight(), 0.f, 1.f, -1.f );

        shader = theResourceManager.loadShaderProgram( "../assets/shaders/sprite.vert", "../assets/shaders/sprite.frag" );
        m_spriteRenderer = new CSpriteRenderer( shader );

        m_spriteRenderer->bindShader();
        m_spriteRenderer->setViewMatrix( mat4f() );
        m_spriteRenderer->setProjectionMatrix( projection );


        shader = theResourceManager.loadShaderProgram( "../assets/shaders/coloredPolygon2D.vert", "../assets/shaders/coloredPolygon2D.frag" );
        m_polygonRenderer = new CColoredPolygon2DRenderer( shader );

        m_polygonRenderer->bindShader();
        m_polygonRenderer->setViewMatrix( mat4f() );
        m_polygonRenderer->setProjectionMatrix( projection );
        m_polygonRenderer->unbindShader();
    }

    CRenderingSystem::~CRenderingSystem() 
    {
        delete m_spriteRenderer;
        delete m_polygonRenderer;
    }

    void CRenderingSystem::submitComponents( CComponentBatch *batch ) 
    {
        SComponentSetSignature signature;

        signature = batch->getSignature();

        if( signature.includes<STransformComponent>() )
        {
            if( signature.includes<STextureComponent>() )
            {
                batch->getComponentsAppendToVec( m_vecTransformForTextureComps );
                batch->getComponentsAppendToVec( m_vecTextureComps );
            }
            if( signature.includes<SPolygonCanvasComponent>() )
            {
                batch->getComponentsAppendToVec( m_vecTransformForPolygonCanvasComps );
                batch->getComponentsAppendToVec( m_vecPolygonCanvasComps );
            }
        }
    }
        
    void CRenderingSystem::clearComponents() 
    {
        m_vecTransformForTextureComps.clear();
        m_vecTextureComps.clear();
        m_vecTransformForPolygonCanvasComps.clear();
        m_vecPolygonCanvasComps.clear();
    }

    void CRenderingSystem::update( uint32_t deltaTime ) 
    {
        STransformComponent *transfComp;
        STextureComponent *texComp;
        SPolygonCanvasComponent *polygonCanvasComp;
        size_t entityCount;

        m_spriteRenderer->clear();
        entityCount = m_vecTransformForTextureComps.size();
        for (size_t i = 0; i < entityCount; i++)
        {
            transfComp = m_vecTransformForTextureComps[i];
            texComp = m_vecTextureComps[i];

            m_spriteRenderer->submitSprite( texComp->texture, transfComp->position, texComp->origin, transfComp->scale, transfComp->rotation );
        }

        m_polygonRenderer->clear();
        entityCount = m_vecTransformForPolygonCanvasComps.size();
        for (size_t i = 0; i < entityCount; i++)
        {
            transfComp = m_vecTransformForPolygonCanvasComps[i];
            polygonCanvasComp = m_vecPolygonCanvasComps[i];

            for( const CColoredPolygon2D& polygon : polygonCanvasComp->vecPolygons )
            {
                m_polygonRenderer->submitPolygon( polygon, transfComp->position, polygonCanvasComp->origin, transfComp->scale, transfComp->rotation );
            }
        }
    }

    void CRenderingSystem::render()
    {
        theWindow.clear();
        
        renderTextures();
        renderColoredPolygons();

        theWindow.flipBuffer();
    }

    void CRenderingSystem::renderTextures()
    {
        m_spriteRenderer->bindShader();
        m_spriteRenderer->render();
        m_spriteRenderer->unbindShader();
    }

    void CRenderingSystem::renderColoredPolygons() 
    {
        m_polygonRenderer->bindShader();
        m_polygonRenderer->render();
        m_polygonRenderer->unbindShader();
    }

} // namespace chestnut

