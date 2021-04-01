#include "component_set.hpp"

#include "engine/debug/debug.hpp"

namespace chestnut
{
    SComponentSet::SComponentSet() 
    {
        componentOwnerID = ENTITY_ID_INVALID;
    }

    SComponentSet::SComponentSet( entityid_t _componentOwnerID ) 
    {
        componentOwnerID = _componentOwnerID;
    }

    void SComponentSet::addComponent( IComponent *component ) 
    {
        if( !component )
        {
            LOG_CHANNEL( "COMPONENT_SET", "Tried adding a null component!" );
            return;
        }
        if( component->ownerID != componentOwnerID )
        {
            LOG_CHANNEL( "COMPONENT_SET", "Tried adding a component that belong to different entity!" );
            LOG_CHANNEL( "COMPONENT_SET", "This set is for entity: " << componentOwnerID );
            LOG_CHANNEL( "COMPONENT_SET", "Owner of the component is: " << component->ownerID );
            return;
        }

        mapTindexToComponent[ TINDEX( *component ) ] = component;
    }

    void SComponentSet::removeComponent( std::type_index tindex ) 
    {
        mapTindexToComponent.erase( tindex );
    }

    SComponentSetSignature SComponentSet::getSignature() const
    {
        SComponentSetSignature signature;

        for( const auto& [ tindex, comp ] : mapTindexToComponent )
        {
            signature.add( tindex );
        }

        return signature;
    }

} // namespace chestnut
