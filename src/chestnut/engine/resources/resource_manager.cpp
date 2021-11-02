#include "resource_manager.hpp"

namespace chestnut::engine
{
    // instantiate static variables
    std::unordered_map< size_t, std::shared_ptr<IResource> > CResourceManager::m_mapHashToResource;
    std::hash< std::string > CResourceManager::m_hasher;


    std::shared_ptr<CShaderProgramResource> CResourceManager::loadShaderProgramResource( const char *vertShaderPath, const char *fragShaderPath ) 
    {
        // a hash created from 2 other hashes (by using XOR)
        size_t hash = m_hasher( vertShaderPath ) ^ m_hasher( fragShaderPath );

        std::shared_ptr<CShaderProgramResource> resource;
        // let the exception propagate if it happens
        resource = loadShaderProgramResourceFromFiles( vertShaderPath, fragShaderPath );
        
        m_mapHashToResource[ hash ] = resource;

        return resource;
    }

    std::shared_ptr<CShaderProgramResource> CResourceManager::getShaderProgramResource( const char *vertShaderPath, const char *fragShaderPath ) 
    {
        size_t hash = m_hasher( vertShaderPath ) ^ m_hasher( fragShaderPath );

        std::shared_ptr<CShaderProgramResource> resource;

        auto it = m_mapHashToResource.find( hash );
        if( it != m_mapHashToResource.end() )
        {
            resource = std::dynamic_pointer_cast<CShaderProgramResource>( it->second );
        }
        // otherwise the resource will stay invalid and will be returned as such

        return resource;
    }

    std::shared_ptr<CShaderProgramResource> CResourceManager::loadOrGetShaderProgramResource(const char *vertShaderPath, const char *fragShaderPath) 
    {
        size_t hash = m_hasher( vertShaderPath ) ^ m_hasher( fragShaderPath );

        std::shared_ptr<CShaderProgramResource> resource;

        auto it = m_mapHashToResource.find( hash );
        if( it != m_mapHashToResource.end() )
        {
            resource = std::dynamic_pointer_cast< CShaderProgramResource >( it->second );
        }
        else
        {
            // let the exception propagate if it happens
            resource = loadShaderProgramResourceFromFiles( vertShaderPath, fragShaderPath );
            m_mapHashToResource[ hash ] = resource;   
        }
        
        return resource;
    }

    bool CResourceManager::isShaderProgramResourceLoaded( const char *vertShaderPath, const char *fragShaderPath ) 
    {
        size_t hash = m_hasher( vertShaderPath ) ^ m_hasher( fragShaderPath );

        if( m_mapHashToResource.find( hash ) != m_mapHashToResource.end() )
        {
            return true;
        }
        
        return false;
    }

    void CResourceManager::freeShaderProgramResource( const char *vertShaderPath, const char *fragShaderPath ) 
    {
        size_t hash = m_hasher( vertShaderPath ) ^ m_hasher( fragShaderPath );

        m_mapHashToResource.erase( hash );
    }




    std::shared_ptr<CTexture2DResource> CResourceManager::loadTexture2DResource( const char *texturePath ) 
    {
        size_t hash = m_hasher( texturePath );

        std::shared_ptr<CTexture2DResource> resource;
        // let the exception propagate if it happens
        resource = loadTexture2DResourceFromFile( texturePath );

        m_mapHashToResource[ hash ] = resource;

        return resource;
    }

    std::shared_ptr<CTexture2DResource> CResourceManager::getTexture2DResource( const char *texturePath ) 
    {
        size_t hash = m_hasher( texturePath );

        std::shared_ptr<CTexture2DResource> resource;

        auto it = m_mapHashToResource.find( hash );
        if( it != m_mapHashToResource.end() )
        {
            resource = std::dynamic_pointer_cast< CTexture2DResource >( it->second );
        }
        // otherwise the resource will stay invalid and will be returned as such

        return resource;
    }

    std::shared_ptr<CTexture2DResource> CResourceManager::loadOrGetTexture2DResource(const char *texturePath) 
    {
        size_t hash = m_hasher( texturePath );

        std::shared_ptr<CTexture2DResource> resource;

        auto it = m_mapHashToResource.find( hash );
        if( it != m_mapHashToResource.end() )
        {
            resource = std::dynamic_pointer_cast< CTexture2DResource >( it->second );
        }
        else
        {
            // let the exception propagate if it happens
            resource = loadTexture2DResourceFromFile( texturePath );
            m_mapHashToResource[ hash ] = resource;
        }

        return resource;
    }

    bool CResourceManager::isTexture2DResourceLoaded( const char *texturePath ) 
    {
        size_t hash = m_hasher( texturePath );

        if( m_mapHashToResource.find( hash ) != m_mapHashToResource.end() )
        {
            return true;
        }
        
        return false;
    }

    void CResourceManager::freeTexture2DResource( const char *texturePath ) 
    {
        size_t hash = m_hasher( texturePath );

        m_mapHashToResource.erase( hash );
    }




    std::shared_ptr<CFontResource> CResourceManager::loadFontResource( const char *fontPath ) 
    {
        size_t hash = m_hasher( fontPath );

        std::shared_ptr<CFontResource> resource;
        // let the exception propagate if it happens
        resource = loadFontResourceFromFile( fontPath );

        m_mapHashToResource[ hash ] = resource;

        return resource;
    }

    std::shared_ptr<CFontResource> CResourceManager::getFontResource( const char *fontPath ) 
    {
        size_t hash = m_hasher( fontPath );

        std::shared_ptr<CFontResource> resource;

        auto it = m_mapHashToResource.find( hash );
        if( it != m_mapHashToResource.end() )
        {
            resource = std::dynamic_pointer_cast< CFontResource >( it->second );
        }
        // otherwise the resource will stay invalid and will be returned as such

        return resource;
    }

    std::shared_ptr<CFontResource> CResourceManager::loadOrGetFontResource(const char *fontPath) 
    {
        size_t hash = m_hasher( fontPath );

        std::shared_ptr<CFontResource> resource;

        auto it = m_mapHashToResource.find( hash );
        if( it != m_mapHashToResource.end() )
        {
            resource = std::dynamic_pointer_cast< CFontResource >( it->second );
        }
        else
        {
            resource = loadFontResourceFromFile( fontPath );
            m_mapHashToResource[ hash ] = resource;
        }
        
        return resource;
    }

    bool CResourceManager::isFontResourceLoaded( const char *fontPath ) 
    {
        size_t hash = m_hasher( fontPath );

        if( m_mapHashToResource.find( hash ) != m_mapHashToResource.end() )
        {
            return true;
        }
        
        return false;
    }

    void CResourceManager::freeFontResource( const char *fontPath ) 
    {
        size_t hash = m_hasher( fontPath );

        m_mapHashToResource.erase( hash );
    }

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

} // namespace chestnut::engine
