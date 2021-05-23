#include "resource_manager.hpp"

#include "engine/debug/debug.hpp"

namespace chestnut
{
    size_t CResourceManager::strHash(const std::string& str) 
    {
        return std::hash< std::string >()( str );
    }

    CShaderProgram CResourceManager::loadShaderProgram( const std::string& vertPath, const std::string& fragPath ) 
    {
        CShaderProgram prog;

        try
        {
            std::shared_ptr<CShaderProgramResource> resource = loadShaderProgramResourceFromFiles( vertPath, fragPath );
            prog = CShaderProgram( resource );

            // a hash created from 2 other hashes (by using XOR)
            size_t hash = strHash( vertPath ) ^ strHash( fragPath );        
            m_mapPathHashToShaderResource.insert( std::make_pair( hash, resource ) );
        }
        catch(const std::exception& e)
        {
            LOG_CHANNEL( "RESOURCE_MANAGER", e.what() );
        }
        
        return prog;
    }

    CTexture2D CResourceManager::loadTexture( const std::string& path ) 
    {
        CTexture2D tex;

        try
        {
            std::shared_ptr<CTexture2DResource> resource = loadTextureResourceFromFile( path );
            tex = CTexture2D( resource );

            size_t hash = strHash( path );
            m_mapPathHashToTextureResource.insert( std::make_pair( hash, resource ) );
        }
        catch( const std::exception& e )
        {
            LOG_CHANNEL( "RESOURCE_MANAGER", e.what() );
        }

        return tex;
    }

} // namespace chestnut
