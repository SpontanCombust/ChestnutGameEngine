#ifndef __CHESTNUT_COMPONENT_SYSTEM_H__
#define __CHESTNUT_COMPONENT_SYSTEM_H__

#include "component_database.hpp"
#include "component.hpp"

#include <unordered_map>
#include <vector>

namespace chestnut
{
    class IComponentSystem
    {
    public:
        virtual ~IComponentSystem() {}
        virtual bool needsComponents( const std::vector< std::string > compTypeStrings ) = 0;
        virtual void fetchComponents( const CComponentDatabase& dbRef ) = 0;
        virtual void manageCurrentComponents() = 0;
    };
    
} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_SYSTEM_H__