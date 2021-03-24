#include "component_bundle_signature.hpp"

namespace chestnut
{    
    SComponentBundleSignature::SComponentBundleSignature( const SComponentBundleSignature& other ) 
    {
        componentTindexes = std::set< std::type_index >( other.componentTindexes );
    }

    void SComponentBundleSignature::add( std::type_index tindex ) 
    {
        componentTindexes.insert( tindex );
    }

    void SComponentBundleSignature::remove( std::type_index tindex ) 
    {
        componentTindexes.erase( tindex );
    }

    bool SComponentBundleSignature::includes( std::type_index tindex ) 
    {
        auto it = componentTindexes.find( tindex ); 
        auto end = componentTindexes.end();
        return it != end;
    }

    bool SComponentBundleSignature::isEqualTo( const SComponentBundleSignature& other ) 
    {
        return componentTindexes == other.componentTindexes;
    }

    bool SComponentBundleSignature::operator==( const SComponentBundleSignature& other ) 
    {
        return isEqualTo( other );
    }

} // namespace chestnut
