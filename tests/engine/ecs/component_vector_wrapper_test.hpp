#ifndef __CHESTNUT_COMPONENT_VECTOR_WRAPPER_TEST_H__
#define __CHESTNUT_COMPONENT_VECTOR_WRAPPER_TEST_H__

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
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp.position ) );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp.rotation ) );
            LOG_CHANNEL( "TEST", VEC_TO_STR( comp.scale ) );
            LOG_CHANNEL( "TEST", "" );
        }
    }

    void componentVectorWrapperTest()
    {
        CComponentVectorWrapper<STransformComponent> transfVec;
        IComponentVectorWrapper *baseVec = (IComponentVectorWrapper *)&transfVec;

        LOG_CHANNEL( "TEST", "<< Create test >>" );
        {
            STransformComponent *transfComp1 = ( STransformComponent * )baseVec->create(1);
            transfComp1->position = Vector2f(1,1);

            logTransformCompVec( transfVec );
        }
        LOG_CHANNEL( "TEST", "" );


        LOG_CHANNEL( "TEST", "<< Get test >>" );
        {
            baseVec->create(2);
            STransformComponent *transfComp2 = ( STransformComponent * )baseVec->get(2);
            transfComp2->scale = Vector2f(2,2);

            logTransformCompVec( transfVec );            
        }
        LOG_CHANNEL( "TEST", "" );
        

        LOG_CHANNEL( "TEST", "<< Erase test >>" );
        {
            baseVec->create(3);

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

#endif // __CHESTNUT_COMPONENT_VECTOR_WRAPPER_TEST_H__