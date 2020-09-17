#pragma once

#include "entity.hpp"

#include <string>

namespace engine { namespace ecs {

    class CEntity; // forward declaration

    class CComponent
    {
    protected:
        CEntity *m_entity;
    public:
        void setParentEntity( CEntity *entity );
        CEntity *getParentEntity();
        static const std::string getTypeStatic();
        inline virtual const std::string getType() { return getTypeStatic(); };
    };

} /*namespace ecs*/ } // namespace engine 