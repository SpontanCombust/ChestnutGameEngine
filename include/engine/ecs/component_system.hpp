#ifndef __CHESTNUT_COMPONENT_SYSTEM_H__
#define __CHESTNUT_COMPONENT_SYSTEM_H__

#include "component.hpp"
#include "component_database.hpp"

#include <unordered_map>
#include <vector>

namespace chestnut
{
    class IComponentSystem
    {
    public:
        virtual ~IComponentSystem() {}
        virtual bool needsAnyOfComponents( const std::vector< std::type_index > compTypeIndexes ) = 0;
        virtual void fetchComponents( const CComponentDatabase& dbRef ) = 0;
        virtual void update() = 0;
    };
    
} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_SYSTEM_H__