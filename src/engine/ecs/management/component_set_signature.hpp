#ifndef __CHESTNUT_COMPONENT_SET_SIGNATURE_H__
#define __CHESTNUT_COMPONENT_SET_SIGNATURE_H__

#include "engine/misc/tindex.hpp"
#include "engine/types.hpp"

#include <set>
#include <string>
#include <vector>

namespace chestnut
{
    struct SComponentSetSignature
    {
        std::set< componenttindex_t > componentTindexes;

        SComponentSetSignature() = default;
        SComponentSetSignature( const SComponentSetSignature& other );

        SComponentSetSignature& operator=( const SComponentSetSignature& other );


        SComponentSetSignature& add( componenttindex_t compTindex );

        template< typename T >
        SComponentSetSignature& add();


        SComponentSetSignature& remove( componenttindex_t compTindex );

        template< typename T >
        SComponentSetSignature& remove();


        bool includes( componenttindex_t compTindex ) const;

        template< typename T >
        bool includes() const;


        bool isEqualTo( const SComponentSetSignature& other ) const;

        bool operator==( const SComponentSetSignature& other ) const;


        bool isEmpty();

        const std::string toString() const;
    };
    

    SComponentSetSignature signatureSum( const SComponentSetSignature& lhs, const SComponentSetSignature& rhs );

    SComponentSetSignature operator+( const SComponentSetSignature& lhs, const SComponentSetSignature& rhs );

    SComponentSetSignature signatureDifference( const SComponentSetSignature& lhs, const SComponentSetSignature& rhs );

    SComponentSetSignature operator-( const SComponentSetSignature& lhs, const SComponentSetSignature& rhs );

} // namespace chestnut


#include "component_set_signature.tpp"


#endif // __CHESTNUT_COMPONENT_SET_SIGNATURE_H__