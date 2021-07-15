#ifndef __CHESTNUT_ENTITY_REQUEST_H__
#define __CHESTNUT_ENTITY_REQUEST_H__

#include "entity_signature.hpp"

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
        CEntitySignature oldSignature;
        CEntitySignature newSignature;
    };
    
} // namespace chestnut


#endif // __CHESTNUT_ENTITY_REQUEST_H__