#ifndef __CHESTNUT_COMPONENT_SYSTEM_H__
#define __CHESTNUT_COMPONENT_SYSTEM_H__

#include "component_database.hpp"

#include <forward_list>

namespace chestnut
{
    namespace ComponentSystemPriority
    {
        // the bigger the number, the lower the priority
        const unsigned int HIGHEST = 0x00000000;
        const unsigned int LOWEST  = 0x7fffffff;
        const unsigned int DEFAULT = 0x0000000f;
    }

    class IComponentSystem
    {
    private:
        unsigned int m_priority;

    public:
        virtual ~IComponentSystem() {}
        virtual bool needsAnyOfComponents( const std::forward_list< std::type_index >& compTypeIndexes ) = 0;
        virtual void fetchComponents( const CComponentDatabase& dbRef ) = 0;
        virtual void update( float deltaTime ) = 0;

        void setPriority( unsigned int priority );
        unsigned int getPriority();
    };
    
} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_SYSTEM_H__