#ifndef __CHESTNUT_COMPONENT_BATCH_TEST_H__
#define __CHESTNUT_COMPONENT_BATCH_TEST_H__

#include "engine/ecs/management/component_batch.hpp"
#include "engine/ecs/components/components.hpp"

namespace chestnut
{
namespace test
{
    void componentBatchTest()
    {
        STransformComponent transfComp1, transfComp2;
        STextureComponent textComp1, textComp2;
        SKinematicsComponent kinemComp1, kinemComp2;

        transfComp1 = STransformComponent( Vector2f( 1, 1 ), Vector2f( 2, 2 ), Vector2f( 3, 3 ) );
        kinemComp1 = SKinematicsComponent( Vector2f( 4, 4 ), Vector2f( 5, 5 ) );
        transfComp2 = STransformComponent( Vector2f( 6, 6 ), Vector2f( 7, 7 ), Vector2f( 8, 8 ) );
        kinemComp2 = SKinematicsComponent( Vector2f( 9, 9 ), Vector2f( 0, 0 ) );

        transfComp1.ownerID = textComp1.ownerID = kinemComp1.ownerID = 1;
        transfComp2.ownerID = textComp2.ownerID = kinemComp2.ownerID = 2;


        SComponentSet compSet1, compSet2, compSet3;

        compSet1.componentOwnerID = 1;
        compSet1.addComponent( &transfComp1 );
        compSet1.addComponent( &textComp1 );
        compSet1.addComponent( &kinemComp1 );

        compSet2.componentOwnerID = 2;
        compSet2.addComponent( &transfComp2 );
        compSet2.addComponent( &textComp2 );
        compSet2.addComponent( &kinemComp2 );

        // components for entity 1 are reused for convenience, normally you need new components as this bundle is for different signature
        compSet3.componentOwnerID = 1;
        compSet3.addComponent( &transfComp1 );
        compSet3.addComponent( &textComp1 );


        CComponentBatch batch = CComponentBatch();

        batch.setSignature( compSet1.getSignature() );

        LOG_CHANNEL( "TEST", "<<Batch signature>>" );
        LOG_CHANNEL( "TEST", batch.getSignature().toString() );
        LOG_CHANNEL( "TEST", "");

        LOG_CHANNEL( "TEST", "<<Incorrent bundle submit test>>" );
        batch.submitComponentSet( compSet3 ); // should print errors
        LOG_CHANNEL( "TEST", "");


        batch.submitComponentSet( compSet1 );
        batch.submitComponentSet( compSet2 );

        
        LOG_CHANNEL( "TEST", "<<Get entities test>>" );
        auto ids = batch.getEntities();
        for( auto id : ids )
        {
            LOG_CHANNEL( "TEST", id );
        }
        LOG_CHANNEL( "TEST", "");


        LOG_CHANNEL( "TEST", "<<Get components incorrect test>>" );
        auto timerComps = batch.getComponents<STimerComponent>();
        LOG_CHANNEL( "TEST", "");


        LOG_CHANNEL( "TEST", "<<Get components test>>" );
        auto transfComps = batch.getComponents<STransformComponent>(); 
        auto kinemComps = batch.getComponents<SKinematicsComponent>();

        for( auto comp : transfComps )
        {
            LOG_CHANNEL( "TEST", comp->ownerID );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->position ) );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->rotation ) );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->scale ) );
        }
        LOG_CHANNEL( "TEST", "");
        for( auto comp : kinemComps )
        {
            LOG_CHANNEL( "TEST", comp->ownerID );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->velocity ) );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->acceleration ) );
        }
        LOG_CHANNEL( "TEST", "");


        LOG_CHANNEL( "TEST", "<<Remove entity test>>" );
        batch.removeEntityAndComponents(1);

        ids = batch.getEntities();
        transfComps = batch.getComponents<STransformComponent>(); 
        kinemComps = batch.getComponents<SKinematicsComponent>();

        for( auto id : ids )
        {
            LOG_CHANNEL( "TEST", id );
        }
        LOG_CHANNEL( "TEST", "");
        for( auto comp : transfComps )
        {
            LOG_CHANNEL( "TEST", comp->ownerID );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->position ) );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->rotation ) );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->scale ) );
        }
        LOG_CHANNEL( "TEST", "");
        for( auto comp : kinemComps )
        {
            LOG_CHANNEL( "TEST", comp->ownerID );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->velocity ) );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->acceleration ) );
        }
        LOG_CHANNEL( "TEST", "");


        LOG_CHANNEL( "TEST", "<<Remove all entities test>>" );
        batch.removeAllEntitiesAndComponents();

        ids = batch.getEntities();
        transfComps = batch.getComponents<STransformComponent>(); 
        kinemComps = batch.getComponents<SKinematicsComponent>();

        for( auto id : ids )
        {
            LOG_CHANNEL( "TEST", id );
        }
        LOG_CHANNEL( "TEST", "");
        for( auto comp : transfComps )
        {
            LOG_CHANNEL( "TEST", comp->ownerID );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->position ) );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->rotation ) );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->scale ) );
        }
        LOG_CHANNEL( "TEST", "");
        for( auto comp : kinemComps )
        {
            LOG_CHANNEL( "TEST", comp->ownerID );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->velocity ) );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp->acceleration ) );
        }
        LOG_CHANNEL( "TEST", "");
    }


} // namespace test

} // namespace chestnut


#endif // __CHESTNUT_COMPONENT_BATCH_TEST_H__