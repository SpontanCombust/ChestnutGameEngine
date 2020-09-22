#include "engine/ecs/component.hpp"

#include "engine/debug/debug.hpp"

namespace chestnut
{
    void CComponent::setParentGUID( const uint64_t guid ) 
    {
        m_parentGUID = guid;
    }
    
    uint64_t CComponent::getParentGUID() const
    {
        return m_parentGUID;
    }

    const std::string CComponent::getTypeStatic()
    {
        return "";
    }

} // namespace chestnut 
