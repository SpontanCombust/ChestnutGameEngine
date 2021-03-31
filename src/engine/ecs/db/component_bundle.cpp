#include "component_bundle.hpp"

namespace chestnut
{

    SComponentBundle::SComponentBundle() 
    {
        componentOwnerID = ENTITY_ID_INVALID;
    }

    SComponentBundle::SComponentBundle( entityid_t _componentOwnerID ) 
    {
        componentOwnerID = _componentOwnerID;
    }

    void SComponentBundle::addComponent( IComponent *component ) 
    {
        if( component )
        {
            mapTindexToComponent[ TINDEX( *component ) ] = component;
        }
    }

    void SComponentBundle::removeComponent( std::type_index tindex ) 
    {
        mapTindexToComponent.erase( tindex );
    }

    SComponentBundleSignature SComponentBundle::getSignature() const
    {
        SComponentBundleSignature signature;

        for( const auto& [ tindex, comp ] : mapTindexToComponent )
        {
            signature.add( tindex );
        }

        return signature;
    }

} // namespace chestnut
