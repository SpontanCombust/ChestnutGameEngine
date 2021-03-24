#ifndef __CHESTNUT_COMPONENT_VECTOR_WRAPPER_H__
#define __CHESTNUT_COMPONENT_VECTOR_WRAPPER_H__

#include "../component.hpp"

#include <vector>

namespace chestnut
{
    class IComponentVectorWrapper
    {
    public:
        virtual ~IComponentVectorWrapper() {}

        virtual IComponent *add( entityid_t ownerID ) = 0;
        virtual IComponent *get( entityid_t ownerID ) = 0;
        virtual void erase( entityid_t ownerID ) = 0;
    };

    template< typename T >
    class CComponentVectorWrapper : public IComponentVectorWrapper
    {
    public:
        std::vector<T> vec;

        IComponent *add( entityid_t ownerID ) override;
        IComponent *get( entityid_t ownerID ) override;
        void erase( entityid_t ownerID ) override;
    };
    
} // namespace chestnut


#include "component_vector_wrapper.tpp"


#endif // __CHESTNUT_COMPONENT_VECTOR_WRAPPER_H__