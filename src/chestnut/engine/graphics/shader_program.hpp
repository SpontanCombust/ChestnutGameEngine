#ifndef __CHESTNUT_ENGINE_SHADER_PROGRAM_H__
#define __CHESTNUT_ENGINE_SHADER_PROGRAM_H__

#include "../maths/vector2.hpp"
#include "../maths/vector3.hpp"
#include "../maths/vector4.hpp"
#include "../maths/matrix3.hpp"
#include "../maths/matrix4.hpp"
#include "../resources/shader_program_resource.hpp"

#include <string>
#include <unordered_map>

namespace chestnut
{
    class CShaderProgram
    {
    private:
        std::shared_ptr<CShaderProgramResource> m_shaderResource;

    public:
        CShaderProgram() = default;
        explicit CShaderProgram( std::shared_ptr<CShaderProgramResource> resource );

        const std::shared_ptr<CShaderProgramResource>& getResource() const;

        GLuint getID() const;
        bool isValid() const;
        
        void bind();
        void unbind();

        // Requires shader to be bound
        // Returns -1 if doesn't find the location
        GLint getAttributeLocation( std::string attrName );
        // Requires shader to be bound
        // Returns -1 if doesn't find the location
        GLint getUniformLocation( std::string uniformName );

        bool setInt( const std::string& unifName, GLint val );
        bool setVector2f( const std::string& unifName, const vec2f& val );
        bool setVector3f( const std::string& unifName, const vec3f& val );
        bool setVector4f( const std::string& unifName, const vec4f& val );
        bool setMatrix3f( const std::string& unifName, const mat3f& val );
        bool setMatrix4f( const std::string& unifName, const mat4f& val );

        void setInt( GLint loc, int val );
        void setVector2f( GLint loc, const vec2f& val );
        void setVector3f( GLint loc, const vec3f& val );
        void setVector4f( GLint loc, const vec4f& val );
        void setMatrix3f( GLint loc, const mat3f& val );
        void setMatrix4f( GLint loc, const mat4f& val );
    };
    
} // namespace chestnut


#endif // __CHESTNUT_ENGINE_SHADER_PROGRAM_H__