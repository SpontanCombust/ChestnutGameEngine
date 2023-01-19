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

        virtual void onAttach() {}
        virtual void onDetach() {}
    };
    
} // namespace chestnut::engine

