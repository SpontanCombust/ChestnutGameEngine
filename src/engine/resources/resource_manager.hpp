#ifndef __CHESTNUT_RESOURCE_MANAGER_H__
#define __CHESTNUT_RESOURCE_MANAGER_H__

#include "texture2d_resource.hpp"
#include "shader_program_resource.hpp"
#include "engine/graphics/shader_program.hpp"
#include "engine/graphics/texture2d.hpp"

#include <string>
#include <unordered_map>

namespace chestnut
{
    class CResourceManager
    {
    private:
        std::unordered_map< size_t, std::shared_ptr<CShaderProgramResource> > m_mapPathHashToShaderResource;
        std::unordered_map< size_t, std::shared_ptr<CTexture2DResource> > m_mapPathHashToTextureResource;

    public:
        CShaderProgram loadShaderProgram( const std::string& vertPath, const std::string& fragPath );
        CTexture2D loadTexture( const std::string& path );

    private:
        size_t strHash( const std::string& str );
    };

} // namespace chestnut

#endif // __CHESTNUT_RESOURCE_MANAGER_H__