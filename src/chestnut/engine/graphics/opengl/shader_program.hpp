#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/maths/vector2.hpp"
#include "chestnut/engine/maths/vector3.hpp"
#include "chestnut/engine/maths/vector4.hpp"
#include "chestnut/engine/maths/matrix3.hpp"
#include "chestnut/engine/maths/matrix4.hpp"
#include "chestnut/engine/resources/shader_program_resource.hpp"
#include "chestnut/engine/graphics/opengl/vertex_attribute.hpp"
#include "chestnut/engine/graphics/opengl/uniform.hpp"

#include <tl/optional.hpp>

#include <string>
#include <unordered_map>

namespace chestnut::engine
{
    class CHESTNUT_API CShaderProgram
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

        template<typename T>
        tl::optional<CVertexAttribute> getAttribute(const char *name, bool isInstanced = false) const noexcept;

        template<typename T>
        tl::optional<CUniform<T>> getUniform(const char *name) const noexcept;
    };
    
} // namespace chestnut::engine


#include "shader_program.inl"


