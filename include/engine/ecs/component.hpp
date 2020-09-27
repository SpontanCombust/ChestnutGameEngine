#ifndef __CHESTNUT_COMPONENT_H__
#define __CHESTNUT_COMPONENT_H__

#include <string>

#define GUID_UNREGISTERED 0

namespace chestnut
{
    struct IComponent
    {
        uint64_t parentGUID;

        IComponent() : parentGUID( GUID_UNREGISTERED ) {}

        inline virtual const std::string getTypeString() = 0;
    };

} // namespace chestnut 

#endif // __CHESTNUT_COMPONENT_H__
