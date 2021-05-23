#ifndef __CHESTNUT_SHADER_PROGRAM_RESOURCE_H__
#define __CHESTNUT_SHADER_PROGRAM_RESOURCE_H__

#include "engine/libs.hpp"

#include <memory>
#include <unordered_map>

namespace chestnut
{
    // A resource class that provides automatic shader program deallocation on object deletion
    class CShaderProgramResource
    {
    public:
        GLuint programID;
        std::unordered_map< std::string, GLint > mapUniformNameToLocation;
        std::unordered_map< std::string, GLint > mapAttributeNameToLocation;

        CShaderProgramResource();
        CShaderProgramResource( GLuint programID );

        bool isValid() const;

        ~CShaderProgramResource();
    };

    // Throws exception if fails to load the shader
    std::shared_ptr<CShaderProgramResource> loadShaderProgramResourceFromFiles( const std::string& vertPath, const std::string& fragPath );

} // namespace chestnut

#endif // __CHESTNUT_SHADER_PROGRAM_RESOURCE_H__