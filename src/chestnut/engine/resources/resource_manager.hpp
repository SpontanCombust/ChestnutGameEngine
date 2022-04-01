#ifndef __CHESTNUT_ENGINE_RESOURCE_MANAGER_H__
#define __CHESTNUT_ENGINE_RESOURCE_MANAGER_H__

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

namespace chestnut::engine
{
    class CResourceManager
    {
    private:
        static std::unordered_map< size_t, std::shared_ptr<IResource> > m_mapHashToResource;
        
    public:
        // Forwards arguments to the resource type specified in template
        template<typename R, typename ...Args> 
        static std::shared_ptr<R> loadResource(Args&&... args);

        // Forwards arguments to the resource type specified in template
        // Returns empty shared_ptr if doesn't find the resource
        template<typename R, typename ...Args> 
        static std::shared_ptr<R> getResource(Args&&... args);

        // Forwards arguments to the resource type specified in template
        template<typename R, typename ...Args> 
        static std::shared_ptr<R> getOrLoadResource(Args&&... args);

        template<typename R, typename ...Args> 
        static bool isResourceLoaded(Args&&... args);

        template<typename R, typename ...Args> 
        static bool freeResource(Args&&... args);

        static void freeUnusedResources();
    };

} // namespace chestnut::engine


#include "resource_manager.inl"


#endif // __CHESTNUT_ENGINE_RESOURCE_MANAGER_H__