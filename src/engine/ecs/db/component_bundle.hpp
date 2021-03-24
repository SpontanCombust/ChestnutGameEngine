#ifndef __CHESTNUT_COMPONENT_BUNDLE_H__
#define __CHESTNUT_COMPONENT_BUNDLE_H__

#include "component_bundle_signature.hpp"
#include "../component.hpp"
#include "engine/misc/tindex.hpp"

#include <unordered_map>

namespace chestnut
{
    struct SComponentBundle
    {
        entityid_t componentOwnerID;
        std::unordered_map< std::type_index, IComponent *> tindexToComponentMap;


        void addComponent( IComponent *component );
        void removeComponent( std::type_index tindex );

        SComponentBundleSignature getSignature();
    };
    
} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_BUNDLE_H__