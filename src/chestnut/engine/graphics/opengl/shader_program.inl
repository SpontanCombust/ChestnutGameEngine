#include <type_traits>

namespace chestnut::engine
{    
    template<typename T, GLuint size>
    tl::optional<CVertexAttribute> CShaderProgram::getAttribute(const char *name, GLuint divisor)
    {
        if(!m_shaderResource) 
        {
            return tl::nullopt;
        }

        if(tl::optional<CVertexAttribute::EType> attribType = CVertexAttribute::deduceTypeEnum<T>())
        {
            GLuint location = m_shaderResource->getAttributeLocation(name);
            if(location == -1)
            {
                return tl::nullopt;
            }

            return CVertexAttribute(name, location, attribType.value(), size, divisor);
        }

        return tl::nullopt;
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
