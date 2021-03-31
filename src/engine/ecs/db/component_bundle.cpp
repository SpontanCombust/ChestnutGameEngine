#include "component_bundle.hpp"

#include "engine/debug/debug.hpp"

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
        if( !component )
        {
            LOG_CHANNEL( "COMPONENT_BUNDLE", "Tried adding a null component!" );
            return;
        }
        if( component->ownerID != componentOwnerID )
        {
            LOG_CHANNEL( "COMPONENT_BUNDLE", "Tried adding a component that belong to different entity!" );
            LOG_CHANNEL( "COMPONENT_BUNDLE", "This bundle is for entity: " << componentOwnerID );
            LOG_CHANNEL( "COMPONENT_BUNDLE", "Owner of the component is: " << component->ownerID );
            return;
        }

        mapTindexToComponent[ TINDEX( *component ) ] = component;
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
