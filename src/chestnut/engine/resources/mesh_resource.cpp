#include "mesh_resource.hpp"

#include "../misc/exception.hpp"
#include "../debug/log.hpp"
#include "resource_manager.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <filesystem>


namespace chestnut::engine
{    
    CMeshResource::CMeshResource()
    {
        m_numVertices = 0;
        m_numIndices = 0;
        m_vboVertices = nullptr;
        m_vboNormals = nullptr;
        m_vboUVs = nullptr;
        m_ibo = nullptr;
    }



    std::shared_ptr<CMeshResource> CMeshResource::loadFromGeometry(
            unsigned int vertexCount,
            const vec3f *vertices,
            const vec3f *normals,
            const vec2f *uvs,
            unsigned int indexCount,
            const unsigned int *indices,
            const SMaterial& material
    )
    {
        LOG_INFO("Loading mesh from geometry...");

        auto vboVertices = std::make_shared<CBuffer>(
            CBuffer::EType::VERTEX,
            CBuffer::EUsage::STATIC_DRAW,
            CBuffer::ELayout::SINGLE_ARRAY
        );
        vboVertices->update(vertices, vertexCount * sizeof(vec3f));

        auto vboNormals = std::make_shared<CBuffer>(
            CBuffer::EType::VERTEX,
            CBuffer::EUsage::STATIC_DRAW,
            CBuffer::ELayout::SINGLE_ARRAY
        );
        vboNormals->update(normals, vertexCount * sizeof(vec3f));

        auto vboUVs = std::make_shared<CBuffer>(
            CBuffer::EType::VERTEX,
            CBuffer::EUsage::STATIC_DRAW,
            CBuffer::ELayout::SINGLE_ARRAY
        );
        vboUVs->update(uvs, vertexCount * sizeof(vec2f));

        auto ibo = std::make_shared<CBuffer>(
            CBuffer::EType::INDEX,
            CBuffer::EUsage::STATIC_DRAW,
            CBuffer::ELayout::SINGLE_ARRAY
        );
        ibo->update(indices, indexCount * sizeof(unsigned int));


        auto resource = std::make_shared<CMeshResource>();
        resource->m_numVertices = vertexCount;
        resource->m_numIndices = indexCount;
        resource->m_vboVertices = vboVertices;
        resource->m_vboNormals = vboNormals;
        resource->m_vboUVs = vboUVs;
        resource->m_ibo = ibo;
        resource->m_material = material;

        return resource;
    }




    // this is bound to be slow and will require async loading functionality
    void extractGeometryFromMesh(aiMesh *mesh,
                                 std::vector<vec3f>& out_vertices, 
                                 std::vector<vec3f>& out_normals, 
                                 std::vector<vec2f>& out_uvs, 
                                 std::vector<unsigned int>& out_indices)
    {
        out_vertices.resize(mesh->mNumVertices);
        out_normals.resize(mesh->mNumVertices);
        out_uvs.resize(mesh->mNumVertices);

        std::memcpy(&out_vertices[0], (void *)mesh->mVertices, mesh->mNumVertices * sizeof(vec3f));
        std::memcpy(&out_normals[0], (void *)mesh->mNormals, mesh->mNumVertices * sizeof(vec3f));
        
        for (size_t i = 0; i < mesh->mNumVertices; i++)
        {
            out_uvs[i] = vec2f(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }
    
        out_indices.resize(mesh->mNumFaces * 3);
        for (size_t i = 0; i < mesh->mNumFaces; i++)
        {   
            // aiProcess_Triangulate ensurs that all faces are triangles
            out_indices[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
            out_indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
            out_indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
        }
    }

    tl::expected<std::shared_ptr<CTexture2DResource>, const char *> extractTextureFromMaterial(aiMaterial *material, ETextureMapType type, std::filesystem::path directory)
    {
        aiTextureType assimpTexType;
        switch(type)
        {
        case ETextureMapType::DIFFUSE:
            assimpTexType = aiTextureType_DIFFUSE;
            break;
        case ETextureMapType::SPECULAR:
            assimpTexType = aiTextureType_SPECULAR;
            break;
        case ETextureMapType::NORMAL:
            assimpTexType = aiTextureType_NORMALS;
            break;
        default:
            return tl::make_unexpected<const char *>("Invalid texture map type");
        }

        aiString path;
        if(material->GetTexture(assimpTexType, 0, &path) > 0)
        {
            std::filesystem::path texturePath = std::filesystem::absolute(directory/path.C_Str());
         
            return CResourceManager::getOrLoadResource<CTexture2DResource>(texturePath.string().c_str());
        }
        
        return tl::make_unexpected<const char *>("No texture of that type available");
    }
    
    SMaterial extractMaterialFromMesh(aiMesh *mesh, const aiScene *scene, std::filesystem::path directory)
    {
        SMaterial material;

        aiMaterial *assimpMaterial = scene->mMaterials[mesh->mMaterialIndex];
        
        if(auto diffuse = extractTextureFromMaterial(assimpMaterial, ETextureMapType::DIFFUSE, directory)) {
            material.diffuse = *diffuse;
        } else {
            LOG_WARNING("Diffuse couldn't be loaded for the material");
            LOG_WARNING(diffuse.error());
        }

        if(auto specular = extractTextureFromMaterial(assimpMaterial, ETextureMapType::SPECULAR, directory)) {
            material.specular = *specular;
        } else {
            LOG_WARNING("Specular couldn't be loaded for the material");
            LOG_WARNING(specular.error());
        }

        if(auto normal = extractTextureFromMaterial(assimpMaterial, ETextureMapType::NORMAL, directory)) {
            material.normal = *normal;
        } else {
            LOG_WARNING("Normal couldn't be loaded for the material");
            LOG_WARNING(normal.error());
        }

        return material;
    }

    tl::expected<std::shared_ptr<CMeshResource>, const char *> CMeshResource::loadFromFile(const char *meshPath)
    {
        LOG_INFO("Loading mesh from file: " << meshPath << "...");

        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile( 
            meshPath, 
            aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_GenUVCoords | aiProcess_OptimizeMeshes
        );

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            return tl::make_unexpected<const char *>(importer.GetErrorString());
        }

        aiMesh *mesh = scene->mMeshes[0];

        std::vector<vec3f> vertices;
        std::vector<vec3f> normals;
        std::vector<vec2f> uvs;
        std::vector<unsigned int> indices;

        LOG_INFO("Extracting mesh geometry from the file...");
        extractGeometryFromMesh(mesh, vertices, normals, uvs, indices);

        auto directory = std::filesystem::path(meshPath).parent_path();
        LOG_INFO("Extracting mesh material from the file...");
        SMaterial material = extractMaterialFromMesh(mesh, scene, directory);

        return loadFromGeometry(
            vertices.size(),
            vertices.data(),
            normals.data(),
            uvs.data(),
            indices.size(),
            indices.data(),
            material
        );
    }

} // namespace chestnut::engine
