#include "resource_manager.hpp"

namespace chestnut
{
    // instantiate static variables
    std::unordered_map< size_t, CResourceManager::ResourceVariant > CResourceManager::m_mapHashToResourceVariant;
    std::hash< std::string > CResourceManager::m_hasher;


    std::shared_ptr<CShaderProgramResource> CResourceManager::loadShaderProgramResource( const std::string& vertShaderPath, const std::string& fragShaderPath ) 
    {
        // a hash created from 2 other hashes (by using XOR)
        size_t hash = m_hasher( vertShaderPath ) ^ m_hasher( fragShaderPath );

        std::shared_ptr<CShaderProgramResource> resource;
        // let the exception propagate if it happens
        resource = loadShaderProgramResourceFromFiles( vertShaderPath, fragShaderPath );
        
        m_mapHashToResourceVariant[ hash ] = resource;

        return resource;
    }

    std::shared_ptr<CShaderProgramResource> CResourceManager::getShaderProgramResource( const std::string& vertShaderPath, const std::string& fragShaderPath ) 
    {
        size_t hash = m_hasher( vertShaderPath ) ^ m_hasher( fragShaderPath );

        std::shared_ptr<CShaderProgramResource> resource;

        auto it = m_mapHashToResourceVariant.find( hash );
        if( it != m_mapHashToResourceVariant.end() )
        {
            ResourceVariant variant = it->second;
            resource = std::get< std::shared_ptr<CShaderProgramResource> >( variant );
        }
        // otherwise the resource will stay invalid and will be returned as such

        return resource;
    }

    bool CResourceManager::isShaderProgramResourceLoaded(const std::string& vertShaderPath, const std::string& fragShaderPath) 
    {
        size_t hash = m_hasher( vertShaderPath ) ^ m_hasher( fragShaderPath );

        if( m_mapHashToResourceVariant.find( hash ) != m_mapHashToResourceVariant.end() )
        {
            return true;
        }
        
        return false;
    }

    void CResourceManager::freeShaderProgramResource( const std::string& vertShaderPath, const std::string& fragShaderPath ) 
    {
        size_t hash = m_hasher( vertShaderPath ) ^ m_hasher( fragShaderPath );

        m_mapHashToResourceVariant.erase( hash );
    }




    std::shared_ptr<CTexture2DResource> CResourceManager::loadTexture2DResource( const std::string& texturePath ) 
    {
        size_t hash = m_hasher( texturePath );

        std::shared_ptr<CTexture2DResource> resource;
        // let the exception propagate if it happens
        resource = loadTexture2DResourceFromFile( texturePath );

        m_mapHashToResourceVariant[ hash ] = resource;

        return resource;
    }

    std::shared_ptr<CTexture2DResource> CResourceManager::getTexture2DResource( const std::string& texturePath ) 
    {
        size_t hash = m_hasher( texturePath );

        std::shared_ptr<CTexture2DResource> resource;

        auto it = m_mapHashToResourceVariant.find( hash );
        if( it != m_mapHashToResourceVariant.end() )
        {
            ResourceVariant variant = it->second;
            resource = std::get< std::shared_ptr<CTexture2DResource> >( variant );
        }
        // otherwise the resource will stay invalid and will be returned as such

        return resource;
    }

    bool CResourceManager::isTexture2DResourceLoaded( const std::string& texturePath ) 
    {
        size_t hash = m_hasher( texturePath );

        if( m_mapHashToResourceVariant.find( hash ) != m_mapHashToResourceVariant.end() )
        {
            return true;
        }
        
        return false;
    }

    void CResourceManager::freeTexture2DResource( std::string& texturePath ) 
    {
        size_t hash = m_hasher( texturePath );

        m_mapHashToResourceVariant.erase( hash );
    }




    std::shared_ptr<CFontResource> CResourceManager::loadFontResource( const std::string& fontPath ) 
    {
        size_t hash = m_hasher( fontPath );

        std::shared_ptr<CFontResource> resource;
        // let the exception propagate if it happens
        resource = loadFontResourceFromFile( fontPath );

        m_mapHashToResourceVariant[ hash ] = resource;

        return resource;
    }

    std::shared_ptr<CFontResource> CResourceManager::getFontResource( const std::string& fontPath ) 
    {
        size_t hash = m_hasher( fontPath );

        std::shared_ptr<CFontResource> resource;

        auto it = m_mapHashToResourceVariant.find( hash );
        if( it != m_mapHashToResourceVariant.end() )
        {
            ResourceVariant variant = it->second;
            resource = std::get< std::shared_ptr<CFontResource> >( variant );
        }
        // otherwise the resource will stay invalid and will be returned as such

        return resource;
    }

    bool CResourceManager::isFontResourceLoaded( const std::string& fontPath ) 
    {
        size_t hash = m_hasher( fontPath );

        if( m_mapHashToResourceVariant.find( hash ) != m_mapHashToResourceVariant.end() )
        {
            return true;
        }
        
        return false;
    }

    void CResourceManager::freeFontResource( std::string& fontPath ) 
    {
        size_t hash = m_hasher( fontPath );

        m_mapHashToResourceVariant.erase( hash );
    }

} // namespace chestnut
