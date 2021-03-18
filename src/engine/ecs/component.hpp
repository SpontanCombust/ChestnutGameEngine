#ifndef __CHESTNUT_COMPONENT_H__
#define __CHESTNUT_COMPONENT_H__

#include "engine/types.hpp"
#include "engine/constants.hpp"

namespace chestnut
{
    // Every component needs to have a default no-parameters constructor
    struct IComponent
    {
        entityid_t ownerID;
        IComponent() : ownerID( ENTITY_ID_INVALID ) {}
        virtual ~IComponent() {};
    };

} // namespace chestnut 

#endif // __CHESTNUT_COMPONENT_H__
