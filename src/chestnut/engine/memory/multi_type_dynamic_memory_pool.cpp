#include "chestnut/engine/memory/multi_type_dynamic_memory_pool.hpp"

#include <cstdlib>

namespace chestnut::engine
{
    CMultiTypeDynamicMemoryPool::CMultiTypeDynamicMemoryPool( CMultiTypeDynamicMemoryPool&& other ) 
    {
        m_mapTypeToPtrStack = std::move( other.m_mapTypeToPtrStack );
    }

    CMultiTypeDynamicMemoryPool::~CMultiTypeDynamicMemoryPool() 
    {
        void *ptr;
        for( auto& [ type, ptrStack ] : m_mapTypeToPtrStack )
        {
            while( !ptrStack.empty() )
            {
                ptr = ptrStack.top();
                std::free( ptr );
                ptrStack.pop();
            }
        }
    }

} // namespace chestnut::engine
