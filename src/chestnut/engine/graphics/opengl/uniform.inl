#include "chestnut/engine/maths/vector2.hpp"
#include "chestnut/engine/maths/vector3.hpp"
#include "chestnut/engine/maths/vector4.hpp"
#include "chestnut/engine/maths/matrix3.hpp"
#include "chestnut/engine/maths/matrix4.hpp"

#include <type_traits>

namespace chestnut::engine
{
    template<typename T>
    CUniform<T>::CUniform()
    : m_name(""), m_location(-1)
    {

    }

    template<typename T>
    CUniform<T>::CUniform(const std::string& name, GLint location, std::shared_ptr<CShaderProgramResource> shaderResource)
    : m_shaderResource(shaderResource), m_name(name), m_location(location)
    {
        
    }

    template<typename T>
    void CUniform<T>::set(const T& value)
    {
        glUseProgram(m_shaderResource->m_programID);

        if constexpr(std::is_same_v<T, int>)
        {
            glUniform1i(m_location, value);
        }
        else if constexpr(std::is_same_v<T, vec2i>)
        {
            glUniform2iv(m_location, 1, value.data());
        }
        else if constexpr(std::is_same_v<T, unsigned int>)
        {
            glUniform1ui(m_location, value);
        }
        else if constexpr(std::is_same_v<T, float>)
        {
            glUniform1f(m_location, value);
        }
        else if constexpr(std::is_same_v<T, vec2f>)
        {
            glUniform2fv(m_location, 1, value.data());
        }
        else if constexpr(std::is_same_v<T, vec3f>)
        {
            glUniform3fv(m_location, 1, value.data());
        }
        else if constexpr(std::is_same_v<T, vec4f>)
        {
            glUniform4fv(m_location, 1, value.data());
        }
        else if constexpr(std::is_same_v<T, mat3f>)
        {
            glUniformMatrix3fv(m_location, 1, GL_FALSE, value.data());
        }
        else if constexpr(std::is_same_v<T, mat4f>)
        {
            glUniformMatrix4fv(m_location, 1, GL_FALSE, value.data());
        }
        else
        {
            static_assert(sizeof(T) == 0, "Template type not supported as uniform type!");   
        }
    }

    template<typename T>
    CUniform<T>& CUniform<T>::operator=(const T& value)
    {
        set(value);
        return *this;
    }

} // namespace chestnut::engine
