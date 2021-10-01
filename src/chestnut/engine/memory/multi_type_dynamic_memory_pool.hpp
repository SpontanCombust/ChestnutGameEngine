#ifndef __CHESTNUT_ENGINE_MULTI_TYPE_DYNAMIC_MEMORY_POOL_H__
#define __CHESTNUT_ENGINE_MULTI_TYPE_DYNAMIC_MEMORY_POOL_H__

#include <stack>
#include <typeindex>
#include <unordered_map>

namespace chestnut::engine
{
    class CMultiTypeDynamicMemoryPool
    {
    private:
        std::unordered_map< std::type_index, std::stack< void * > > m_mapTypeToPtrStack;

    public:
        CMultiTypeDynamicMemoryPool() = default;

        CMultiTypeDynamicMemoryPool( const CMultiTypeDynamicMemoryPool& ) = delete; // we don't copy the pointers

        CMultiTypeDynamicMemoryPool( CMultiTypeDynamicMemoryPool&& other );

        ~CMultiTypeDynamicMemoryPool();

        // Return an allocated pointer of type T
        // Transfers the ownership onto user
        template< typename T >
        T *create();

        // Takes the ownership over pointer of type T
        template< typename T >
        void remove( T *ptr );
    };
    
} // namespace chestnut::engine


#include "multi_type_dynamic_memory_pool.tpp"


#endif // __CHESTNUT_ENGINE_MULTI_TYPE_DYNAMIC_MEMORY_POOL_H__