#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/resource.hpp"

#include <tl/optional.hpp>
#include <tl/expected.hpp>

#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>

namespace chestnut::engine
{
    /**
     * @brief 
     * Class designed to centralize resource sharing in order to minimize memory and time overhead.
     * 
     * @details
     * A resource is identified in the manager by both its location and type,
     * so a specific location can be used by mutiple resources of different types,
     * but only one of each type.
     * 
     * Location usually means path to a file in the system, but it can also be an arbitrary string in case of addResource().
     */
    class CHESTNUT_API CResourceManager
    {
    private:
        std::unordered_map<size_t, std::shared_ptr<IResource>> m_mapHashToResource;
        
    public:
        /**
         * @brief Loads the resource from specified location. It does it even if that resource has been loaded before.
         * 
         * @tparam R resource type
         * @param location path to a resource
         * @return Resource on success, error if any problems occur during loading.
         */
        template<class R> 
        tl::expected<std::shared_ptr<R>, std::string> 
        loadResource(std::filesystem::path location);

        /**
         * @brief Returns resource if it has been loaded from specified location before.
         * 
         * @tparam R resource type
         * @param location path to a resource
         * @return Resource if it has been loaded before, nullopt otherwise.
         */
        template<class R> 
        tl::optional<std::shared_ptr<R>> 
        getResource(std::filesystem::path location);

        /**
         * @brief Returns a resource if it has been loaded from that location before or loads it if it hasn't.
         * 
         * @tparam R resource type
         * @param location path to a resource
         * @return Resource on success, error if any problems occur during loading.
         */
        template<class R> 
        tl::expected<std::shared_ptr<R>, std::string> 
        getOrLoadResource(std::filesystem::path location);

        /**
         * @brief Adds a resource directly into a manager with an option to have it put in a custom location.
         * This is especially useful if a resource has not been loaded from a file.
         * 
         * @tparam R resource type
         * @param resource new resource
         * @param customLocation optional custom location for a resource
         * @return Nothing or error in case the resource is invalid or some other resource already exists at that location.
         */
        template<class R>
        tl::expected<void, std::string> 
        addResource(std::shared_ptr<R> resource, tl::optional<std::filesystem::path> customLocation = tl::nullopt);
        
        /**
         * @brief Returns whether a resource of specified type has been loaded from given location.
         * 
         * @tparam R resource type
         * @param location path to a resource
         * @return True if resource has been loaded, false otherwise
         */
        template<class R> 
        bool isResourceLoaded(std::filesystem::path location);

        /**
         * @brief Lets go of resource of specified type has been loaded from given location.
         * 
         * @tparam R resource type
         * @param location path to a resource
         * @return True if resource was found and let go by the manager.
         */
        template<class R> 
        bool freeResource(std::filesystem::path location);

        /**
         * @brief Lets go of all resources that are not referenced anywhere else in the program, 
         * consequently freeing memory from them.
         * 
         * @return How many resources were freed
         */
        int freeUnusedResources();

        /**
         * @brief Lets go of all stored resources.
         */
        void freeAllResources();

    private:
        size_t resourceHash(std::type_index type, std::filesystem::path location);
    };

} // namespace chestnut::engine


#include "resource_manager.inl"


