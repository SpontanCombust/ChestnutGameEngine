//TODO at least allowing to not group render calls by texture ID - maybe use 3D texture?

#ifndef __CHESTNUT_ENGINE_SPRITE_RENDERER_H__
#define __CHESTNUT_ENGINE_SPRITE_RENDERER_H__

#include "renderer.hpp"
#include "../opengl/buffer.hpp"
#include "../opengl/uniform.hpp"
#include "../opengl/vertex_array.hpp"
#include "../../maths/vector2.hpp"
#include "../../maths/vector3.hpp"
#include "../../maths/vector4.hpp"
#include "../sprite.hpp"

#include <memory>
#include <vector>
#include <unordered_map>

namespace chestnut::engine
{
    /**
     * @brief A renderer class used to render textures onto the screen
     * 
     * @details
     * Renderer receives data by using submitSprite() method, which takes:
     * - CSprite object (which texture to use and with which properties), 
     * - translation vector (where sprite should be moved),
     * - origin vector (which point relative to texture body should be used as its "anchor" for transformations,
     *   values are normalized, typically range between 0 and 1, point (0,0) being upper left corner of the texture and (1,1) being lower right corner
     * - scale vector (how big the sprite should be relative to its original dimensions) 
     * - rotation in radians (this ties with origin vector as that one dictates around which point sprite is rotated).
     * 
     * The received data is converted into structs of sprite render instances for the shader. The base vertex data GPU receives from the renderer
     * represents 4 vertices forming a 1x1 square. This base data is later transformed using instanced rendering into quads tailored for specific sprites.
     * For each submitted sprite a single render instance is created. This instance consists of data received at the submitting stage and packed into POD format.
     * Render instance stores: 
     * - origin vector, 
     * - translation vector, 
     * - scale vector, 
     * - clipping rectangle vector (x, y, w, h), 
     * - tint color RGB vector, 
     * - tint factor (how much the tint influences sprite color)
     * - rotation value in radians
     * These instances get grouped together in instances groups, with each group having a common texture to draw - that means the group stores texture ID 
     * and texture size (size gets used to scale the 1x1 square to its initial correct dimensions in space) aside from a collection of instances.
     * 
     * At the rendering stage all data stored in instance groups is sent to the GPU in seperate vertex buffer for instances. Then rendering batch structs are created, 
     * which represent the way data sent to the GPU is layed out. That data being instance amount and instance offset relative to buffer origin; on top of that there
     * is also texture ID and texture size, which are set before rendering a batch.
     * For each batch three operations are performed: binding the texture, setting texture size uniform and finally drawing instances using instance amount and offset.
     */
    class CSpriteRenderer : public IRenderer
    {
        struct SSpriteRender_Instance
        {
            vec2f origin;
            vec2f transl;
            vec2f scale;
            float rot;
            vec4f clipRect;
            vec3f tint;
            float tintFactor;
        };

        struct SSpriteRender_InstanceGroup
        {
            GLuint texID;
            vec2f texSize;
            std::vector< SSpriteRender_Instance > vecInstances;
        };

        struct SSpriteRender_Batch
        {
            GLuint texID;
            vec2f texSize;
            GLsizei instanceAmount;
            GLuint instanceOffset;
        };
        
    private:
        std::unordered_map< GLuint, SSpriteRender_InstanceGroup > m_mapTexIDToInstanceGroup;
        std::vector< SSpriteRender_Batch > m_vecBatches;

        std::shared_ptr<CBuffer> m_vboInst;
        CVertexArray m_vao;
        CUniform<vec2f> m_unifTexSize;

        GLsizei m_spriteCapacity;

        CSprite m_missingTexturePlaceholder;
        

    public:
        CSpriteRenderer() = default;

        void reserveBufferSpace( GLsizei targetSpriteCapacity );

        void clear() override;

        // Origin values should be in range <0;1> representing the normalized texture coordinate from which it should be transformed 
        void submitSprite( const CSprite& sprite, const vec2f& translation, const vec2f& origin = { 0.f, 0.f }, const vec2f& scale = { 1.f, 1.f }, double rotation = 0.0 );
        
        // Origin values should be in range <0;1> representing the normalized texture coordinate from which it should be transformed 
        // Method that takes the base CTexture2D object and proceeds with default values for CSprite specific fields
        void submitTexture( const CTexture2D& texture, const vec2f& translation, const vec2f& origin = { 0.f, 0.f }, const vec2f& scale = { 1.f, 1.f }, double rotation = 0.0 );


        void render() override;
        
        void render( const CFramebuffer& targetFramebuffer ) override;

    protected:
        bool setShaderProgram() override;
        bool initBuffers() override;
        void onInit() override;

        void prepareBuffers();
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_SPRITE_RENDERER_H__