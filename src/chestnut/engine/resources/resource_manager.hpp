#ifndef __CHESTNUT_ENGINE_RESOURCE_MANAGER_H__
#define __CHESTNUT_ENGINE_RESOURCE_MANAGER_H__

#include "resource.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>

namespace chestnut::engine
{
    class CResourceManager
    {
    private:
        static std::unordered_map< size_t, std::shared_ptr<IResource> > m_mapHashToResource;
        static std::hash<std::string> m_pathHasher;
        
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
        // If something is still using one of the resources it won't be freed until that something lets go of it 
        static void freeAllResources();


    private:
        static size_t hashPaths(const std::string& p);

        template<typename ...Args>
        static size_t hashPaths(const std::string& p, Args&& ...args);

        static size_t hashType(std::type_index tindex);
    };

} // namespace chestnut::engine


#include "resource_manager.inl"


#endif // __CHESTNUT_ENGINE_RESOURCE_MANAGER_H__