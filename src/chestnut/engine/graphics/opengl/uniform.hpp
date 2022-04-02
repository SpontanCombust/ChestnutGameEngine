#ifndef __CHESTNUT_ENGINE_UNIFORM_H__
#define __CHESTNUT_ENGINE_UNIFORM_H__

#include "../../maths/vector2.hpp"
#include "../../maths/vector3.hpp"
#include "../../maths/vector4.hpp"
#include "../../maths/matrix3.hpp"
#include "../../maths/matrix4.hpp"

#include <GL/glew.h>

#include <string>


namespace chestnut::engine
{
    namespace internal
    {
        class CUniform_Base
        {
        protected:
            std::string m_name;
            GLint m_location;

        public:
            CUniform_Base(const std::string& name, GLint location);
        };

    } // namespace internal
    
    template<typename T>
    class CUniform : public internal::CUniform_Base
    {
    public:
        CUniform(const std::string& name, GLint location);

        void set(T&& value);
    };



    //TODO I should add more vector and matrix specializations

    template<>
    class CUniform<int> : public internal::CUniform_Base
    {
    public:
        CUniform(const std::string& name, GLint location);

        void set(int value);
    };

    template<>
    class CUniform<vec2i> : public internal::CUniform_Base
    {
    public:
        CUniform(const std::string& name, GLint location);

        void set(const vec2i& value);
    };

    template<>
    class CUniform<unsigned int> : public internal::CUniform_Base
    {
    public:
        CUniform(const std::string& name, GLint location);

        void set(unsigned int value);
    };

    template<>
    class CUniform<float> : public internal::CUniform_Base
    {
    public:
        CUniform(const std::string& name, GLint location);

        void set(float value);
    };

    template<>
    class CUniform<vec2f> : public internal::CUniform_Base
    {
    public:
        CUniform(const std::string& name, GLint location);

        void set(const vec2f& value);
    };

    template<>
    class CUniform<vec3f> : public internal::CUniform_Base
    {
    public:
        CUniform(const std::string& name, GLint location);

        void set(const vec3f& value);
    };

    template<>
    class CUniform<vec4f> : public internal::CUniform_Base
    {
    public:
        CUniform(const std::string& name, GLint location);

        void set(const vec4f& value);
    };

    template<>
    class CUniform<mat3f> : public internal::CUniform_Base
    {
    public:
        CUniform(const std::string& name, GLint location);

        void set(const mat3f& value);
    };

    template<>
    class CUniform<mat4f> : public internal::CUniform_Base
    {
    public:
        CUniform(const std::string& name, GLint location);

        void set(const mat4f& value);
    };

} // namespace chestnut::engine


#include "uniform.inl"


#endif // __CHESTNUT_ENGINE_UNIFORM_H__