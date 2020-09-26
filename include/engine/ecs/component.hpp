#ifndef __CHESTNUT_COMPONENT_H__
#define __CHESTNUT_COMPONENT_H__

#include <string>

namespace chestnut
{
    struct SComponent
    {
        uint64_t parentGUID; //TODO implement uuid distribution

        static const std::string getTypeStringStatic();
        inline virtual const std::string getTypeString() { return getTypeStringStatic(); };
    };

} // namespace chestnut 

#endif // __CHESTNUT_COMPONENT_H__
