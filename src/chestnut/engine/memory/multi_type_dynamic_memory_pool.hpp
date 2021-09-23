#ifndef __CHESTNUT_MULTI_TYPE_FLEXIBLE_MEMORY_POOL_H__
#define __CHESTNUT_MULTI_TYPE_FLEXIBLE_MEMORY_POOL_H__

#include <stack>
#include <typeindex>
#include <unordered_map>

namespace chestnut
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
    
} // namespace chestnut


#include "multi_type_dynamic_memory_pool.tpp"


#endif // __CHESTNUT_MULTI_TYPE_FLEXIBLE_MEMORY_POOL_H__