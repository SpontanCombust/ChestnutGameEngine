#ifndef __CHESTNUT_COMPONENT_VECTOR_WRAPPER_TEST_H__
#define __CHESTNUT_COMPONENT_VECTOR_WRAPPER_TEST_H__

#include "engine/ecs/db/component_vector_wrapper.hpp"
#include "engine/ecs/components/components.hpp"

namespace chestnut 
{ 
namespace test
{
    void componentVectorWrapperTest()
    {
        CComponentVectorWrapper<STransformComponent> transfVec;
        IComponentVectorWrapper *baseVec = (IComponentVectorWrapper *)&transfVec;

        STransformComponent *transfComp1 = ( STransformComponent * )baseVec->create(1);
        transfComp1->position = Vector2f(1,1);

        baseVec->create(2);
        STransformComponent *transfComp2 = ( STransformComponent * )baseVec->get(2);
        transfComp2->scale = Vector2f(2,2);

        for( const STransformComponent& comp : transfVec.vec )
        {
            LOG( comp.ownerID );
            LOG( VEC_TO_STR( comp.position ) );
            LOG( VEC_TO_STR( comp.rotation ) );
            LOG( VEC_TO_STR( comp.scale ) );
            LOG( "" );
        }

        baseVec->create(3);

        baseVec->erase(2);

        for( const STransformComponent& comp : transfVec.vec )
        {
            LOG( comp.ownerID );
            LOG( VEC_TO_STR( comp.position ) );
            LOG( VEC_TO_STR( comp.rotation ) );
            LOG( VEC_TO_STR( comp.scale ) );
            LOG( "" );
        }
    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_VECTOR_WRAPPER_TEST_H__