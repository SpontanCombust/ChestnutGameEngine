#include "chestnut/engine/resources/resource_manager.hpp"

namespace chestnut::engine
{
    void CResourceManager::freeUnusedResources() 
    {
        auto it = m_mapHashToResource.begin();
        while( it != m_mapHashToResource.end() )
        {
            // test if only resouce manager references the resource
            if( it->second.use_count() < 2 )
            {
                it = m_mapHashToResource.erase( it );
            }
            else
            {
                ++it;
            }
        }
    }

    void CResourceManager::freeAllResources()
    {
        m_mapHashToResource.clear();
    }

} // namespace chestnut::engine
