#include "chestnut/engine_extensions/graphics3d/graphics/algorithms/heightmap.hpp"

#include "chestnut/engine/resources/image_data_resource.hpp"

namespace chestnut::engine
{
    tl::expected<std::shared_ptr<SHeightmap>, const char *> heightmapFromFile(const char *path, float valueScale)
    {
        auto imageDataExpected = CImageDataResource::loadFromFile(path, false);
        if(imageDataExpected)
        {
            auto imageData = *imageDataExpected;

            SHeightmap *heightmap = new SHeightmap{};
            heightmap->size.x = imageData->m_width;
            heightmap->size.y = imageData->m_height;

            const int numValues = imageData->m_width * imageData->m_height;
            heightmap->values = new float[numValues];

            for (int i = 0; i < numValues; i++)
            {
                heightmap->values[i] = float(imageData->m_data[i * imageData->m_numChannels]) / 255.0f * valueScale;
            }
            
            return std::shared_ptr<SHeightmap>(heightmap, [](SHeightmap *heightmap) {
                delete[] heightmap->values;
                delete heightmap;
            });
        }
        else
        {
            return tl::make_unexpected(imageDataExpected.error());
        }
    }



    inline vec3f heightmapVertexNormal(const std::vector<vec3f>& vertices, int x, int y, int w, int h)
    {
        vec3f normal(0.f);

        vec3f vThis = vertices[y * w + x];
        if(x < w - 1 && y < h - 1) {
            normal += vecNormalized(vecCrossProduct(
                vertices[(y + 1) * w + x] - vThis,
                vertices[y * w + (x + 1)] - vThis
            ));
        }
        if(x < w - 1 && y > 0) {
            normal += vecNormalized(vecCrossProduct(
                vertices[y * w + (x + 1)] - vThis,
                vertices[(y - 1) * w + x] - vThis
            ));
        }
        if(x > 0 && y > 0) {
            normal += vecNormalized(vecCrossProduct(
                vertices[(y - 1) * w + x] - vThis,
                vertices[y * w + (x - 1)] - vThis
            ));
        }
        if(x > 0 && y < h - 1) {
            normal += vecNormalized(vecCrossProduct(
                vertices[y * w + (x - 1)] - vThis,
                vertices[(y + 1) * w + x] - vThis
            ));
        }

        return vecNormalized(normal);
    }

    tl::expected<std::shared_ptr<CMeshDataResource>, const char *> meshDataFromHeightmap(const SHeightmap &heightmap, vec2f dstSize, float valueScale)
    {
        if(!heightmap.values) {
            return tl::make_unexpected("heightmap values has to not be null");
        } else if(heightmap.size.x == 0 || heightmap.size.y == 0) {
            return tl::make_unexpected("heightmap width and height must not be zero");
        }

        const size_t numVertices = heightmap.size.x * heightmap.size.y;
        std::vector<vec3f> vertices(numVertices);
        std::vector<vec3f> normals(numVertices);
        std::vector<vec2f> uvs(numVertices);

        for (int y = 0; y < heightmap.size.y; y++)
        {
            for (int x = 0; x < heightmap.size.x; x++)
            {
                const size_t i = y * heightmap.size.x + x;
                vertices[i] = vec3f(
                    static_cast<float>(x) / static_cast<float>(heightmap.size.x) * dstSize.x,
                    heightmap.values[i] * valueScale,
                    static_cast<float>(y) / static_cast<float>(heightmap.size.y) * dstSize.y
                );
                uvs[i] = vec2f(
                    static_cast<float>(x) / static_cast<float>(heightmap.size.x),
                    (1.0f - static_cast<float>(y)) / static_cast<float>(heightmap.size.y)
                );
            }
        }
        for (int y = 0; y < heightmap.size.y; y++)
        {
            for (int x = 0; x < heightmap.size.x; x++)
            {
                const size_t i = y * heightmap.size.x + x;
                normals[i] = heightmapVertexNormal(vertices, x, y, heightmap.size.x, heightmap.size.y);
            }
        }


        std::vector<unsigned int> indices;
        indices.reserve((heightmap.size.x - 1) * (heightmap.size.y - 1) * 6);
        
        for (int y = 0; y < heightmap.size.y - 1; y++)
        {
            for (int x = 0; x < heightmap.size.x - 1; x++)
            {
                indices.push_back(y * heightmap.size.x + x);
                indices.push_back((y + 1) * heightmap.size.x + x);
                indices.push_back((y + 1) * heightmap.size.x + (x + 1));
                indices.push_back(y * heightmap.size.x + x);
                indices.push_back((y + 1) * heightmap.size.x + (x + 1));
                indices.push_back(y * heightmap.size.x + (x + 1));
            }
        }


        return CMeshDataResource::loadFromGeometry(
            vertices.size(),
            vertices.data(),
            normals.data(),
            uvs.data(),
            indices.size(),
            indices.data()
        );
    }

} // namespace chestnut::engine
