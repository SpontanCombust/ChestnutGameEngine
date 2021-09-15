#include "event_listener.hpp"

namespace chestnut
{    
    void IEventListener::setEnabled( bool enabled ) 
    {
        m_isEnabled = enabled;
    }

    bool IEventListener::isEnabled() const
    {
        return m_isEnabled;
    }

} // namespace chestnut
