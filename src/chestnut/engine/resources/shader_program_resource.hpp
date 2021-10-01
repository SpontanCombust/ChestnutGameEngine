#ifndef __CHESTNUT_ENGINE_SHADER_PROGRAM_RESOURCE_H__
#define __CHESTNUT_ENGINE_SHADER_PROGRAM_RESOURCE_H__

#include "resource.hpp"

#include <GL/glew.h>

#include <memory>
#include <unordered_map>

namespace chestnut::engine
{
    // A resource class that provides automatic shader program deallocation on object deletion
    class CShaderProgramResource : public IResource
    {
    public:
        std::string m_vertexShaderPath;
        std::string m_fragmentShaderPath;
        
        GLuint m_programID;

        std::unordered_map< std::string, GLint > m_mapUniformNameToLocation;
        std::unordered_map< std::string, GLint > m_mapAttributeNameToLocation;

    public:
        CShaderProgramResource();

        ~CShaderProgramResource();


        bool isValid() const override;


        // Requires shader to be bound
        // Returns -1 if doesn't find the location
        GLint getAttributeLocation( std::string attrName );
        // Requires shader to be bound
        // Returns -1 if doesn't find the location
        GLint getUniformLocation( std::string uniformName );
    };


    // Throws exception if fails to load the shader program
    std::shared_ptr<CShaderProgramResource> loadShaderProgramResourceFromFiles( const std::string& vertPath, const std::string& fragPath );

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_SHADER_PROGRAM_RESOURCE_H__