#ifndef __CHESTNUT_SHADER_PROGRAM_RESOURCE_H__
#define __CHESTNUT_SHADER_PROGRAM_RESOURCE_H__

#include "../libs.hpp"

#include <memory>
#include <unordered_map>

namespace chestnut
{
    // Returns shader program ID
    // User is responsible for deleting the program
    // Throws exception if fails to load the program
    GLuint loadOpenGLShaderProgramFromFiles( const std::string& vertPath, const std::string& fragPath );

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

        // Requires shader to be bound
        // Returns -1 if doesn't find the location
        GLint getAttributeLocation( std::string attrName );
        // Requires shader to be bound
        // Returns -1 if doesn't find the location
        GLint getUniformLocation( std::string uniformName );

        ~CShaderProgramResource();
    };

    // Throws exception if fails to load the shader program
    std::shared_ptr<CShaderProgramResource> loadShaderProgramResourceFromFiles( const std::string& vertPath, const std::string& fragPath );

} // namespace chestnut

#endif // __CHESTNUT_SHADER_PROGRAM_RESOURCE_H__