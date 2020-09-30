#ifndef __CHESTNUT_ENTITY_H__
#define __CHESTNUT_ENTITY_H__

#include "component.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace chestnut
{    
    class CEntity
    {
    private:
        friend class CChestnutECS;

    protected:
        uint64_t m_GUID;
        std::unordered_map< std::string, IComponent* > m_components;

    public:
        CEntity() : m_GUID( GUID_UNREGISTERED ) {}

        uint64_t getGUID() const;

        bool addComponent( IComponent *component );
        bool hasComponent( const std::string componentType ) const;
        IComponent *getComponent( const std::string componentType );

        const std::vector< std::string > getComponentTypes() const;
    };

} // namespace chestnut 

#endif // __CHESTNUT_ENTITY_H__
