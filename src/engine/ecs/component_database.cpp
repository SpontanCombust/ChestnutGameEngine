#include "engine/ecs/component_database.hpp"

namespace chestnut
{    
    void CComponentDatabase::clearComponents() 
    {
        m_componentMaps.clear();
    }

} // namespace chestnut
