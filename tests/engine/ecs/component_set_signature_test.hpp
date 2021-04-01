#ifndef __CHESTNUT_COMPONENT_SET_SIGNATURE_TEST_H__
#define __CHESTNUT_COMPONENT_SET_SIGNATURE_TEST_H__

#include "engine/ecs/management/component_set_signature.hpp"
#include "engine/ecs/components/components.hpp"

namespace chestnut 
{ 
namespace test 
{
    void componentSetSignatureTest()
    {
        SComponentSetSignature signature1;

        LOG_CHANNEL( "TEST", "<<Add to signature test>>" );
        signature1.add<STransformComponent>();
        signature1.add<STextureComponent>();

        LOG_CHANNEL( "TEST", signature1.toString() );
        LOG_CHANNEL( "TEST", "");


        LOG_CHANNEL( "TEST", "<<Remove from signature test>>" );
        signature1.remove( TINDEX( STransformComponent ) );

        LOG_CHANNEL( "TEST", signature1.toString() );
        LOG_CHANNEL( "TEST", "");


        LOG_CHANNEL( "TEST", "<<Includes signature test>>" );
        LOG_CHANNEL( "TEST", signature1.includes( TINDEX( STextureComponent ) ) );
        LOG_CHANNEL( "TEST", "");


        LOG_CHANNEL( "TEST", "<<Signature equality test>>" );
        SComponentSetSignature signature2;

        signature2.add( TINDEX( STextureComponent ) );

        LOG_CHANNEL( "TEST", ( signature1 == signature2 ) );
        LOG_CHANNEL( "TEST", "");
    }

} // namespace test
    
} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_SET_SIGNATURE_TEST_H__