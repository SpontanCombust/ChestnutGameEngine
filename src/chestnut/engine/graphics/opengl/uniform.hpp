#pragma once


#include "chestnut/engine/macros.hpp"
#include "../../resources/shader_program_resource.hpp"

#include <GL/glew.h>

#include <string>


namespace chestnut::engine
{
    template<typename T>
    class CUniform
    {
    private:
        // Added to make autobinding possible.
        // It couldn't be CShaderProgram, because that one already needs CUniform
        // So this is a little hacky way to make it work.
        std::shared_ptr<CShaderProgramResource> m_shaderResource;

        std::string m_name;
        GLint m_location;

    public:
        CUniform();
        CUniform(const std::string& name, GLint location, std::shared_ptr<CShaderProgramResource> m_shaderResource);

        void set(const T& value);
        CUniform& operator=(const T& value);
    };

} // namespace chestnut::engine


#include "uniform.inl"


