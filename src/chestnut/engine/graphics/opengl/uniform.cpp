#include "uniform.hpp"

namespace chestnut::engine
{
    namespace internal
    {
        CUniform_Base::CUniform_Base(const std::string& name, GLint location)
        : m_name(name), m_location(location)
        {

        }
        
    } // namespace internal



    
    CUniform<int>::CUniform(const std::string& name, GLint location)
    : internal::CUniform_Base(name, location)
    {

    }

    void CUniform<int>::set(int value)
    {
        glUniform1i(m_location, value);
    }


    CUniform<vec2i>::CUniform(const std::string& name, GLint location)
    : internal::CUniform_Base(name, location)
    {

    }

    void CUniform<vec2i>::set(const vec2i& value)
    {
        glUniform2iv(m_location, 1, value.data());
    }


    CUniform<unsigned int>::CUniform(const std::string& name, GLint location)
    : internal::CUniform_Base(name, location)
    {

    }

    void CUniform<unsigned int>::set(unsigned int value)
    {
        glUniform1ui(m_location, value);
    }


    CUniform<float>::CUniform(const std::string& name, GLint location)
    : internal::CUniform_Base(name, location)
    {

    }

    void CUniform<float>::set(float value)
    {
        glUniform1f(m_location, value);
    }


    CUniform<vec2f>::CUniform(const std::string& name, GLint location)
    : internal::CUniform_Base(name, location)
    {

    }

    void CUniform<vec2f>::set(const vec2f& value)
    {
        glUniform2fv(m_location, 1, value.data());
    }


    CUniform<vec3f>::CUniform(const std::string& name, GLint location)
    : internal::CUniform_Base(name, location)
    {

    }

    void CUniform<vec3f>::set(const vec3f& value)
    {
        glUniform3fv(m_location, 1, value.data());
    }


    CUniform<vec4f>::CUniform(const std::string& name, GLint location)
    : internal::CUniform_Base(name, location)
    {

    }

    void CUniform<vec4f>::set(const vec4f& value)
    {
        glUniform4fv(m_location, 1, value.data());
    }


    CUniform<mat3f>::CUniform(const std::string& name, GLint location)
    : internal::CUniform_Base(name, location)
    {

    }

    void CUniform<mat3f>::set(const mat3f& value)
    {
        glUniformMatrix3fv(m_location, 1, GL_FALSE, value.data());
    }


    CUniform<mat4f>::CUniform(const std::string& name, GLint location)
    : internal::CUniform_Base(name, location)
    {

    }

    void CUniform<mat4f>::set(const mat4f& value)
    {
        glUniformMatrix4fv(m_location, 1, GL_FALSE, value.data());
    }
    
} // namespace chestnut::engine
