#ifndef __CHESTNUT_COMPONENT_SET_TEST_H__
#define __CHESTNUT_COMPONENT_SET_TEST_H__

#include "engine/ecs/management/component_set.hpp"
#include "engine/ecs/components/components.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
namespace test
{
    void componentSetTest()
    {
        SComponentSet compSet;

        STransformComponent transfComp;
        STextureComponent textComp;
        STimerComponent timerComp;

        LOG_CHANNEL( "TEST", "<<Add component test>>" );
        compSet.addComponent( &transfComp );
        compSet.addComponent( &textComp );
        compSet.addComponent( &timerComp );

        LOG_CHANNEL( "TEST", compSet.getSignature().toString() );
        LOG_CHANNEL( "TEST", "");


        LOG_CHANNEL( "TEST", "<<Remove components test>>" );
        compSet.removeComponent( TINDEX( textComp ) );
        compSet.removeComponent( TINDEX( STimerComponent ) );

        LOG_CHANNEL( "TEST", compSet.getSignature().toString() );
        LOG_CHANNEL( "TEST", "");


        LOG_CHANNEL( "TEST", "<<Add null component test>>" );
        compSet.addComponent( nullptr );   

        LOG_CHANNEL( "TEST", compSet.getSignature().toString() );
        LOG_CHANNEL( "TEST", "");  
    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_SET_TEST_H__