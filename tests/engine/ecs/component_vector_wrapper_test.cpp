#include "ecs_tests.hpp"

#include "engine/ecs/management/component_vector_wrapper.hpp"
#include "engine/ecs/components/components.hpp"

namespace chestnut 
{ 
namespace test
{
    static void logTransformCompVec( CComponentVectorWrapper<STransformComponent> transfVec )
    {
        for( const STransformComponent& comp : transfVec.vec )
        {
            LOG_CHANNEL( "TEST", comp.ownerID );
            LOG_CHANNEL( "TEST", vecToString( comp.position ) );
            LOG_CHANNEL( "TEST", comp.rotation );
            LOG_CHANNEL( "TEST", vecToString( comp.scale ) );
            LOG_CHANNEL( "TEST", "" );
        }
    }

    void componentVectorWrapperTest()
    {
        CComponentVectorWrapper<STransformComponent> transfVec;
        IComponentVectorWrapper *baseVec = (IComponentVectorWrapper *)&transfVec;

        LOG_CHANNEL( "TEST", "<< Create test >>" );
        {
            STransformComponent *transfComp1 = ( STransformComponent * )baseVec->push_back(1);
            transfComp1->position = vec2f(1,1);

            logTransformCompVec( transfVec );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<< Get test >>" );
        {
            baseVec->push_back(2);
            STransformComponent *transfComp2 = ( STransformComponent * )baseVec->find(2);
            transfComp2->scale = vec2f(2,2);

            logTransformCompVec( transfVec );            
        }
        LOG_CHANNEL( "TEST", "" );
        

        LOG_CHANNEL( "TEST", "<< Erase test >>" );
        {
            baseVec->push_back(3);

            baseVec->erase(2);

            logTransformCompVec( transfVec );
        }
        LOG_CHANNEL( "TEST", "" );

        LOG_CHANNEL( "TEST", "<< toString test >>" );
        {
            LOG_CHANNEL( "TEST", baseVec->toString() );
        }
        LOG_CHANNEL( "TEST", "" );
    }

} // namespace test

} // namespace chestnut
