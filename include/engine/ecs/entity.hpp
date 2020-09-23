#ifndef __CHESTNUT_ENTITY_H__
#define __CHESTNUT_ENTITY_H__

#include "component.hpp"

#include <string>
#include <unordered_map>

namespace chestnut
{    
    class CEntity
    {
    protected:
        uint64_t m_GUID;
        std::unordered_map< std::string, SComponent* > m_components;

    public:
        void setGUID( uint64_t guid );
        uint64_t getGUID() const;

        bool addComponent( SComponent *component );
        bool hasComponent( const std::string componentType ) const;
        SComponent *getComponent( const std::string componentType );
    };

} // namespace chestnut 

#endif // __CHESTNUT_ENTITY_H__
