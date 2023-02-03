#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/types.hpp"
#include "chestnut/engine/ecs_impl/event_listener.hpp"

#include <unordered_map>

namespace chestnut::engine
{
    class CHESTNUT_API ISystem
    {
    private:
        std::unordered_map<std::string, IEventListener *> m_mapEventListeners;

    protected:
        systempriority_t m_priority;

    public:
        ISystem();
        ISystem(systempriority_t priority);
        virtual ~ISystem();

        void setPriority(systempriority_t priority);
        systempriority_t getPriority() const;

        virtual void onAttach() {}
        virtual void onDetach() {}

    protected:
        // System takes ownership of the pointer
        void addEventListener(const char *name, IEventListener *listener);
        void addEventListener(const char *name, IEventListener *listener, listenerpriority_t priority);
        void removeEventListener(const char *name);
    };
    
} // namespace chestnut::engine

