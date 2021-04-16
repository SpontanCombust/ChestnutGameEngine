#ifndef __CHESTNUT_ENTITY_REQUEST_H__
#define __CHESTNUT_ENTITY_REQUEST_H__

#include "component_set_signature.hpp"

namespace chestnut
{
    enum class EEntityRequestType
    {
        CREATE_ENTITY,
        DESTROY_ENTITY,
        CREATE_COMPONENT,
        DESTROY_COMPONENT
    };

    struct SEntityRequest
    {
        EEntityRequestType type;
        entityid_t id;
        SComponentSetSignature oldSignature;
        SComponentSetSignature newSignature;
    };
    
} // namespace chestnut


#endif // __CHESTNUT_ENTITY_REQUEST_H__