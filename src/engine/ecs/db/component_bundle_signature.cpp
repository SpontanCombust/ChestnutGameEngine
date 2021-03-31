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

    bool SComponentBundleSignature::includes( std::type_index tindex ) const
    {
        auto it = componentTindexes.find( tindex ); 
        auto end = componentTindexes.end();
        return it != end;
    }

    bool SComponentBundleSignature::isEqualTo( const SComponentBundleSignature& other ) const
    {
        return componentTindexes == other.componentTindexes;
    }

    bool SComponentBundleSignature::operator==( const SComponentBundleSignature& other ) const
    {
        return isEqualTo( other );
    }

    const std::string SComponentBundleSignature::toString() const
    {
        std::string str;

        str += "(";
        if( !componentTindexes.empty() )
        {
            auto it = componentTindexes.begin();
            str += it->name();

            ++it;
            for(; it != componentTindexes.end(); ++it )
            {
                str += ", ";
                str += it->name();
            }
        }
        str += ")";

        return str;
    }

} // namespace chestnut
