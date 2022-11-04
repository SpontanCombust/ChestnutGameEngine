#include "chestnut/engine/ecs_impl/event_listener.hpp"

namespace chestnut::engine
{    
    void IEventListener::setEnabled( bool enabled ) 
    {
        m_isEnabled = enabled;
    }

    bool IEventListener::isEnabled() const
    {
        return m_isEnabled;
    }

} // namespace chestnut::engine
