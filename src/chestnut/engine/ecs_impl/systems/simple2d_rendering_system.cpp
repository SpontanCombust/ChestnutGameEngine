#include "simple2d_rendering_system.hpp"

#include "../../main/engine.hpp"
#include "../../resources/resource_manager.hpp"
#include "../../maths/matrix4.hpp"
#include "../../maths/vector_cast.hpp"
#include "../components/model2d_component.hpp"
#include "../components/transform2d_component.hpp"
#include "../components/texture2d_component.hpp"
#include "../components/render_layer_component.hpp"
#include "../../debug/log.hpp"
#include "../../macros.hpp"

namespace chestnut::engine
{
    CSimple2DRenderingSystem::CSimple2DRenderingSystem( CEngine& engine ) : IRenderingSystem( engine )
    {
        try
        {
            m_spriteRenderer.init( CResourceManager::loadOrGetShaderProgramResource( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/sprite.vert", CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/sprite.frag" ) );
        }
        catch(const std::exception& e)
        {
            LOG_ERROR( e.what() );
        }

        try
        {
            m_polygonRenderer.init( CResourceManager::loadOrGetShaderProgramResource( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.vert", CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.frag" ) );
        }
        catch(const std::exception& e)
        {
            LOG_ERROR( e.what() );   
        }
        
        try
        {
            m_textRenderer.init( CResourceManager::loadOrGetShaderProgramResource( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/text.vert", CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/text.frag" ) );
        }
        catch(const std::exception& e)
        {
            LOG_ERROR( e.what() );  
        }


        m_textureQueryID = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CTransform2DComponent, CTexture2DComponent >(),
            ecs::makeEntitySignature< CModel2DComponent, CRenderLayerComponent >()
        );

