#ifndef __CHESTNUT_ENGINE_UNIFORM_H__
#define __CHESTNUT_ENGINE_UNIFORM_H__

#include <GL/glew.h>

#include <string>


namespace chestnut::engine
{
    template<typename T>
    class CUniform
    {
    private:
        std::string m_name;
        GLint m_location;

    public:
        CUniform(const std::string& name, GLint location);

        void set(const T& value);
    };

} // namespace chestnut::engine


#include "uniform.inl"


#endif // __CHESTNUT_ENGINE_UNIFORM_H__