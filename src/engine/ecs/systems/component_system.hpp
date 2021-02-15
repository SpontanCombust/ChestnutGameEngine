#ifndef __CHESTNUT_COMPONENT_SYSTEM_H__
#define __CHESTNUT_COMPONENT_SYSTEM_H__

#include "../system.hpp"
#include "../component_database.hpp"

#include <list>

namespace chestnut
{
    class IComponentDrivenSystem : public ISystem
    {
    public:
        virtual bool needsAnyOfComponents( const std::list< std::type_index >& compTypeIndexes ) = 0;
        virtual void fetchComponents( const CComponentDatabase& dbRef ) = 0;
        ~IComponentDrivenSystem() {}
    };
    
} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_SYSTEM_H__