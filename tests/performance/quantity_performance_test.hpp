#ifndef __CHESTNUT_QUANTITY_PERFORMANCE_TEST_H__
#define __CHESTNUT_QUANTITY_PERFORMANCE_TEST_H__

#include "engine/globals.hpp"
#include "engine/ecs/components/components.hpp"

namespace chestnut
{
namespace test
{
    using namespace chestnut;

    static void randTransf( STransformComponent *comp )
    {
        int x = rand() % theWindow.getWidth() + 1;
        int y = rand() % theWindow.getHeight() + 1;

        comp->position = { (float)x, (float)y };

        comp->scale = { 0.05f, 0.05f };
    }

    static void randRot( SKinematicsComponent *comp )
    {
        double rot = (double)rand() / (double)( RAND_MAX / 6.f );
        comp->angularVelocity = rot;
    }
    
    CTexture2D lol;
    CTexture2D gatsu;

    static void randTex( STextureComponent *comp )
    {
        // unsigned int r = rand() % 2;
        // if( r == 0 )
            comp->texture = lol;
        // else
        //     comp->texture = gatsu;
    }

    void loadLotsOfEntities()
    {
        srand( time(nullptr) );

        SComponentSetSignature sign;
        sign.add<STransformComponent>()
            .add<SKinematicsComponent>()
            .add<STextureComponent>();

        int amount = 1000;
        std::vector<entityid_t> ids = theEntityManager.createEntities( sign, amount );

        lol = theResourceManager.loadTexture( "../_media_test/awesomeface.png" );
        gatsu = theResourceManager.loadTexture( "../_media_test/berk.jpg" );

        for( const auto& id : ids )
        {
            STransformComponent *transf = theEntityManager.getComponent<STransformComponent>( id );
            SKinematicsComponent *kinem = theEntityManager.getComponent<SKinematicsComponent>( id );
            STextureComponent *tex = theEntityManager.getComponent<STextureComponent>( id );

            randTransf( transf );
            randRot( kinem );
            randTex( tex );
        }
    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_QUANTITY_PERFORMANCE_TEST_H__