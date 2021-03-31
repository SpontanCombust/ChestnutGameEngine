#ifndef __CHESTNUT_COMPONENT_BUNDLE_SIGNATURE_H__
#define __CHESTNUT_COMPONENT_BUNDLE_SIGNATURE_H__

#include "engine/misc/tindex.hpp"

#include <set>
#include <string>
#include <typeindex>
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


        bool includes( std::type_index tindex ) const;

        template< typename T >
        bool includes() const;


        bool isEqualTo( const SComponentBundleSignature& other ) const;

        bool operator==( const SComponentBundleSignature& other ) const;


        const std::string toString() const;
    };
    
} // namespace chestnut


#include "component_bundle_signature.tpp"


#endif // __CHESTNUT_COMPONENT_BUNDLE_SIGNATURE_H__