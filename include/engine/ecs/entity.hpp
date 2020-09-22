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
        uint64_t m_GUID;
        std::unordered_map< std::string, CComponent* > m_components;

    public:
        void setGUID( uint64_t guid );
        uint64_t getGUID() const;

        bool addComponent( CComponent *component );
        bool hasComponent( const std::string componentType ) const;
        CComponent *getComponent( const std::string componentType );
    };

} /*namespace ecs*/ } // namespace engine 
