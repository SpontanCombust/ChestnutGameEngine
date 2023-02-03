#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/resource.hpp"

#include <glad/glad.h>

#include <string>
#include <unordered_map>


namespace chestnut::engine
{
    // A resource class that provides automatic shader program deallocation on object deletion
    class CHESTNUT_API CShaderProgramResource : public IResource
    {
    public:
        inline static const std::vector<std::string> SUPPORTED_FILE_EXTENSIONS_SHADER_CODE {
            "glsl", "vert", "frag", "vs", "fs"
        };
        inline static const std::vector<std::string> SUPPORTED_FILE_EXTENSIONS_DEFINITIONS = {
            "shader"
        };

        std::filesystem::path m_vertexShaderPath;
        std::filesystem::path m_fragmentShaderPath;
        
        GLuint m_programID;

    public:
        CShaderProgramResource(tl::optional<std::filesystem::path> location) noexcept;
        ~CShaderProgramResource() noexcept;

        // vertPath - path to file with vertex shader
        // fragPath - path to file with fragment shader
        static tl::expected<std::shared_ptr<CShaderProgramResource>, std::string> 
        loadFromSourceFiles(std::filesystem::path vertPath, std::filesystem::path fragPath ) noexcept;

        static tl::expected<std::shared_ptr<CShaderProgramResource>, std::string> 
        loadFromDefinition(std::filesystem::path location) noexcept;

        // Calls loadFromDefinition
        static tl::expected<std::shared_ptr<CShaderProgramResource>, std::string> 
        load(std::filesystem:: path location) noexcept;


    private:
        static tl::expected<GLuint, std::string> 
        loadShaderFromFile(std::filesystem::path path, GLenum shaderType ) noexcept;
        
        static tl::expected<GLuint, std::string> 
        loadOpenGLShaderProgramFromFiles(std::filesystem::path vertPath, std::filesystem::path fragPath ) noexcept;
    };



} // namespace chestnut::engine

