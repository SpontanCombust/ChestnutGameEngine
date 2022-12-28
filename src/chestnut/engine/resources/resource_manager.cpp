#include "chestnut/engine/resources/resource_manager.hpp"

namespace chestnut::engine
{
    int CResourceManager::freeUnusedResources() 
    {
        int count = 0;

        auto it = m_mapHashToResource.begin();
        while( it != m_mapHashToResource.end() )
        {
            // test if only resouce manager references the resource
            if( it->second.use_count() < 2 )
            {
                it = m_mapHashToResource.erase( it );
                ++count;
            }
            else
            {
                ++it;
            }
        }

        return count;
    }

    void CResourceManager::freeAllResources()
    {
        m_mapHashToResource.clear();
    }

    size_t CResourceManager::resourceHash(std::type_index type, std::filesystem::path location)
    {
        return std::hash<std::type_index>()(type) ^ std::filesystem::hash_value(location);
    }

} // namespace chestnut::engine
