#include "simple2d_rendering_system.hpp"

#include "../../main/engine.hpp"
#include "../../resources/resource_manager.hpp"
#include "../../maths/matrix4.hpp"
#include "../../maths/vector_cast.hpp"
#include "../components/model2d_component.hpp"
#include "../components/transform2d_component.hpp"
#include "../components/texture2d_component.hpp"
#include "../../debug/log.hpp"

namespace chestnut::engine
{
    CSimple2DRenderingSystem::CSimple2DRenderingSystem( CEngine& engine ) : IRenderingSystem( engine )
    {
        CShaderProgram shader;

        try
        {
            shader = CShaderProgram( CResourceManager::loadOrGetShaderProgramResource( "../assets/shaders/sprite.vert", "../assets/shaders/sprite.frag" ) );
            m_spriteRenderer.init( shader );
        }
        catch(const std::exception& e)
        {
            LOG_ERROR( e.what() );
        }

        try
        {
            shader = CShaderProgram( CResourceManager::loadOrGetShaderProgramResource( "../assets/shaders/coloredPolygon2D.vert", "../assets/shaders/coloredPolygon2D.frag" ) );
            m_polygonRenderer.init( shader );
        }
        catch(const std::exception& e)
        {
            LOG_ERROR( e.what() );   
        }
        
        try
        {
            shader = CShaderProgram( CResourceManager::loadOrGetShaderProgramResource( "../assets/shaders/text.vert", "../assets/shaders/text.frag" ) );
            m_textRenderer.init( shader );
        }
        catch(const std::exception& e)
        {
            LOG_ERROR( e.what() );  
        }


        m_textureWithModelQueryID = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CModel2DComponent, CTransform2DComponent, CTexture2DComponent  >(),
            ecs::makeEntitySignature()
        );

        m_textureWithoutModelQueryID = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CTransform2DComponent, CTexture2DComponent >(),
            ecs::makeEntitySignature< CModel2DComponent >()
        );
    }

    CSimple2DRenderingSystem::~CSimple2DRenderingSystem() 
    {
        getEngine().getEntityWorld().destroyQuery( m_textureWithModelQueryID );
    }

    void CSimple2DRenderingSystem::update( float deltaTime ) 
    {
        m_spriteRenderer.clear();


        const ecs::CEntityQuery* query;

        query = getEngine().getEntityWorld().queryEntities( m_textureWithModelQueryID );

        query->forEachEntityWith< CModel2DComponent, CTransform2DComponent, CTexture2DComponent >(
            [this]( CModel2DComponent& model, CTransform2DComponent& transform, CTexture2DComponent& texture )
            {
                vec2f adjustScale;

                switch( texture.adjust )
                {
                case ETexture2DToModel2DAdjust::SCALED:
                    adjustScale = model.size / vecCastType<float>( texture.texture.getSize() );
                    adjustScale = vec2f( std::min( adjustScale.x, adjustScale.y ) );
                    break;

                case ETexture2DToModel2DAdjust::SPANNED:
                    adjustScale = model.size / vecCastType<float>( texture.texture.getSize() );
                    break;
                
                case ETexture2DToModel2DAdjust::ZOOMED:
                    adjustScale = model.size / vecCastType<float>( texture.texture.getSize() );
                    adjustScale = vec2f( std::max( adjustScale.x, adjustScale.y ) );
                    break;

                default:
                    adjustScale = vec2f( 1.f );
                }

                m_spriteRenderer.submitSprite( texture.texture, transform.position, model.origin, adjustScale * transform.scale, transform.rotation );
            }
        );


        query = getEngine().getEntityWorld().queryEntities( m_textureWithoutModelQueryID );

        query->forEachEntityWith< CTransform2DComponent, CTexture2DComponent >(
            [this]( CTransform2DComponent& transform, CTexture2DComponent& texture )
            {
                m_spriteRenderer.submitSprite( texture.texture, transform.position, vec2f{ 0.f }, transform.scale, transform.rotation );
            }
        );
    }

    void CSimple2DRenderingSystem::render()
    {
        getEngine().getWindow().clear();
        
        m_spriteRenderer.bindShader();
        m_spriteRenderer.setViewMatrix( mat4f() );
        m_spriteRenderer.setProjectionMatrix( matMakeOrthographic<float>( 0.f, getEngine().getWindow().getSizeWidth(), getEngine().getWindow().getSizeHeight(), 0.f, -1.f, 1.f ) );
        glFinish(); // prevent CPU getting too hasty with sending requests to GPU
        m_spriteRenderer.render( getEngine().getWindow().getFramebuffer() );
        m_spriteRenderer.unbindShader();

        getEngine().getWindow().flipBuffer();
    }




    CSpriteRenderer& CSimple2DRenderingSystem::getSpriteRenderer() 
    {
        return m_spriteRenderer;
    }

    CColoredPolygon2DRenderer& CSimple2DRenderingSystem::getColoredPolygonRenderer() 
    {
        return m_polygonRenderer;
    }

    CTextRenderer& CSimple2DRenderingSystem::getTextRenderer() 
    {
        return m_textRenderer;
    }

} // namespace chestnut::engine

