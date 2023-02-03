namespace chestnut::engine
{
    template<class R> 
    tl::expected<std::shared_ptr<R>, std::string> 
    CResourceManager::loadResource(std::filesystem::path location)
    {
        const size_t hash = resourceHash(typeid(R), location);
        auto resource = R::load(location);

        if(resource.has_value()) 
        {
            m_mapHashToResource[hash] = resource.value();
        }

        return resource;
    }

    template<class R>
    tl::optional<std::shared_ptr<R>>  
    CResourceManager::getResource(std::filesystem::path location)
    {
        const size_t hash = resourceHash(typeid(R), location);

        auto it = m_mapHashToResource.find(hash);
        if(it != m_mapHashToResource.end()) 
        {
            return std::dynamic_pointer_cast<R>(it->second);
        }

        return tl::nullopt;
    }

    template<class R>
    tl::expected<std::shared_ptr<R>, std::string> 
    CResourceManager::getOrLoadResource(std::filesystem::path location)
    {
        const size_t hash = resourceHash(typeid(R), location);

        auto it = m_mapHashToResource.find(hash);
        if(it != m_mapHashToResource.end()) 
        {
            return std::dynamic_pointer_cast<R>(it->second);
        }
        else
        {
            auto resource = R::load(location);

            if(resource.has_value()) 
            {
                m_mapHashToResource[hash] = resource.value();
            }

            return resource;
        }
    }

    template<class R>
    tl::expected<void, std::string> 
    CResourceManager::addResource(std::shared_ptr<R> resource, tl::optional<std::filesystem::path> customLocation)
    {
        if(!resource)
        {
            return tl::make_unexpected("Resource in empty");
        }

        std::filesystem::path location;
        if(!customLocation.has_value())
        {
            if(!resource->m_location.has_value())
            {
                return tl::make_unexpected("Resource's location nor the custom location are valid");
            }

            location = resource->m_location.value();
        }
        else
        {
            location = customLocation.value();
        }


        const size_t hash = resourceHash(typeid(R), location);

        auto it = m_mapHashToResource.find(hash);
        if(it != m_mapHashToResource.end()) 
        {
            return tl::make_unexpected("There already is a resource at given location");
        }

        m_mapHashToResource[hash] = resource;

        return {};
    }

    template<class R>
    bool CResourceManager::isResourceLoaded(std::filesystem::path location)
    {
        const size_t hash = resourceHash(typeid(R), location);

        return m_mapHashToResource.find(hash) != m_mapHashToResource.end();
    }

    template<class R>
    bool CResourceManager::freeResource(std::filesystem::path location)
    {
        const size_t hash = resourceHash(typeid(R), location);

        return m_mapHashToResource.erase(hash) > 0;
    }

} // namespace chestnut::engine
