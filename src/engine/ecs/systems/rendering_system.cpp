#include "rendering_system.hpp"

#include "../../resources/resource_manager.hpp"
#include "../../maths/matrix4.hpp"

namespace chestnut
{
    CRenderingSystem::CRenderingSystem( CEngine& engine ) : ISystem( engine )
    {
        CShaderProgram shader;
        mat4f projection = matMakeOrthographic<float>( 0.f, getEngine().getWindow().getWidth(), getEngine().getWindow().getHeight(), 0.f, 1.f, -1.f );

        shader = CResourceManager::loadShaderProgramResource( "../assets/shaders/sprite.vert", "../assets/shaders/sprite.frag" );
        m_spriteRenderer.init( shader );

        m_spriteRenderer.bindShader();
        m_spriteRenderer.setViewMatrix( mat4f() );
        m_spriteRenderer.setProjectionMatrix( projection );


        shader = CResourceManager::loadShaderProgramResource( "../assets/shaders/coloredPolygon2D.vert", "../assets/shaders/coloredPolygon2D.frag" );
        m_polygonRenderer.init( shader );

        m_polygonRenderer.bindShader();
        m_polygonRenderer.setViewMatrix( mat4f() );
        m_polygonRenderer.setProjectionMatrix( projection );
        m_polygonRenderer.unbindShader();



        m_textureQuery.entitySignCond = []( const ecs::CEntitySignature& sign )
        {
            return sign.has<CTransformComponent>() && sign.has<CTextureComponent>();
        };

        m_polygonQuery.entitySignCond = []( const ecs::CEntitySignature& sign )
        {
            return sign.has<CTransformComponent>() && sign.has<CPolygonCanvasComponent>();
        };
    }

    void CRenderingSystem::update( uint32_t deltaTime ) 
    {
        getEngine().getEntityWorld().queryEntities( m_textureQuery );

        m_spriteRenderer.clear();

        ecs::forEachEntityInQuery< CTransformComponent, CTextureComponent >( m_textureQuery,
        [this]( CTransformComponent& transform, CTextureComponent& texture )
        {
            m_spriteRenderer.submitSprite( texture.texture, transform.position, texture.origin, transform.scale, transform.rotation );
        });



        getEngine().getEntityWorld().queryEntities( m_polygonQuery );

        m_polygonRenderer.clear();

        ecs::forEachEntityInQuery< CTransformComponent, CPolygonCanvasComponent >( m_polygonQuery, 
        [this]( CTransformComponent& transform, CPolygonCanvasComponent& canvas )
        {
            for( const CColoredPolygon2D& polygon : canvas.vecPolygons )
            {
                m_polygonRenderer.submitPolygon( polygon, transform.position, transform.scale, transform.rotation );
            }
        });
    }

    void CRenderingSystem::render()
    {
        getEngine().getWindow().clear();
        
        renderTextures();
        renderColoredPolygons();

        getEngine().getWindow().flipBuffer();
    }

    void CRenderingSystem::renderTextures()
    {
        m_spriteRenderer.bindShader();
        m_spriteRenderer.render();
        m_spriteRenderer.unbindShader();
    }

    void CRenderingSystem::renderColoredPolygons() 
    {
        m_polygonRenderer.bindShader();
        m_polygonRenderer.render();
        m_polygonRenderer.unbindShader();
    }

} // namespace chestnut

