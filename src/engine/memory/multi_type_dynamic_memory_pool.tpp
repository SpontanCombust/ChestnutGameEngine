namespace chestnut
{  
    template< typename T >
    T* CMultiTypeDynamicMemoryPool::create() 
    {
        std::stack< void * >& ptrStack = m_mapTypeToPtrStack[ TINDEX(T) ];
        void *uncastedPtr;
        T *castedPtr;

        if( ptrStack.empty() )
        {
            uncastedPtr = malloc( sizeof(T) );
        }
        else
        {
            uncastedPtr = ptrStack.top();
            ptrStack.pop();    
        }

        castedPtr = new (uncastedPtr) T();

        return castedPtr;
    }

    template<typename T>
    void CMultiTypeDynamicMemoryPool::remove( T *ptr ) 
    {
        std::stack< void * >& ptrStack = m_mapTypeToPtrStack[ TINDEX( *ptr ) ];
        ptrStack.push( static_cast< void * >( ptr ) );
    }

} // namespace chestnut
