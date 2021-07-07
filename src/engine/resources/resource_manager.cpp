#include "resource_manager.hpp"

namespace chestnut
{
    size_t CResourceManager::strHash(const std::string& str) 
    {
        return std::hash< std::string >()( str );
    }

    std::shared_ptr<CShaderProgramResource> CResourceManager::getShaderProgramResource( const std::string& vertPath, const std::string& fragPath ) 
    {
        std::shared_ptr<CShaderProgramResource> resource;

        // a hash created from 2 other hashes (by using XOR)
        size_t hash = strHash( vertPath ) ^ strHash( fragPath );

        auto it = m_mapPathHashToShaderResource.find( hash );
        auto end = m_mapPathHashToShaderResource.end();
        if( it != end )
        {
            resource = it->second;
        }
        else
        {
            // let the eventual exception propagate
            resource = loadShaderProgramResourceFromFiles( vertPath, fragPath );
            m_mapPathHashToShaderResource[ hash ] = resource;
        }

        return resource;
    }

    std::shared_ptr<CTexture2DResource> CResourceManager::getTexture2DResource( const std::string& path ) 
    {
        std::shared_ptr<CTexture2DResource> resource;

        size_t hash = strHash( path );

        auto it = m_mapPathHashToTextureResource.find( hash );
        auto end = m_mapPathHashToTextureResource.end();
        if( it != end )
        {
            resource = it->second;
        }
        else
        {
            resource = loadTexture2DResourceFromFile( path );
            m_mapPathHashToTextureResource[ hash ] = resource;
        }
     
        return resource;
    }

    std::shared_ptr<CFontResource> CResourceManager::getFontResource( const std::string& path ) 
    {
        std::shared_ptr<CFontResource> resource;

        size_t hash = strHash( path );

        auto it = m_mapPathHashToFontResource.find( hash );
        auto end = m_mapPathHashToFontResource.end();
        if( it != end )
        {
            resource = it->second;
        }
        else
        {
            resource = loadFontResourceFromFile( path );
            m_mapPathHashToFontResource[ hash ] = resource;
        }

        return resource;
    }

} // namespace chestnut
