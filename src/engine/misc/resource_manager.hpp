#ifndef __CHESTNUT_RESOURCE_MANAGER_H__
#define __CHESTNUT_RESOURCE_MANAGER_H__

#include "engine/graphics/shader_program.hpp"
#include "engine/graphics/texture2d.hpp"

#include <string>
#include <unordered_map>

namespace chestnut
{
    CShaderProgram loadShaderProgramFromFiles( const std::string& vertPath, const std::string& fragPath );

    CTexture2D loadTextureFromFile( const std::string& path );

    CTexture2D loadTextureFromPixels( void *pixels, int width, int height, unsigned int pixelFormat );


    class CResourceManager
    {
    private:
        std::unordered_map< size_t, CShaderProgram > m_mapPathHashToShader;
        std::unordered_map< size_t, CTexture2D > m_mapPathHashToTexture;

    public:
        ~CResourceManager();

        // If doesn't load successfully returns shader program object with program ID equal 0
        CShaderProgram loadShaderProgram( const std::string& vertPath, const std::string& fragPath );
        CTexture2D loadTexture( const std::string& path );

    private:
        size_t strHash( const std::string& str );
    };

} // namespace chestnut

#endif // __CHESTNUT_RESOURCE_MANAGER_H__