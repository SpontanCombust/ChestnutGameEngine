#ifndef __CHESTNUT_COMPONENT_BUNDLE_H__
#define __CHESTNUT_COMPONENT_BUNDLE_H__

#include "component_bundle_signature.hpp"
#include "../component.hpp"
#include "engine/misc/tindex.hpp"

#include <unordered_map>

namespace chestnut
{
    /**
     * @brief A struct containing component pointers belonging to one entity
     * 
     * @details 
     * A data structure used to move around component pointers.
     * A single bundle corresponds to one entity. A bundle has a signature that
     * is deducted by checking types of stored component pointers.
     */
    struct SComponentBundle
    {
        entityid_t componentOwnerID;
        std::unordered_map< std::type_index, IComponent *> mapTindexToComponent;

        SComponentBundle();
        SComponentBundle( entityid_t _componentOwnerID );

        void addComponent( IComponent *component );
        void removeComponent( std::type_index tindex );

        SComponentBundleSignature getSignature() const;
    };
    
} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_BUNDLE_H__