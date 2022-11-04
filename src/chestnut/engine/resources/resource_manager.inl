#include "chestnut/engine/resources/resource.hpp"
#include "chestnut/engine/resources/texture2d_resource.hpp"
#include "chestnut/engine/resources/shader_program_resource.hpp"
#include "chestnut/engine/resources/font_resource.hpp"

#include <type_traits>

namespace chestnut::engine
{
    inline size_t CResourceManager::hashPaths(const std::string& p)
    {
        return m_pathHasher(p);
    }

    template<typename ...Args>
    inline size_t CResourceManager::hashPaths(const std::string& p, Args&& ...args)
    {

        return m_pathHasher(p) ^ hashPaths(args...);
    }

    inline size_t CResourceManager::hashType(std::type_index tindex)
    {
        static std::hash<std::type_index> hasher;
        return hasher(tindex);
    }



    template<typename R, typename ...Args>
    tl::expected<std::shared_ptr<R>, const char *> CResourceManager::loadResource(Args&&... args)
    {
        const size_t hash = hashType(typeid(R)) ^ hashPaths(args...);

        tl::expected<std::shared_ptr<R>, const char *> resource = tl::make_unexpected("");

        if constexpr( std::is_same_v<R, CShaderProgramResource> ) {
            resource = R::loadFromFiles(std::forward<Args>(args)...);
        } else {
            resource = R::loadFromFile(std::forward<Args>(args)...);
        }

        if(resource) {
            m_mapHashToResource[hash] = resource.value();
        }

        return resource;
    }

    template<typename R, typename ...Args>
    tl::optional<std::shared_ptr<R>> CResourceManager::getResource(Args&&... args)
    {
        const size_t hash = hashType(typeid(R)) ^ hashPaths(args...);

        auto it = m_mapHashToResource.find( hash );
        if( it != m_mapHashToResource.end() ) {
            return std::dynamic_pointer_cast<R>(it->second);
        }

        return tl::nullopt;
    }

    template<typename R, typename ...Args>
    tl::expected<std::shared_ptr<R>, const char *> CResourceManager::getOrLoadResource(Args&&... args)
    {
        const size_t hash = hashType(typeid(R)) ^ hashPaths(args...);

        tl::expected<std::shared_ptr<R>, const char *> resource = tl::make_unexpected("");

        auto it = m_mapHashToResource.find( hash );
        if( it != m_mapHashToResource.end() ) {
            resource = std::dynamic_pointer_cast<R>(it->second);
        } else {
            if constexpr( std::is_same_v<R, CShaderProgramResource> ) {
                resource = R::loadFromFiles(std::forward<Args>(args)...);
            } else {
                resource = R::loadFromFile(std::forward<Args>(args)...);
            }

            if(resource) {
                m_mapHashToResource[hash] = resource.value();
            }
        }

        return resource;
    }

    template<typename R, typename ...Args>
    bool CResourceManager::isResourceLoaded(Args&&... args)
    {
        const size_t hash = hashType(typeid(R)) ^ hashPaths(args...);

        return m_mapHashToResource.find( hash ) != m_mapHashToResource.end();
    }

    template<typename R, typename ...Args>
    bool CResourceManager::freeResource(Args&&... args)
    {
        const size_t hash = hashType(typeid(R)) ^ hashPaths(args...);

        return m_mapHashToResource.erase(hash) > 0;
    }

} // namespace chestnut::engine
