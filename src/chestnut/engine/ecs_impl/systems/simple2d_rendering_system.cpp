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
    CSimpled2DRenderingSystem::CSimpled2DRenderingSystem( CEngine& engine ) : IRenderingSystem( engine )
    {
        CShaderProgram shader;
        mat4f projection = matMakeOrthographic<float>( 0.f, getEngine().getWindow().getSizeWidth(), getEngine().getWindow().getSizeHeight(), 0.f, 1.f, -1.f );

        try
        {
            shader = CShaderProgram( CResourceManager::loadOrGetShaderProgramResource( "../assets/shaders/sprite.vert", "../assets/shaders/sprite.frag" ) );
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
            shader = CShaderProgram( CResourceManager::loadOrGetShaderProgramResource( "../assets/shaders/coloredPolygon2D.vert", "../assets/shaders/coloredPolygon2D.frag" ) );
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


        m_modelWithTextureQueryID = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CModel2DComponent, CTransform2DComponent, CTexture2DComponent  >(),
            ecs::makeEntitySignature()
        );
    }

    CSimpled2DRenderingSystem::~CSimpled2DRenderingSystem() 
    {
        getEngine().getEntityWorld().destroyQuery( m_modelWithTextureQueryID );
    }

    void CSimpled2DRenderingSystem::update( float deltaTime ) 
    {
        const ecs::CEntityQuery* query;


        query = getEngine().getEntityWorld().queryEntities( m_modelWithTextureQueryID );

        m_spriteRenderer.clear();

        query->forEachEntityWith< CModel2DComponent, CTransform2DComponent, CTexture2DComponent >(
            [this]( CModel2DComponent& model, CTransform2DComponent& transform, CTexture2DComponent& texture )
            {
                vec2f adjustScale;

                float tmp;
                switch( texture.adjust )
                {
                case EModel2DTextureAdjust::SCALED:
                    adjustScale = model.size / vecCastType<float>( texture.texture.getSize() );
                    tmp = std::min( adjustScale.x, adjustScale.y );
                    adjustScale = { tmp, tmp };
                    break;

                case EModel2DTextureAdjust::SPANNED:
                    adjustScale = model.size / vecCastType<float>( texture.texture.getSize() );
                    break;
                
                case EModel2DTextureAdjust::ZOOMED:
                    adjustScale = model.size / vecCastType<float>( texture.texture.getSize() );
                    tmp = std::max( adjustScale.x, adjustScale.y );
                    adjustScale = { tmp, tmp };
                    break;

                default:
                    adjustScale = { 1.f, 1.f };
                }

                m_spriteRenderer.submitSprite( texture.texture, transform.position, model.origin, adjustScale * transform.scale, transform.rotation );
            }
        );
    }

    void CSimpled2DRenderingSystem::render()
    {
        getEngine().getWindow().clear();
        
        m_spriteRenderer.bindShader();
        m_spriteRenderer.render();
        m_spriteRenderer.unbindShader();

        getEngine().getWindow().flipBuffer();
    }

} // namespace chestnut::engine

