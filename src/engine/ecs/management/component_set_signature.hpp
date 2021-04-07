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


        void add( componenttindex_t compTindex );

        template< typename T >
        void add();


        void remove( componenttindex_t compTindex );

        template< typename T >
        void remove();


        bool includes( componenttindex_t compTindex ) const;

        template< typename T >
        bool includes() const;


        bool isEqualTo( const SComponentSetSignature& other ) const;

        bool operator==( const SComponentSetSignature& other ) const;


        bool isEmpty();


        const std::string toString() const;
    };
    
} // namespace chestnut


#include "component_set_signature.tpp"


#endif // __CHESTNUT_COMPONENT_SET_SIGNATURE_H__