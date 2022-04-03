#include <type_traits>

namespace chestnut::engine
{    
    template<typename T>
    tl::optional<CVertexAttribute> CShaderProgram::getAttribute(const char *name, bool isInstanced)
    {
        if(!m_shaderResource) 
        {
            return tl::nullopt;
        }

        GLuint location = m_shaderResource->getAttributeLocation(name);
        if(location == -1)
        {
            return tl::nullopt;
        }

        return CVertexAttribute::create<T>(name, location, isInstanced);
    }

    template<typename T>
    tl::optional<CUniform<T>> CShaderProgram::getUniform(const char *name)
    {
        if(!m_shaderResource) 
        {
            return tl::nullopt;
        }

        GLint location = m_shaderResource->getUniformLocation(name);
        if(location == -1)
        {
            return tl::nullopt;
        }

        return CUniform<T>(name, location);
    }

} // namespace chestnut::engine
