#ifndef __CHESTNUT_COMPONENT_SET_SIGNATURE_H__
#define __CHESTNUT_COMPONENT_SET_SIGNATURE_H__

#include "engine/misc/tindex.hpp"

#include <set>
#include <string>
#include <typeindex>
#include <vector>

namespace chestnut
{
    struct SComponentSetSignature
    {
        std::set< std::type_index > componentTindexes;

        SComponentSetSignature() = default;
        SComponentSetSignature( const SComponentSetSignature& other );


        void add( std::type_index tindex );

        template< typename T >
        void add();


        void remove( std::type_index tindex );

        template< typename T >
        void remove();


        bool includes( std::type_index tindex ) const;

        template< typename T >
        bool includes() const;


        bool isEqualTo( const SComponentSetSignature& other ) const;

        bool operator==( const SComponentSetSignature& other ) const;


        const std::string toString() const;
    };
    
} // namespace chestnut


#include "component_set_signature.tpp"


#endif // __CHESTNUT_COMPONENT_SET_SIGNATURE_H__