#include <type_traits>

namespace chestnut::engine
{    
    template<typename T>
    tl::optional<CVertexAttribute> CShaderProgram::getAttribute(const char *name, bool isInstanced) const noexcept
    {
        if(!m_shaderResource) 
        {
            return tl::nullopt;
        }

        GLint location = glGetAttribLocation(m_shaderResource->m_programID, name);
        if(location == -1)
        {
            return tl::nullopt;
        }

        return CVertexAttribute::create<T>(name, location, isInstanced);
    }

    template<typename T>
    tl::optional<CUniform<T>> CShaderProgram::getUniform(const char *name) const noexcept
    {
        if(!m_shaderResource) 
        {
            return tl::nullopt;
        }

        GLint location = glGetUniformLocation(m_shaderResource->m_programID, name);
        if(location == -1)
        {
            return tl::nullopt;
        }

        return CUniform<T>(name, location, m_shaderResource);
    }

} // namespace chestnut::engine
