#include <algorithm>

namespace chestnut
{

    template<typename T>
    CComponentVectorWrapper<T>::~CComponentVectorWrapper() 
    {
        vec.clear();
    }

    template<typename T>
    IComponent* CComponentVectorWrapper<T>::push_back( entityid_t ownerID ) 
    {
        T comp;
        comp.ownerID = ownerID;
        vec.push_back( comp );

        T *compPtr = &( vec.back() );
        return dynamic_cast<IComponent *>( compPtr );
    }

    template<typename T>
    IComponent* CComponentVectorWrapper<T>::at( size_t i )
    {
        if( i >= vec.size() )
        {
            return nullptr;
        }

        return ( IComponent * )&vec[i];
    }

    template<typename T>
    IComponent* CComponentVectorWrapper<T>::find( entityid_t ownerID ) 
    {
        IComponent *retComp = nullptr;
        for( auto it = vec.begin(); it != vec.end(); ++it )
        {
            if( it->ownerID == ownerID )
            {
                retComp = &( *it );
                break;
            }
        }

        return retComp;
    }

    template<typename T>
    void CComponentVectorWrapper<T>::erase( entityid_t ownerID ) 
    {
        for( auto it = vec.begin(); it != vec.end(); ++it )
        {
            if( it->ownerID == ownerID )
            {
                vec.erase(it);
                break;
            }
        }
    }

    template<typename T>
    void CComponentVectorWrapper<T>::clear() 
    {
        vec.clear();
    }

    template<typename T>
    size_t CComponentVectorWrapper<T>::size() 
    {
        return vec.size();
    }

    template<typename T>
    size_t CComponentVectorWrapper<T>::capacity() 
    {
        return vec.capacity();
    }

    template<typename T>
    void CComponentVectorWrapper<T>::reserve( size_t newCapacity ) 
    {
        vec.reserve( newCapacity );
    }


    template<typename T>
    const std::string CComponentVectorWrapper<T>::toString() const 
    {
        std::string str;

        str += "[";
        if( !vec.empty() )
        {
            auto it = vec.begin();
            str += std::to_string( it->ownerID );
            ++it;

            for(; it != vec.end(); ++it )
            {
                str += ", " + std::to_string( it->ownerID );
            }
        }
        str += "]";

        return str;
    }


} // namespace chestnut
