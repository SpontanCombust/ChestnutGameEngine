#include "component_set_signature.hpp"

namespace chestnut
{    
    SComponentSetSignature::SComponentSetSignature( const SComponentSetSignature& other ) 
    {
        componentTindexes = std::set< std::type_index >( other.componentTindexes );
    }

    void SComponentSetSignature::add( std::type_index tindex ) 
    {
        componentTindexes.insert( tindex );
    }

    void SComponentSetSignature::remove( std::type_index tindex ) 
    {
        componentTindexes.erase( tindex );
    }

    bool SComponentSetSignature::includes( std::type_index tindex ) const
    {
        auto it = componentTindexes.find( tindex ); 
        auto end = componentTindexes.end();
        return it != end;
    }

    bool SComponentSetSignature::isEqualTo( const SComponentSetSignature& other ) const
    {
        return componentTindexes == other.componentTindexes;
    }

    bool SComponentSetSignature::operator==( const SComponentSetSignature& other ) const
    {
        return isEqualTo( other );
    }

    bool SComponentSetSignature::isEmpty() 
    {
        return componentTindexes.empty();
    }

    const std::string SComponentSetSignature::toString() const
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
