#ifndef __CHESTNUT_ENTITY_MANAGER_TEST_H__
#define __CHESTNUT_ENTITY_MANAGER_TEST_H__

#include "engine/ecs/management/entity_manager.hpp"
#include "engine/ecs/components/components.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{         
namespace test
{
    void entityManagerTest()
    {
        CEntityManager manager;
        entityid_t ids[7];


        LOG_CHANNEL( "TEST", "<< Create/has entity test >>");
        {
            std::vector< entityid_t > tmp;

            ids[0] = manager.createEntity();
            LOG_CHANNEL( "TEST", "Created entity " << ids[0] );

            tmp = manager.createEntities(3);
            ids[1] = tmp[0];
            LOG_CHANNEL( "TEST", "Created entity " << ids[1] );
            ids[2] = tmp[1];
            LOG_CHANNEL( "TEST", "Created entity " << ids[2] );
            ids[3] = tmp[2];
            LOG_CHANNEL( "TEST", "Created entity " << ids[3] );

            LOG_CHANNEL( "TEST", "Has entity " << ids[0] << "? : " << manager.hasEntity( ids[0] ) );
            LOG_CHANNEL( "TEST", "Has entity " << ids[1] << "? : " << manager.hasEntity( ids[1] ) );
            LOG_CHANNEL( "TEST", "Has entity " << ids[2] << "? : " << manager.hasEntity( ids[2] ) );
            LOG_CHANNEL( "TEST", "Has entity " << ids[3] << "? : " << manager.hasEntity( ids[3] ) );
            LOG_CHANNEL( "TEST", "Has entity " << 0 << "? : " << manager.hasEntity( 0 ) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<< Create/has component test >>");
        {
            // 1st entity will have no components

            manager.createComponent<STransformComponent>( ids[1] );
            manager.createComponent<SKinematicsComponent>( ids[1] );

            manager.createComponent<STransformComponent>( ids[2] );
            manager.createComponent<SKinematicsComponent>( ids[2] );
            manager.createComponent<STextureComponent>( ids[2] );

            manager.createComponent<STransformComponent>( ids[3] );
            manager.createComponent<SKinematicsComponent>( ids[3] );
            manager.createComponent<STimerComponent>( ids[3] );

            manager.processEntityRequests();

            LOG_CHANNEL( "TEST", "Has entity " << ids[0] << " got STransformComponent? : " << manager.hasComponent<STransformComponent>( ids[0] ) );

            LOG_CHANNEL( "TEST", "Has entity " << ids[1] << " got STransformComponent? : " << manager.hasComponent<STransformComponent>( ids[1] ) );
            LOG_CHANNEL( "TEST", "Has entity " << ids[1] << " got STimerComponent? : " << manager.hasComponent<STimerComponent>( ids[1] ) );
            LOG_CHANNEL( "TEST", "Has entity " << ids[1] << " got SKinematicsComponent? : " << manager.hasComponent<SKinematicsComponent>( ids[1] ) );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<< Create/has signed entity test >>");
        {
            std::vector< entityid_t > tmp;

            SComponentSetSignature sign1;
            SComponentSetSignature sign2;

            sign1.add<STransformComponent>();

            sign2.add<STextureComponent>()
                 .add<SKinematicsComponent>();

            ids[4] = manager.createEntity( sign1 );
            
            tmp = manager.createEntities( sign2, 2 );
            ids[5] = tmp[0];
            ids[6] = tmp[1];

            manager.processEntityRequests();

            LOG_CHANNEL( "TEST", "Has entity " << ids[4] << " got STransformComponent? : " << manager.hasComponent<STransformComponent>( ids[4] ) );

            LOG_CHANNEL( "TEST", "Has entity " << ids[5] << " got STextureComponent? : " << manager.hasComponent<STextureComponent>( ids[5] ) );
            LOG_CHANNEL( "TEST", "Has entity " << ids[6] << " got SKinematicsComponent? : " << manager.hasComponent<SKinematicsComponent>( ids[6] ) );
        }
        LOG_CHANNEL( "TEST", "");

        LOG_CHANNEL( "TEST", "<< Get component test >>");
        {
            STransformComponent *transfComp = manager.getComponent<STransformComponent>( ids[3] );
            SKinematicsComponent *kinemComp = manager.getComponent<SKinematicsComponent>( ids[3] );
            STextureComponent *textComp = manager.getComponent<STextureComponent>( ids[3] );

            if( transfComp )
            {
                transfComp->position = Vector2f( 1, 2 );
                LOG_CHANNEL( "TEST", VEC_TO_STR( transfComp->position ) );
            }

            if( kinemComp )
            {
                kinemComp->velocity = Vector2f( 3, 4 );
                LOG_CHANNEL( "TEST", VEC_TO_STR( kinemComp->velocity ) );
            }

            if( textComp )
            {
                textComp->scaleOffset = Vector2f( 5, 6 );
                LOG_CHANNEL( "TEST", VEC_TO_STR( textComp->scaleOffset ) );
            }
        }
        LOG_CHANNEL( "TEST", "");


        LOG_CHANNEL( "TEST", "<< Get batches test >>");
        {
            auto vec = manager.getComponentBatches();

            for( const auto batch : vec )
            {
                LOG_CHANNEL( "TEST", batch->toString() );
            }
        }
        LOG_CHANNEL( "TEST", "");


        LOG_CHANNEL( "TEST", "<< Remove component test >>");
        {
            manager.destroyComponent<STextureComponent>( ids[2] );
            manager.destroyComponent<STextureComponent>( ids[3] );

            manager.processEntityRequests();

            LOG_CHANNEL( "TEST", "Has entity " << ids[2] << " got STextureComponent? : " << manager.hasComponent<STextureComponent>( ids[2] ) );

            auto vec = manager.getComponentBatches();

            for( const auto batch : vec )
            {
                LOG_CHANNEL( "TEST", batch->toString() );
            }
        }
        LOG_CHANNEL( "TEST", "");


        LOG_CHANNEL( "TEST", "<< Remove entity test >>");
        {
            manager.destroyEntity( ids[0] );
            manager.destroyEntity( ids[3] );

            manager.processEntityRequests();
            
            auto vec = manager.getComponentBatches();

            for( const auto batch : vec )
            {
                LOG_CHANNEL( "TEST", batch->toString() );
            }
        }
        LOG_CHANNEL( "TEST", "");

        manager.destroyAllEntities();
    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_ENTITY_MANAGER_TEST_H__