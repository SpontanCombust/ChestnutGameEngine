#ifndef __CHESTNUT_ENGINE_RESOURCE_MANAGER_H__
#define __CHESTNUT_ENGINE_RESOURCE_MANAGER_H__

#include "resource.hpp"
#include "texture2d_resource.hpp"
#include "shader_program_resource.hpp"
#include "font_resource.hpp"

#include <string>
#include <unordered_map>

namespace chestnut::engine
{
    class CResourceManager
    {
    private:
        static std::unordered_map< size_t, std::shared_ptr<IResource> > m_mapHashToResource;
        static std::hash< std::string > m_hasher;

    public:
        // Throws an exception if fails to load the resource
        static std::shared_ptr<CShaderProgramResource> loadShaderProgramResource( const std::string& vertShaderPath, const std::string& fragShaderPath );
        // Returns invalid resource if that was not loaded beforehand
        static std::shared_ptr<CShaderProgramResource> getShaderProgramResource( const std::string& vertShaderPath, const std::string& fragShaderPath );
        // Throws an exception if fails to load the resource
        static std::shared_ptr<CShaderProgramResource> loadOrGetShaderProgramResource( const std::string& vertShaderPath, const std::string& fragShaderPath );
        static bool isShaderProgramResourceLoaded( const std::string& vertShaderPath, const std::string& fragShaderPath ); 
        static void freeShaderProgramResource( const std::string& vertShaderPath, const std::string& fragShaderPath );

        // Throws an exception if fails to load the resource
        static std::shared_ptr<CTexture2DResource> loadTexture2DResource( const std::string& texturePath );
        // Returns invalid resource if that was not loaded beforehand
        static std::shared_ptr<CTexture2DResource> getTexture2DResource( const std::string& texturePath );
        // Throws an exception if fails to load the resource
        static std::shared_ptr<CTexture2DResource> loadOrGetTexture2DResource( const std::string& texturePath );
        static bool isTexture2DResourceLoaded( const std::string& texturePath );
        static void freeTexture2DResource( std::string& texturePath );

        // Throws an exception if fails to load the resource
        static std::shared_ptr<CFontResource> loadFontResource( const std::string& fontPath );
        // Returns invalid resource if that was not loaded beforehand
        static std::shared_ptr<CFontResource> getFontResource( const std::string& fontPath );
        // Throws an exception if fails to load the resource
        static std::shared_ptr<CFontResource> loadOrGetFontResource( const std::string& fontPath );
        static bool isFontResourceLoaded( const std::string& fontPath );
        static void freeFontResource( std::string& fontPath );
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_RESOURCE_MANAGER_H__