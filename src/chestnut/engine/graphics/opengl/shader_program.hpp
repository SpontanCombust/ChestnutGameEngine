#pragma once


#include "chestnut/engine/macros.hpp"
#include "../../maths/vector2.hpp"
#include "../../maths/vector3.hpp"
#include "../../maths/vector4.hpp"
#include "../../maths/matrix3.hpp"
#include "../../maths/matrix4.hpp"
#include "../../resources/shader_program_resource.hpp"
#include "vertex_attribute.hpp"
#include "uniform.hpp"

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


