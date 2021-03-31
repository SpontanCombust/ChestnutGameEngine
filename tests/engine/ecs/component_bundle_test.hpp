#ifndef __CHESTNUT_COMPONENT_BUNDLE_TEST_H__
#define __CHESTNUT_COMPONENT_BUNDLE_TEST_H__

#include "engine/ecs/db/component_bundle.hpp"
#include "engine/ecs/components/components.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{
namespace test
{
    void componentBundleTest()
    {
        SComponentBundle bundle;

        STransformComponent transfComp;
        STextureComponent textComp;
        STimerComponent timerComp;

        bundle.addComponent( &transfComp );
        bundle.addComponent( &textComp );
        bundle.addComponent( &timerComp );

        LOG( bundle.getSignature().toString() );
        LOG("");


        bundle.removeComponent( TINDEX( textComp ) );
        bundle.removeComponent( TINDEX( STimerComponent ) );

        LOG( bundle.getSignature().toString() );
        LOG("");


        bundle.addComponent( nullptr );   

        LOG( bundle.getSignature().toString() );
        LOG("");  
    }

} // namespace test

} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_BUNDLE_TEST_H__