#include <algorithm>

namespace chestnut
{    
    template<typename T>
    IComponent* CComponentVectorWrapper<T>::add( entityid_t ownerID ) 
    {
        T comp;
        comp.ownerID = ownerID;
        vec.push_back( comp );

        T *compPtr = &( vec.back() );
        return dynamic_cast<IComponent *>( compPtr );
    }

    template<typename T>
    IComponent* CComponentVectorWrapper<T>::get( entityid_t ownerID ) 
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

} // namespace chestnut
