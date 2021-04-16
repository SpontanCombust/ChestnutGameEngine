#include "multi_type_dynamic_memory_pool.hpp"

namespace chestnut
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
                free( ptr );
                ptrStack.pop();
            }
        }
    }

} // namespace chestnut
