#ifndef __CHESTNUT_COMPONENT_H__
#define __CHESTNUT_COMPONENT_H__

#include "ecs_utils.hpp"

namespace chestnut
{
    struct IComponent
    {
        guid_t parentGUID;
        IComponent() : parentGUID( GUID_UNREGISTERED ) {}
        virtual ~IComponent() {};
    };

} // namespace chestnut 

#endif // __CHESTNUT_COMPONENT_H__
