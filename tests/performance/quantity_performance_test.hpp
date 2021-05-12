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

        lol = theResourceManager.loadTexture( "../_media_test/awesomeface.png" );
        gatsu = theResourceManager.loadTexture( "../_media_test/berk.jpg" );

        SComponentSetSignature sign;
        sign.add<STransformComponent>()
            .add<SKinematicsComponent>()
            .add<STextureComponent>();

        int amount = 10000;
        std::vector<SComponentSet> vecCompSets = theEntityManager.createEntitiesReturnSets( sign, amount );

        for( auto& compSet : vecCompSets )
        {
            sign = compSet.getSignature();
            
            IComponent *c;

            c = compSet.mapTindexToComponent[ TINDEX( STransformComponent ) ];
            STransformComponent *transf = ( STransformComponent* )c;
            c = compSet.mapTindexToComponent[ TINDEX( SKinematicsComponent ) ];
            SKinematicsComponent *kinem = ( SKinematicsComponent* )c;
            c = compSet.mapTindexToComponent[ TINDEX( STextureComponent ) ];
            STextureComponent *tex = ( STextureComponent* )c;

            randTransf( transf );
            randRot( kinem );
            randTex( tex );
        }        
    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_QUANTITY_PERFORMANCE_TEST_H__