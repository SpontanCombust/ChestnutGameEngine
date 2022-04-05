#include "simple2d_rendering_system.hpp"

#include "../../main/engine.hpp"
#include "../../resources/resource_manager.hpp"
#include "../../maths/matrix4.hpp"
#include "../../maths/vector_cast.hpp"
#include "../components/model2d_component.hpp"
#include "../components/transform2d_component.hpp"
#include "../components/sprite_component.hpp"
#include "../components/render_layer_component.hpp"
#include "../../debug/log.hpp"
#include "../../macros.hpp"

namespace chestnut::engine
{
    CSimple2DRenderingSystem::CSimple2DRenderingSystem( CEngine& engine ) : IRenderingSystem( engine )
    {
        try
        {
            m_spriteRenderer.init();
        }
        catch(const std::exception& e)
        {
            LOG_ERROR( e.what() );
        }

        try
        {
            m_polygonRenderer.init();
        }
        catch(const std::exception& e)
        {
            LOG_ERROR( e.what() );   
        }
        
        try
        {
            m_textRenderer.init();
        }
        catch(const std::exception& e)
        {
            LOG_ERROR( e.what() );  
        }


        m_spriteQueryID = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CTransform2DComponent, CSpriteComponent >(),
            ecs::makeEntitySignature< CModel2DComponent, CRenderLayerComponent >()
        );

        m_spriteModelQueryID = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CModel2DComponent, CTransform2DComponent, CSpriteComponent  >(),
            ecs::makeEntitySignature< CRenderLayerComponent >()
        );

        m_layerSpriteQueryID = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CTransform2DComponent, CSpriteComponent, CRenderLayerComponent >(),
            ecs::makeEntitySignature< CModel2DComponent >()
        );

        m_layerSpriteModelQueryID = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature< CModel2DComponent, CTransform2DComponent, CSpriteComponent, CRenderLayerComponent >(),
            ecs::makeEntitySignature()
        );


        const CWindow& win = getEngine().getWindow();
        m_camera.m_dimensions = { (float)win.getSizeWidth(), (float)win.getSizeHeight() };
    }

    CSimple2DRenderingSystem::~CSimple2DRenderingSystem() 
    {
        getEngine().getEntityWorld().destroyQuery( m_spriteModelQueryID );
    }



    vec2f getAdjustScale( const CModel2DComponent& model, const CSpriteComponent& texture )
    {
        SRectangle clip = texture.sprite.getClippingRect();
        vec2f adjustScale;

        switch( texture.adjust )
        {
        case ESpriteToModel2DAdjust::SCALED:
            adjustScale = model.size / vec2f{ clip.w, clip.h };
            adjustScale = vec2f( std::min( adjustScale.x, adjustScale.y ) );
            break;

        case ESpriteToModel2DAdjust::SPANNED:
            adjustScale = model.size / vec2f{ clip.w, clip.h };
            break;
        
        case ESpriteToModel2DAdjust::ZOOMED:
            adjustScale = model.size / vec2f{ clip.w, clip.h };
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


        query = getEngine().getEntityWorld().queryEntities( m_spriteQueryID );

        query->sort<CTransform2DComponent>( comparator );

        query->forEachEntityWith< CTransform2DComponent, CSpriteComponent >(
            [this]( CTransform2DComponent& transform, CSpriteComponent& texture )
            {
                m_spriteRenderer.submitSprite( texture.sprite, transform.position, vec2f{ 0.f }, transform.scale, transform.rotation );
            }
        );
        

        query = getEngine().getEntityWorld().queryEntities( m_spriteModelQueryID );
        
        query->sort<CTransform2DComponent>( comparator );

        query->forEachEntityWith< CTransform2DComponent, CSpriteComponent, CModel2DComponent >(
            [this]( CTransform2DComponent& transform, CSpriteComponent& texture, CModel2DComponent& model )
            {
                vec2f adjustScale = getAdjustScale( model, texture );
                m_spriteRenderer.submitSprite( texture.sprite, transform.position, model.origin, adjustScale * transform.scale, transform.rotation );
            }
        );


        query = getEngine().getEntityWorld().queryEntities( m_layerSpriteQueryID );

        query->sort<CTransform2DComponent, CRenderLayerComponent>( comparatorLayered );

        query->forEachEntityWith< CTransform2DComponent, CSpriteComponent, CRenderLayerComponent >(
            [this]( CTransform2DComponent& transform, CSpriteComponent& texture, CRenderLayerComponent& layer )
            {
                m_spriteRenderer.submitSprite( texture.sprite, transform.position, vec2f{ 0.f }, transform.scale, transform.rotation );
            }
        );


        query = getEngine().getEntityWorld().queryEntities( m_layerSpriteModelQueryID );
        
        query->sort<CTransform2DComponent, CRenderLayerComponent>( comparatorLayered );
        
        query->forEachEntityWith< CTransform2DComponent, CSpriteComponent, CModel2DComponent, CRenderLayerComponent >(
            [this]( CTransform2DComponent& transform, CSpriteComponent& texture, CModel2DComponent& model, CRenderLayerComponent& layer )
            {
                vec2f adjustScale = getAdjustScale( model, texture );
                m_spriteRenderer.submitSprite( texture.sprite, transform.position, model.origin, adjustScale * transform.scale, transform.rotation );
            }
        );
    }

    void CSimple2DRenderingSystem::render()
    {
        getEngine().getWindow().clear();
        
        m_camera.calculateMatrices();
        m_spriteRenderer.setViewMatrix( m_camera.getViewMatrix() );
        m_spriteRenderer.setProjectionMatrix( m_camera.getProjectionMatrix() );

#if CHESTNUT_SIMPLE2D_RENDERING_SYSTEM_FORCE_GPU_SYNCHRONIZATION > 0
        glFinish(); // prevent CPU getting too hasty with sending requests to GPU
#endif

        m_spriteRenderer.render( getEngine().getWindow().getFramebuffer() );

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




    const CCamera2D& CSimple2DRenderingSystem::getCamera() const
    {
        return m_camera;
    }

    CCamera2D& CSimple2DRenderingSystem::getCamera() 
    {
        return m_camera;
    }

} // namespace chestnut::engine

