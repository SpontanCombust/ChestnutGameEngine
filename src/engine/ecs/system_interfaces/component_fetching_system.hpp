#ifndef __CHESTNUT_COMPONENT_FETCHING_SYSTEM_H__
#define __CHESTNUT_COMPONENT_FETCHING_SYSTEM_H__

#include "../component_database.hpp"

#include <list>

namespace chestnut
{
    class IComponentFetchingSystem
    {
    public:
        virtual bool needsAnyOfComponents( const std::list< std::type_index >& compTypeIndexes ) = 0;
        virtual void fetchComponents( const CComponentDatabase& dbRef ) = 0;
        ~IComponentFetchingSystem() {}
    };
    
} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_FETCHING_SYSTEM_H__