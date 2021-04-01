#ifndef __CHESTNUT_COMPONENT_SET_H__
#define __CHESTNUT_COMPONENT_SET_H__

#include "component_set_signature.hpp"
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
     * A single set corresponds to one entity. A set has a signature that
     * is deducted by checking types of stored component pointers.
     */
    struct SComponentSet
    {
        entityid_t componentOwnerID;
        std::unordered_map< std::type_index, IComponent *> mapTindexToComponent;

        SComponentSet();
        SComponentSet( entityid_t _componentOwnerID );

        void addComponent( IComponent *component );
        void removeComponent( std::type_index tindex );

        SComponentSetSignature getSignature() const;
    };
    
} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_SET_H__