#ifndef __CHESTNUT_ENGINE_SHADER_PROGRAM_RESOURCE_H__
#define __CHESTNUT_ENGINE_SHADER_PROGRAM_RESOURCE_H__

#include "resource.hpp"

#include <GL/glew.h>

#include <string>
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

    public:
        CShaderProgramResource() noexcept;
        ~CShaderProgramResource() noexcept;

        // vertPath - path to file with vertex shader
        // fragPath - path to file with fragment shader
        static tl::expected<std::shared_ptr<CShaderProgramResource>, const char *> loadFromFiles( const char *vertPath, const char *fragPath ) noexcept;
    };



} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_SHADER_PROGRAM_RESOURCE_H__