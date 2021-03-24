#include "component_bundle.hpp"

namespace chestnut
{    
    void SComponentBundle::addComponent( IComponent *component ) 
    {
        tindexToComponentMap[ TINDEX( *component ) ] = component;
    }

    void SComponentBundle::removeComponent( std::type_index tindex ) 
    {
        tindexToComponentMap.erase( tindex );
    }

    SComponentBundleSignature SComponentBundle::getSignature() 
    {
        SComponentBundleSignature signature;

        for( const auto& [ tindex, comp ] : tindexToComponentMap )
        {
            signature.add( tindex );
        }

        return signature;
    }

} // namespace chestnut
