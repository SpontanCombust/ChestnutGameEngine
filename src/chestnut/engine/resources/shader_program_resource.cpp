#include "chestnut/engine/resources/shader_program_resource.hpp"

#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/main/window.hpp"
#include "chestnut/engine/misc/utility_functions.hpp"

#include <nlohmann/json.hpp>

#include <cassert>
#include <fstream>
#include <sstream>
#include <tuple>

namespace chestnut::engine
{    
    std::tuple<bool, std::string> checkShaderCompiled(GLuint shader) noexcept
    {
        GLint compiled;

        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
        if( compiled == GL_TRUE )
        {
            return {true, ""};
        }
        else
        {
            GLint logMaxLength;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logMaxLength );

            GLsizei logLength;
            std::string logBuffer; logBuffer.reserve(logMaxLength);
            glGetShaderInfoLog(shader, logMaxLength, &logLength, logBuffer.data());

            return {false, logBuffer};
        }
    }

    std::tuple<bool, std::string> checkProgramLinked(GLuint program) noexcept
    {
        GLint linked;

        glGetProgramiv( program, GL_LINK_STATUS, &linked );
        if( linked == GL_TRUE )
        {
            return {true, ""};
        }
        else
        {
            GLint logMaxLength;
            glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logMaxLength );

            GLsizei logLength;
            std::string logBuffer; logBuffer.reserve(logMaxLength);
            glGetProgramInfoLog(program, logMaxLength, &logLength, logBuffer.data());

            return {false, logBuffer};
        }
    }

    tl::expected<GLuint, std::string> 
    CShaderProgramResource::loadShaderFromFile(std::filesystem::path path, GLenum shaderType ) noexcept
    {
        if(!std::filesystem::exists(path))
        {
            LOG_ERROR("Shader source file does not exist: " << path);
            return tl::make_unexpected("Shader source file does not exist");
        }

        auto [ext, supported] = isExtensionSupported(path, SUPPORTED_FILE_EXTENSIONS_SHADER_CODE);
        if(!supported)
        {
            return tl::make_unexpected("Unsupported file type: " + ext);
        }

        std::ifstream f = std::ifstream( path, std::ios::in );
        if( f.good() )
        {
            std::stringstream shaderBuffer;
            std::string shaderSource;

            shaderBuffer << f.rdbuf();
            shaderSource = shaderBuffer.str();

            const char *shaderSourceRawStr = shaderSource.c_str();

            f.close();


            GLuint shader = glCreateShader( shaderType );
            glShaderSource( shader, 1, &shaderSourceRawStr, NULL );
            glCompileShader( shader );

            auto [compiled, error] = checkShaderCompiled(shader);
            if(!compiled)
            {
                LOG_ERROR( "Failed to compile the shader from file: " << path );
                LOG_ERROR( "Error: " << error );
                glDeleteShader( shader );
                return tl::make_unexpected("Shader compilation error: " + error);
            }
            else
            {
                return shader;
            }
        }
        else
        {
            LOG_ERROR( "Failed to open shader source file: " << path );
            return tl::make_unexpected("Shader file open error");
        }
    }

    tl::expected<GLuint, std::string> createAndLinkShaderProgram(GLuint vertexShader, GLuint fragmentShader) noexcept
    {
        GLuint program = glCreateProgram();
        glAttachShader( program, vertexShader );
        glAttachShader( program, fragmentShader );
        glLinkProgram( program );

        glDetachShader( program, fragmentShader );
        glDetachShader( program, vertexShader );
        glDeleteShader( fragmentShader );
        glDeleteShader( vertexShader );

        auto [linked, error] = checkProgramLinked(program);
        if(!linked)
        {
            LOG_ERROR( "Failed to link the shader program" );
            LOG_ERROR( "Error: " << error );
            glDeleteProgram( program );
            return tl::make_unexpected("Shader program linking error: " + error);
        }
        else
        {
            return program;
        }
    }

    tl::expected<GLuint, std::string> 
    CShaderProgramResource::loadOpenGLShaderProgramFromFiles(std::filesystem::path vertPath, std::filesystem::path fragPath ) noexcept
    {
        GLuint vertShader;
        GLuint fragShader;
        
        if( auto shader = loadShaderFromFile( vertPath, GL_VERTEX_SHADER ) ) {
            vertShader = *shader;
        } else {
            return tl::make_unexpected(shader.error());
        }
        
        if( auto shader = loadShaderFromFile( fragPath, GL_FRAGMENT_SHADER ) ) {
            fragShader = *shader;
        } else {
            return tl::make_unexpected(shader.error());
        }

        return createAndLinkShaderProgram( vertShader, fragShader );
    }

    




    CShaderProgramResource::CShaderProgramResource(tl::optional<std::filesystem::path> location) noexcept
    : IResource(location)
    {
        m_programID = 0;
        m_vertexShaderPath = "";
        m_fragmentShaderPath = "";
    }

    CShaderProgramResource::~CShaderProgramResource() noexcept
    {
        glDeleteProgram( m_programID );
    }





    tl::expected<std::shared_ptr<CShaderProgramResource>, std::string> 
    CShaderProgramResource::loadFromSourceFiles(std::filesystem::path vertPath, std::filesystem::path fragPath) noexcept
    {
        assert(CWindow::isAnyActive() && "OpenGL context is needed to use this type of resource."
                                        " Make sure to instantiate CWindow before trying to load it.");

        LOG_INFO("Loading shader program from files: " << vertPath << " and " << fragPath << "..." );

        auto program = loadOpenGLShaderProgramFromFiles(vertPath, fragPath);

        if( program ) 
        {
            CShaderProgramResource *resource = new CShaderProgramResource(tl::nullopt);
            resource->m_programID = *program;
            resource->m_vertexShaderPath = std::filesystem::absolute(vertPath);
            resource->m_fragmentShaderPath = std::filesystem::absolute(fragPath);

            return std::shared_ptr<CShaderProgramResource>( resource );
        } 
        
        return tl::make_unexpected(program.error());
    }

    tl::expected<std::shared_ptr<CShaderProgramResource>, std::string> 
    CShaderProgramResource::loadFromDefinition(std::filesystem::path location) noexcept
    {
        assert(CWindow::isAnyActive() && "OpenGL context is needed to use this type of resource."
                                        " Make sure to instantiate CWindow before trying to load it.");
                                        
        LOG_INFO("Loading shader program from definition: " << location << "..." );

        if(!std::filesystem::exists(location))
        {
            return tl::make_unexpected("File does not exist: " + location.string());
        }

        auto [ext, supported] = isExtensionSupported(location, SUPPORTED_FILE_EXTENSIONS_DEFINITIONS);
        if(!supported)
        {
            return tl::make_unexpected("Unsupported file type: " + ext);
        }


        std::ifstream f(location);

        if(!f)
        {
            return tl::make_unexpected("Definition file could not be opened");
        }

        std::filesystem::path vs, fs;
        try
        {
            auto j = nlohmann::json::parse(f); 
            
            j.at("vertexShaderSourceFile").get_to(vs);
            j.at("fragmentShaderSourceFile").get_to(fs);
        }
        catch(const std::exception& e)
        {
            return tl::make_unexpected("Error when parsing the file: " + std::string(e.what()));
        }


        if(!vs.is_absolute())
        {
            vs = assetPathToAbsolute(vs);
        }
        if(!fs.is_absolute())
        {
            fs = assetPathToAbsolute(fs);
        }

        if(auto program = loadOpenGLShaderProgramFromFiles(vs, fs))
        {
            CShaderProgramResource *resource = new CShaderProgramResource(location);
            resource->m_programID = *program;
            resource->m_vertexShaderPath = vs;
            resource->m_fragmentShaderPath = fs;

            return std::shared_ptr<CShaderProgramResource>( resource );
        }
        else
        {
            return tl::make_unexpected(program.error());
        }
    }

    tl::expected<std::shared_ptr<CShaderProgramResource>, std::string> 
    CShaderProgramResource::load(std::filesystem::path location) noexcept
    {
        return loadFromDefinition(location);
    }

} // namespace chestnut::engine
