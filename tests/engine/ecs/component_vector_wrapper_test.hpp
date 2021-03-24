#include "engine/ecs/db/component_vector_wrapper.hpp"
#include "engine/ecs/components/components.hpp"

namespace chestnut_test
{
    int componentVectorWrapperTest()
    {
        using namespace chestnut;

        CComponentVectorWrapper<STransformComponent> transfVec;
        IComponentVectorWrapper *baseVec = (IComponentVectorWrapper *)&transfVec;

        STransformComponent *transfComp1 = ( STransformComponent * )baseVec->add(1);
        transfComp1->position = Vector2f(1,1);

        baseVec->add(2);
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

        baseVec->add(3);

        baseVec->erase(2);

        for( const STransformComponent& comp : transfVec.vec )
        {
            LOG( comp.ownerID );
            LOG( VEC_TO_STR( comp.position ) );
            LOG( VEC_TO_STR( comp.rotation ) );
            LOG( VEC_TO_STR( comp.scale ) );
            LOG( "" );
        }

        return 0;

    }

} // namespace chestnut_test
