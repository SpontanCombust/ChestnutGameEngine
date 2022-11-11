#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/types.hpp"

namespace chestnut::engine
{
    class CHESTNUT_API ISystem
    {
    protected:
        systempriority_t m_priority;

    public:
        ISystem();
        ISystem(systempriority_t priority);
        virtual ~ISystem() = default;

        void setPriority(systempriority_t priority);
        systempriority_t getPriority() const;
    };
    
} // namespace chestnut::engine

