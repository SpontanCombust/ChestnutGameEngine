#pragma once

#include "component.hpp"

#pragma once

#include <string>
#include <unordered_map>

namespace engine { namespace ecs {
    
    class CComponent; // forward declaration

    class CEntity
    {
    protected:
        uint32_t m_id;
        std::unordered_map< std::string, CComponent* > m_components;

    public:
        void setID( uint32_t id );
        uint32_t getID() const;

        bool addComponent( CComponent *component );
        bool removeComponent( const std::string componentType );
        void removeAllComponents();
        bool hasComponent( const std::string componentType ) const;
        CComponent *getComponent( const std::string componentType );
    };

} /*namespace ecs*/ } // namespace engine 
