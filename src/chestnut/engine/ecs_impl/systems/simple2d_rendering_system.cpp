#include "simple2d_rendering_system.hpp"

#include "../../main/engine.hpp"
#include "../../resources/resource_manager.hpp"
#include "../../maths/matrix4.hpp"
#include "../components/transform2d_component.hpp"
#include "../components/texture2d_component.hpp"
#include "../components/polygon2d_canvas_component.hpp"
#include "../../debug/log.hpp"

namespace chestnut
{
    CSimpled2DRenderingSystem::CSimpled2DRenderingSystem( CEngine& engine ) : IRenderingSystem( engine )
    {
        CShaderProgram shader;
        mat4f projection = matMakeOrthographic<float>( 0.f, getEngine().getWindow().getSizeWidth(), getEngine().getWindow().getSizeHeight(), 0.f, 1.f, -1.f );

        try
        {
            shader = CShaderProgram( CResourceManager::loadShaderProgramResource( "../assets/shaders/sprite.vert", "../assets/shaders/sprite.frag" ) );
            m_spriteRenderer.init( shader );
        }
        catch(const std::exception& e)
        {
            LOG_ERROR( e.what() );
        }

        m_spriteRenderer.bindShader();
        m_spriteRenderer.setViewMatrix( mat4f() );
        m_spriteRenderer.setProjectionMatrix( projection );

        try
        {
            shader = CShaderProgram( CResourceManager::loadShaderProgramResource( "../assets/shaders/coloredPolygon2D.vert", "../assets/shaders/coloredPolygon2D.frag" ) );
            m_polygonRenderer.init( shader );
        }
        catch(const std::exception& e)
        {
            LOG_ERROR( e.what() );   
        }
        
        m_polygonRenderer.bindShader();
        m_polygonRenderer.setViewMatrix( mat4f() );
        m_polygonRenderer.setProjectionMatrix( projection );
        m_polygonRenderer.unbindShader();



        m_textureQuery.entitySignCond = []( const ecs::CEntitySignature& sign )
        {
            return sign.has<CTransform2DComponent>() && sign.has<CTextureComponent>();
        };

        m_polygonQuery.entitySignCond = []( const ecs::CEntitySignature& sign )
        {
            return sign.has<CTransform2DComponent>() && sign.has<CPolygon2DCanvasComponent>();
        };
    }

    void CSimpled2DRenderingSystem::update( float deltaTime ) 
    {
        getEngine().getEntityWorld().queryEntities( m_textureQuery );

        m_spriteRenderer.clear();

        ecs::forEachEntityInQuery< CTransform2DComponent, CTextureComponent >( m_textureQuery,
        [this]( CTransform2DComponent& transform, CTextureComponent& texture )
        {
            m_spriteRenderer.submitSprite( texture.texture, transform.position, texture.origin, transform.scale, transform.rotation );
        });



        getEngine().getEntityWorld().queryEntities( m_polygonQuery );

        m_polygonRenderer.clear();

        ecs::forEachEntityInQuery< CTransform2DComponent, CPolygon2DCanvasComponent >( m_polygonQuery, 
        [this]( CTransform2DComponent& transform, CPolygon2DCanvasComponent& canvas )
        {
            for( const CColoredPolygon2D& polygon : canvas.vecPolygons )
            {
                m_polygonRenderer.submitPolygon( polygon, transform.position, transform.scale, transform.rotation );
            }
        });
    }

    void CSimpled2DRenderingSystem::render()
    {
        getEngine().getWindow().clear();
        
        renderTextures();
        renderColoredPolygons();

        getEngine().getWindow().flipBuffer();
    }

    void CSimpled2DRenderingSystem::renderTextures()
    {
        m_spriteRenderer.bindShader();
        m_spriteRenderer.render();
        m_spriteRenderer.unbindShader();
    }

    void CSimpled2DRenderingSystem::renderColoredPolygons() 
    {
        m_polygonRenderer.bindShader();
        m_polygonRenderer.render();
        m_polygonRenderer.unbindShader();
    }

} // namespace chestnut

