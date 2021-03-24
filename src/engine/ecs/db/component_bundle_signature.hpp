#ifndef __CHESTNUT_COMPONENT_BUNDLE_SIGNATURE_H__
#define __CHESTNUT_COMPONENT_BUNDLE_SIGNATURE_H__

#include "engine/misc/tindex.hpp"

#include <typeindex>
#include <set>
#include <vector>

namespace chestnut
{
    struct SComponentBundleSignature
    {
        std::set< std::type_index > componentTindexes;

        SComponentBundleSignature() = default;
        SComponentBundleSignature( const SComponentBundleSignature& other );


        void add( std::type_index tindex );

        template< typename T >
        void add();


        void remove( std::type_index tindex );

        template< typename T >
        void remove();


        bool includes( std::type_index tindex );

        template< typename T >
        bool includes();


        bool isEqualTo( const SComponentBundleSignature& other );

        bool operator==( const SComponentBundleSignature& other );
    };
    
} // namespace chestnut


#include "component_bundle_signature.tpp"


#endif // __CHESTNUT_COMPONENT_BUNDLE_SIGNATURE_H__