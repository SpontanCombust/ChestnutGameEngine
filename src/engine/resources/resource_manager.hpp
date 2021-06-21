#ifndef __CHESTNUT_RESOURCE_MANAGER_H__
#define __CHESTNUT_RESOURCE_MANAGER_H__

#include "texture2d_resource.hpp"
#include "shader_program_resource.hpp"
#include "font_resource.hpp"

#include <string>
#include <unordered_map>

namespace chestnut
{
    class CResourceManager
    {
    private:
        std::unordered_map< size_t, std::shared_ptr<CShaderProgramResource> > m_mapPathHashToShaderResource;
        std::unordered_map< size_t, std::shared_ptr<CTexture2DResource> > m_mapPathHashToTextureResource;
        std::unordered_map< size_t, std::shared_ptr<CFontResource> > m_mapPathHashToFontResource;

    public:
        // Throws an exception if fails to load the resource
        std::shared_ptr<CShaderProgramResource> getShaderProgramResource( const std::string& vertPath, const std::string& fragPath );
        // Throws an exception if fails to load the resource
        std::shared_ptr<CTexture2DResource> getTexture2DResource( const std::string& path );
        // Throws an exception if fails to load the resource
        std::shared_ptr<CFontResource> getFontResource( const std::string& path );

    private:
        size_t strHash( const std::string& str );
    };

} // namespace chestnut

#endif // __CHESTNUT_RESOURCE_MANAGER_H__