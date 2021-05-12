#ifndef __CHESTNUT_COMPONENT_VECTOR_WRAPPER_H__
#define __CHESTNUT_COMPONENT_VECTOR_WRAPPER_H__

#include "../component.hpp"

#include <string>
#include <vector>

namespace chestnut
{
    class IComponentVectorWrapper
    {
    public:
        virtual ~IComponentVectorWrapper() {}

        // Allocates and pushes back a component with given owner ID, returns a pointer to this component
        virtual IComponent *push_back( entityid_t ownerID ) = 0;
        // Returns a pointer to component at a given position in the vector, returns null on error
        virtual IComponent *at( size_t i ) = 0;
        // Returns a pointer to component with given owner ID, returns null on failure
        virtual IComponent *find( entityid_t ownerID ) = 0;
        // Erases a component with given owner ID if it exists
        virtual void erase( entityid_t ownerID ) = 0;
        // Erases all elements
        virtual void clear() = 0;
        // Returns number of stored components
        virtual size_t size() = 0;
        // Returns the capacity of vector
        virtual size_t capacity() = 0;
        // Increases capacity to given amount without actually creating components
        virtual void reserve( size_t newCapacity ) = 0;

        virtual const std::string toString() const = 0;
    };

    template< typename T >
    class CComponentVectorWrapper : public IComponentVectorWrapper
    {
    public:
        std::vector<T> vec;

        ~CComponentVectorWrapper();

        // Allocates and pushes back a component with given owner ID, returns a pointer to this component
        IComponent *push_back( entityid_t ownerID ) override;
        // Returns a pointer to component at a given position in the vector, returns null on error
        virtual IComponent *at( size_t i ) override;
        // Returns a pointer to component with given owner ID, returns null on failure
        IComponent *find( entityid_t ownerID ) override;
        // Erases a component with given owner ID if it exists
        void erase( entityid_t ownerID ) override;
        // Erases all elements
        void clear() override;
        // Returns number of stored components
        size_t size() override;
        // Returns the capacity of vector
        size_t capacity() override;
        // Increases capacity to given amount without actually creating components
        void reserve( size_t newCapacity ) override;
        
        const std::string toString() const override;
    };
    
} // namespace chestnut


#include "component_vector_wrapper.tpp"


#endif // __CHESTNUT_COMPONENT_VECTOR_WRAPPER_H__