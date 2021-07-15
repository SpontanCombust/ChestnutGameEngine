#include "entity_signature.hpp"

namespace chestnut
{    
    CEntitySignature& CEntitySignature::add( componenttindex_t compTindex ) 
    {
        m_setComponentTindexes.insert( compTindex );
        
        return *this;
    }

    CEntitySignature& CEntitySignature::remove( componenttindex_t compTindex ) 
    {
        
        m_setComponentTindexes.erase( compTindex );

        return *this;
    }

    bool CEntitySignature::includes( componenttindex_t compTindex ) const
    {
        auto it = m_setComponentTindexes.find( compTindex ); 
        auto end = m_setComponentTindexes.end();
        
        return it != end;
    }

    bool CEntitySignature::isEqualTo( const CEntitySignature& other ) const
    {
        return m_setComponentTindexes == other.m_setComponentTindexes;
    }

    bool CEntitySignature::operator==( const CEntitySignature& other ) const
    {
        return isEqualTo( other );
    }

    bool CEntitySignature::isEmpty() 
    {
        return m_setComponentTindexes.empty();
    }

    const std::string CEntitySignature::toString() const
    {
        std::string str;

        str += "(";
        if( !m_setComponentTindexes.empty() )
        {
            auto it = m_setComponentTindexes.begin();
            str += it->name();

            ++it;
            for(; it != m_setComponentTindexes.end(); ++it )
            {
                str += ", ";
                str += it->name();
            }
        }
        str += ")";

        return str;
    }



    CEntitySignature signatureSum( const CEntitySignature& lhs, const CEntitySignature& rhs ) 
    {
        CEntitySignature sum = lhs;

        for( const componenttindex_t& tindex : rhs.m_setComponentTindexes )
        {
            sum.add( tindex );
        }

        return sum;
    }

    CEntitySignature operator+( const CEntitySignature& lhs, const CEntitySignature& rhs ) 
    {
        return signatureSum( lhs, rhs );
    }

    CEntitySignature signatureDifference( const CEntitySignature& lhs, const CEntitySignature& rhs ) 
    {
        CEntitySignature diff = lhs;

        for( const componenttindex_t& tindex : rhs.m_setComponentTindexes )
        {
            diff.remove( tindex );
        }

        return diff;
    }

    CEntitySignature operator-( const CEntitySignature& lhs, const CEntitySignature& rhs ) 
    {
        return signatureDifference( lhs, rhs );
    }

} // namespace chestnut
