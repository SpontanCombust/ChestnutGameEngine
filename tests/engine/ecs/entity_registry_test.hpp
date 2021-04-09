#ifndef __CHESTNUT_ENTITY_REGISTRY_TEST_H__
#define __CHESTNUT_ENTITY_REGISTRY_TEST_H__

#include "engine/ecs/management/entity_registry.hpp"
#include "engine/ecs/components/components.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
namespace test
{
    void entityRegistryTest()
    {
        CEntityRegistry registry;

        SComponentSetSignature testSign;


        LOG_CHANNEL( "TEST", "<<Add and get entity without signature test>>");

        registry.addEntity(0);
        testSign = registry.getEntitySignature(0);
        LOG_CHANNEL( "TEST", testSign.toString() );
        LOG_CHANNEL( "TEST", "" );



        LOG_CHANNEL( "TEST", "<<Add and get entity with signature test>>");
        
        SComponentSetSignature sign1;
        sign1.add<STransformComponent>();
        sign1.add<SKinematicsComponent>();

        registry.addEntity( 1, sign1 );
        
        testSign = registry.getEntitySignature(1);
        LOG_CHANNEL( "TEST", testSign.toString() );
        LOG_CHANNEL( "TEST", "" );



        LOG_CHANNEL( "TEST", "<<Has entity test>>");
        LOG_CHANNEL( "TEST", registry.hasEntity(2) );
        LOG_CHANNEL( "TEST", registry.hasEntity(1) );
        LOG_CHANNEL( "TEST", "" );



        LOG_CHANNEL( "TEST", "<<Get entity invalid test>>");

        try
        {
            testSign = registry.getEntitySignature(2);
            LOG_CHANNEL( "TEST", testSign.toString() );
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        LOG_CHANNEL( "TEST", "" );
        


        LOG_CHANNEL( "TEST", "<<Update entity test>>");
        SComponentSetSignature sign2, sign3;
        sign2.add<STimerComponent>();
        sign3.add<STransformComponent>();
        sign3.add<STextureComponent>();

        registry.updateEntity( 0, sign2 );
        testSign = registry.getEntitySignature(0);
        LOG_CHANNEL( "TEST", testSign.toString() );

        registry.updateEntity( 2, sign3 );
        testSign = registry.getEntitySignature(2);
        LOG_CHANNEL( "TEST", testSign.toString() );
        LOG_CHANNEL( "TEST", "" );



        LOG_CHANNEL( "TEST", "<<Remove entity test>>");

        registry.removeEntity(0);
        LOG_CHANNEL( "TEST", registry.hasEntity(0) );
        LOG_CHANNEL( "TEST", "" );
    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_ENTITY_REGISTRY_TEST_H__