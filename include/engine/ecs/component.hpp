#pragma once

#include "entity.hpp"

#include <string>

namespace engine { namespace ecs {

    class CComponent
    {
    protected:
        uint64_t m_parentGUID; //TODO implement uuid distribution
    public:
        void setParentGUID( const uint64_t guid );
        uint64_t getParentGUID() const;
        static const std::string getTypeStatic();
        inline virtual const std::string getType() { return getTypeStatic(); };
    };

} /*namespace ecs*/ } // namespace engine 