#include "component_set_signature.hpp"

namespace chestnut
{    
    SComponentSetSignature::SComponentSetSignature( const SComponentSetSignature& other ) 
    {
        componentTindexes = std::set< componenttindex_t >( other.componentTindexes );
    }

    SComponentSetSignature& SComponentSetSignature::operator=( const SComponentSetSignature& other ) 
    {
        componentTindexes = std::set< componenttindex_t >( other.componentTindexes );
        return *this;
    }

    SComponentSetSignature& SComponentSetSignature::add( componenttindex_t compTindex ) 
    {
        componentTindexes.insert( compTindex );
        return *this;
    }

    SComponentSetSignature& SComponentSetSignature::remove( componenttindex_t compTindex ) 
    {
        componentTindexes.erase( compTindex );
        return *this;
    }

    bool SComponentSetSignature::includes( componenttindex_t compTindex ) const
    {
        auto it = componentTindexes.find( compTindex ); 
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



    SComponentSetSignature signatureSum( const SComponentSetSignature& lhs, const SComponentSetSignature& rhs ) 
    {
        SComponentSetSignature sum = lhs;

        for( const componenttindex_t& tindex : rhs.componentTindexes )
        {
            sum.add( tindex );
        }

        return sum;
    }

    SComponentSetSignature operator+( const SComponentSetSignature& lhs, const SComponentSetSignature& rhs ) 
    {
        return signatureSum( lhs, rhs );
    }

    SComponentSetSignature signatureDifference( const SComponentSetSignature& lhs, const SComponentSetSignature& rhs ) 
    {
        SComponentSetSignature diff = lhs;

        for( const componenttindex_t& tindex : rhs.componentTindexes )
        {
            diff.remove( tindex );
        }

        return diff;
    }

    SComponentSetSignature operator-( const SComponentSetSignature& lhs, const SComponentSetSignature& rhs ) 
    {
        return signatureDifference( lhs, rhs );
    }

} // namespace chestnut
