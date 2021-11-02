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
        // vertShaderPath - path to file with vertex shader
        // fragShaderPath - path to file with fragment shader
        // Throws an exception if fails to load the resource
        static std::shared_ptr<CShaderProgramResource> loadShaderProgramResource( const char *vertShaderPath, const char *fragShaderPath );
        // vertShaderPath - path to file with vertex shader
        // fragShaderPath - path to file with fragment shader
        // Returns invalid resource if that was not loaded beforehand
        static std::shared_ptr<CShaderProgramResource> getShaderProgramResource( const char *vertShaderPath, const char *fragShaderPath );
        // vertShaderPath - path to file with vertex shader
        // fragShaderPath - path to file with fragment shader
        // Throws an exception if fails to load the resource
        static std::shared_ptr<CShaderProgramResource> loadOrGetShaderProgramResource( const char *vertShaderPath, const char *fragShaderPath );
        // vertShaderPath - path to file with vertex shader
        // fragShaderPath - path to file with fragment shader
        static bool isShaderProgramResourceLoaded( const char *vertShaderPath, const char *fragShaderPath ); 
        // vertShaderPath - path to file with vertex shader
        // fragShaderPath - path to file with fragment shader
        static void freeShaderProgramResource( const char *vertShaderPath, const char *fragShaderPath );

        // texturePath - path to either JPG, PNG or TIFF image
        // Throws an exception if fails to load the resource
        static std::shared_ptr<CTexture2DResource> loadTexture2DResource( const char *texturePath );
        // texturePath - path to either JPG, PNG or TIFF image
        // Returns invalid resource if that was not loaded beforehand
        static std::shared_ptr<CTexture2DResource> getTexture2DResource( const char *texturePath );
        // texturePath - path to either JPG, PNG or TIFF image
        // Throws an exception if fails to load the resource
        static std::shared_ptr<CTexture2DResource> loadOrGetTexture2DResource( const char *texturePath );
        // texturePath - path to either JPG, PNG or TIFF image
        static bool isTexture2DResourceLoaded( const char *texturePath );
        // texturePath - path to either JPG, PNG or TIFF image
        static void freeTexture2DResource( const char *texturePath );

        // fontPath - path to .ttf file
        // Throws an exception if fails to load the resource
        static std::shared_ptr<CFontResource> loadFontResource( const char *fontPath );
        // fontPath - path to .ttf file
        // Returns invalid resource if that was not loaded beforehand
        static std::shared_ptr<CFontResource> getFontResource( const char *fontPath );
        // fontPath - path to .ttf file
        // Throws an exception if fails to load the resource
        static std::shared_ptr<CFontResource> loadOrGetFontResource( const char *fontPath );
        // fontPath - path to .ttf file
        static bool isFontResourceLoaded( const char *fontPath );
        // fontPath - path to .ttf file
        static void freeFontResource( const char *fontPath );

        static void freeUnusedResources();
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_RESOURCE_MANAGER_H__