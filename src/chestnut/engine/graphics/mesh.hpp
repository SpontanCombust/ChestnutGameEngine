#pragma once


#include "chestnut/engine/macros.hpp"
#include "../resources/mesh_resource.hpp"
#include "../resources/mesh_data_resource.hpp"
#include "opengl/vertex_array.hpp"
#include "opengl/shader_program.hpp"

#include <tl/optional.hpp>


namespace chestnut::engine
{
    class CHESTNUT_API CMesh
    {
    private:
        std::shared_ptr<CMeshResource> m_resource;

    public:
        CMesh();
        explicit CMesh(std::shared_ptr<CMeshResource> resource);
        explicit CMesh(std::shared_ptr<CMeshDataResource> resource, const SMaterial& material);

        bool isValid() const;
        const std::shared_ptr<CMeshResource>& getResource() const;

        // If encounters an error will return a value with the error message
        tl::optional<const char *> addBuffersToVAO( CVertexArray& vao, const CShaderProgram& shaderProgram, 
            const char *vertPosAttribName, 
            const char *vertNormalAttribName, 
            const char *vertUVAttribName) const;
    };

} // namespace chestnut::engine

