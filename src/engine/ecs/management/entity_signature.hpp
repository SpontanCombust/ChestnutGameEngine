#ifndef __CHESTNUT_ENTITY_SIGNATURE_H__
#define __CHESTNUT_ENTITY_SIGNATURE_H__

#include "engine/misc/tindex.hpp"
#include "engine/types.hpp"

#include <unordered_set>
#include <string>

namespace chestnut
{
    class CEntitySignature
    {
    public:
        std::unordered_set< componenttindex_t > m_setComponentTindexes;

    public:
        CEntitySignature& add( componenttindex_t compTindex );

        template< typename T >
        CEntitySignature& add();


        CEntitySignature& remove( componenttindex_t compTindex );

        template< typename T >
        CEntitySignature& remove();


        bool includes( componenttindex_t compTindex ) const;

        template< typename T >
        bool includes() const;


        bool isEqualTo( const CEntitySignature& other ) const;

        bool operator==( const CEntitySignature& other ) const;


        bool isEmpty();


        const std::string toString() const;
    };
    

    CEntitySignature signatureSum( const CEntitySignature& lhs, const CEntitySignature& rhs );

    CEntitySignature operator+( const CEntitySignature& lhs, const CEntitySignature& rhs );

    CEntitySignature signatureDifference( const CEntitySignature& lhs, const CEntitySignature& rhs );

    CEntitySignature operator-( const CEntitySignature& lhs, const CEntitySignature& rhs );

} // namespace chestnut


#include "entity_signature.tpp"


#endif // __CHESTNUT_ENTITY_SIGNATURE_H__