#ifndef __CHESTNUT_COMPONENT_H__
#define __CHESTNUT_COMPONENT_H__

#include <string>

namespace chestnut
{
    struct SComponent
    {
        uint64_t parentGUID; //TODO implement uuid distribution

        static const std::string getTypeStatic();
        inline virtual const std::string getType() { return getTypeStatic(); };
    };

} // namespace chestnut 

#endif // __CHESTNUT_COMPONENT_H__
