#ifndef __CHESTNUT_COMPONENT_BUNDLE_SIGNATURE_TEST_H__
#define __CHESTNUT_COMPONENT_BUNDLE_SIGNATURE_TEST_H__

#include "../src/engine/ecs/db/component_bundle_signature.hpp"
#include "../src/engine/ecs/components/components.hpp"

namespace chestnut 
{ 
namespace test 
{
    void componentBundleSignatureTest()
    {
        SComponentBundleSignature signature1;

        signature1.add<STransformComponent>();
        signature1.add<STextureComponent>();

        LOG( signature1.toString() );
        LOG("");


        signature1.remove( TINDEX( STransformComponent ) );

        LOG( signature1.toString() );
        LOG("");


        LOG( signature1.includes( TINDEX( STextureComponent ) ) );
        LOG("");


        SComponentBundleSignature signature2;

        signature2.add( TINDEX( STextureComponent ) );

        LOG( ( signature1 == signature2 ) );
        LOG("");
    }

} // namespace test
    
} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_BUNDLE_SIGNATURE_TEST_H__