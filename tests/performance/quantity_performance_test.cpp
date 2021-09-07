#include "performance_tests.hpp"

#include "engine/globals.hpp"
#include "engine/ecs/components/components.hpp"

namespace chestnut
{
namespace test
{
    using namespace chestnut;

    static void randTransf( CTransformComponent *comp )
    {
        int x = rand() % theWindow.getWidth() + 1;
        int y = rand() % theWindow.getHeight() + 1;

        comp->position = { (float)x, (float)y };

        comp->scale = { 0.05f, 0.05f };
    }

    static void randRot( CKinematicsComponent *comp )
    {
        double rot = (double)rand() / (double)( RAND_MAX / 6.f );
        comp->angularVelocity = rot;
    }
    
    CTexture2D lol;
    CTexture2D gatsu;

    static void randTex( CTextureComponent *comp )
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

        lol = CResourceManager::getTexture2DResource( "../_media_test/awesomeface.png" );
        gatsu = CResourceManager::getTexture2DResource( "../_media_test/berk.jpg" );

        CEntitySignature sign;
        sign.add<CTransformComponent>()
            .add<CKinematicsComponent>()
            .add<CTextureComponent>();

        int amount = 10000;
        std::vector<SComponentSet> vecCompSets = theEntityManager.createEntitiesReturnSets( sign, amount );

        for( auto& compSet : vecCompSets )
        {
            sign = compSet.getSignature();
            
            IComponent *c;

            c = compSet.mapTindexToComponent[ TINDEX( CTransformComponent ) ];
            CTransformComponent *transf = ( CTransformComponent* )c;
            c = compSet.mapTindexToComponent[ TINDEX( CKinematicsComponent ) ];
            CKinematicsComponent *kinem = ( CKinematicsComponent* )c;
            c = compSet.mapTindexToComponent[ TINDEX( CTextureComponent ) ];
            CTextureComponent *tex = ( CTextureComponent* )c;

            randTransf( transf );
            randRot( kinem );
            randTex( tex );
        }        
    }

} // namespace test

} // namespace chestnut