        m_textureModelQueryID = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CModel2DComponent, CTransform2DComponent, CTexture2DComponent  >(),
            ecs::makeEntitySignature< CRenderLayerComponent >()
        );

        m_layerTextureQueryID = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CTransform2DComponent, CTexture2DComponent, CRenderLayerComponent >(),
            ecs::makeEntitySignature< CModel2DComponent >()
        );

        m_layerTextureModelQueryID = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CModel2DComponent, CTransform2DComponent, CTexture2DComponent, CRenderLayerComponent >(),
            ecs::makeEntitySignature()
        );
    }

    CSimple2DRenderingSystem::~CSimple2DRenderingSystem() 
    {
        getEngine().getEntityWorld().destroyQuery( m_textureModelQueryID );
    }



    inline vec2f getAdjustScale( const CModel2DComponent& model, const CTexture2DComponent& texture )
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

        return adjustScale;
    }


    bool topToBottomCompare( const CTransform2DComponent& t1, const CTransform2DComponent& t2 )
    {
        return t1.position.y < t2.position.y;
    }

    bool bottomToTopCompare( const CTransform2DComponent& t1, const CTransform2DComponent& t2 )
    {
        return t1.position.y > t2.position.y;
    }

    bool leftToRightCompare( const CTransform2DComponent& t1, const CTransform2DComponent& t2 )
    {
        return t1.position.x < t2.position.x;
    }

    bool rightToLeftCompare( const CTransform2DComponent& t1, const CTransform2DComponent& t2 )
    {
        return t1.position.x > t2.position.x;
    }

    bool topToBottomCompareLayered( const CTransform2DComponent& t1, const CRenderLayerComponent& l1, const CTransform2DComponent& t2, const CRenderLayerComponent& l2 )
    {
        if( l1.layer == l2.layer )
        {
            return t1.position.y < t2.position.y;
        }

        return l1.layer < l2.layer;
    }

    bool bottomToTopCompareLayered( const CTransform2DComponent& t1, const CRenderLayerComponent& l1, const CTransform2DComponent& t2, const CRenderLayerComponent& l2 )
    {
        if( l1.layer == l2.layer )
        {
            return t1.position.y > t2.position.y;
        }

        return l1.layer < l2.layer;
    }

    bool leftToRightCompareLayered( const CTransform2DComponent& t1, const CRenderLayerComponent& l1, const CTransform2DComponent& t2, const CRenderLayerComponent& l2 )
    {
        if( l1.layer == l2.layer )
        {
            return t1.position.x < t2.position.x;
        }

        return l1.layer < l2.layer;
    }

    bool rightToLeftCompareLayered( const CTransform2DComponent& t1, const CRenderLayerComponent& l1, const CTransform2DComponent& t2, const CRenderLayerComponent& l2 )
    {
        if( l1.layer == l2.layer )
        {
            return t1.position.x > t2.position.x;
        }

        return l1.layer < l2.layer;
    }

    void CSimple2DRenderingSystem::update( float deltaTime ) 
    {
        bool (*comparator)( const CTransform2DComponent&, const CTransform2DComponent& );
        bool (*comparatorLayered)( const CTransform2DComponent&, const CRenderLayerComponent&, const CTransform2DComponent&, const CRenderLayerComponent& );
        switch( m_defaultRenderOrder )
        {
        case EDefaultRenderOrder::BOTTOM_TO_TOP:
            comparator = bottomToTopCompare;
            comparatorLayered = bottomToTopCompareLayered;
            break;
        case EDefaultRenderOrder::LEFT_TO_RIGHT:
            comparator = leftToRightCompare;
            comparatorLayered = leftToRightCompareLayered;
            break;
        case EDefaultRenderOrder::RIGHT_TO_LEFT:
            comparator = rightToLeftCompare;
            comparatorLayered = rightToLeftCompareLayered;
            break;
        default:
            comparator = topToBottomCompare;
            comparatorLayered = topToBottomCompareLayered;
        }


        m_spriteRenderer.clear();

        ecs::CEntityQuery* query;


        query = getEngine().getEntityWorld().queryEntities( m_textureQueryID );

        query->sort<CTransform2DComponent>( comparator );

        query->forEachEntityWith< CTransform2DComponent, CTexture2DComponent >(
            [this]( CTransform2DComponent& transform, CTexture2DComponent& texture )
            {
                m_spriteRenderer.submitSprite( texture.texture, transform.position, vec2f{ 0.f }, transform.scale, transform.rotation );
            }
        );
        

        query = getEngine().getEntityWorld().queryEntities( m_textureModelQueryID );
        
        query->sort<CTransform2DComponent>( comparator );

        query->forEachEntityWith< CTransform2DComponent, CTexture2DComponent, CModel2DComponent >(
            [this]( CTransform2DComponent& transform, CTexture2DComponent& texture, CModel2DComponent& model )
            {
                vec2f adjustScale = getAdjustScale( model, texture );
                m_spriteRenderer.submitSprite( texture.texture, transform.position, model.origin, adjustScale * transform.scale, transform.rotation );
            }
        );


        query = getEngine().getEntityWorld().queryEntities( m_layerTextureQueryID );

        query->sort<CTransform2DComponent, CRenderLayerComponent>( comparatorLayered );

        query->forEachEntityWith< CTransform2DComponent, CTexture2DComponent, CRenderLayerComponent >(
            [this]( CTransform2DComponent& transform, CTexture2DComponent& texture, CRenderLayerComponent& layer )
            {
                m_spriteRenderer.submitSprite( texture.texture, transform.position, vec2f{ 0.f }, transform.scale, transform.rotation );
            }
        );


        query = getEngine().getEntityWorld().queryEntities( m_layerTextureModelQueryID );
        
        query->sort<CTransform2DComponent, CRenderLayerComponent>( comparatorLayered );
        
        query->forEachEntityWith< CTransform2DComponent, CTexture2DComponent, CModel2DComponent, CRenderLayerComponent >(
            [this]( CTransform2DComponent& transform, CTexture2DComponent& texture, CModel2DComponent& model, CRenderLayerComponent& layer )
            {
                vec2f adjustScale = getAdjustScale( model, texture );
                m_spriteRenderer.submitSprite( texture.texture, transform.position, model.origin, adjustScale * transform.scale, transform.rotation );
            }
        );
    }

    void CSimple2DRenderingSystem::render()
    {
        getEngine().getWindow().clear();
        
        m_spriteRenderer.bindShader();
        m_spriteRenderer.setViewMatrix( mat4f() );
        m_spriteRenderer.setProjectionMatrix( matMakeOrthographic<float>( 0.f, getEngine().getWindow().getSizeWidth(), getEngine().getWindow().getSizeHeight(), 0.f, -1.f, 1.f ) );

#if CHESTNUT_SIMPLE2D_RENDERING_SYSTEM_FORCE_GPU_SYNCHRONIZATION > 0
        glFinish(); // prevent CPU getting too hasty with sending requests to GPU
#endif

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




    void CSimple2DRenderingSystem::setDefaultRenderOrder( EDefaultRenderOrder order ) 
    {
        m_defaultRenderOrder = order;
    }

    EDefaultRenderOrder CSimple2DRenderingSystem::getDefaultRenderOrder() const
    {
        return m_defaultRenderOrder;
    }

} // namespace chestnut::engine

