#include "chestnut/engine/graphics/renderers/sprite_renderer.hpp"

#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/resources/shader_program_resource.hpp"
#include "chestnut/engine/misc/utility_functions.hpp"
#include "chestnut/engine/graphics/opengl/vertex_attribute_array.hpp"

namespace chestnut::engine
{   
    static const uint8_t missingTextureBytes[] = 
    {
        0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,
        0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,
        0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,
        0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff
    };




    bool CSpriteRenderer::setShaderProgram()
    {
        auto shader = CEngine::getInstance().getResourceManager().getOrLoadResource<CShaderProgramResource>(
            assetPathToAbsolute("shaders/sprite.shader")
        );

        if(shader) {
            m_shader = CShaderProgram(shader.value());
        } else {
            LOG_ERROR(shader.error());
            return false;
        }
        
        return true;
    }

    bool CSpriteRenderer::initBuffers() 
    {
        const vec2f vertices[] = {
            // pos            // uv
            vec2f(0.0, 0.0),  vec2f(0.0, 1.0),   // upper left
            vec2f(1.0, 0.0),  vec2f(1.0, 1.0),   // upper right
            vec2f(1.0, 1.0),  vec2f(1.0, 0.0),   // lower right
            vec2f(0.0, 1.0),  vec2f(0.0, 0.0)    // lower left
        };

        const GLuint indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        try
        {
            auto vboVert = std::make_shared<CBuffer>(
                CBuffer::EType::VERTEX,
                CBuffer::EUsage::STATIC_DRAW, 
                CBuffer::ELayout::ARRAY_OF_STRUCTS
            );
            vboVert->update(vertices, sizeof(vertices));

            m_vao.addBuffer(vboVert, {
                m_shader.getAttribute<vec2f>( "avPos", false ).value(),
                m_shader.getAttribute<vec2f>( "avUVPos", false ).value()
            });


            auto ibo = std::make_shared<CBuffer>(
                CBuffer::EType::INDEX,
                CBuffer::EUsage::STATIC_DRAW, 
                CBuffer::ELayout::SINGLE_ARRAY
            );
            ibo->update(indices, sizeof(indices));

            m_vao.addBuffer(ibo);


            m_vboInst = std::make_shared<CBuffer>(
                CBuffer::EType::VERTEX,
                CBuffer::EUsage::DYNAMIC_DRAW, 
                CBuffer::ELayout::ARRAY_OF_STRUCTS
            );

            m_vao.addBuffer(m_vboInst, {
                m_shader.getAttribute<vec2f>( "aiOrigin", true ).value(),
                m_shader.getAttribute<vec2f>( "aiTransl", true ).value(),
                m_shader.getAttribute<vec2f>( "aiScale", true ).value(),
                m_shader.getAttribute<float>( "aiRot", true ).value(),
                m_shader.getAttribute<vec4f>( "aiClipRect", true ).value(),
                m_shader.getAttribute<vec3f>( "aiTint", true ).value(),
                m_shader.getAttribute<float>( "aiTintFactor", true ).value()
            });
            

            m_vao.compose();


            m_unifTexSize = m_shader.getUniform<vec2f>( "uTexSize" ).value();
        }
        catch(const tl::bad_optional_access& e)
        {
            return false;
        }        

        return true;
    }

    void CSpriteRenderer::onInit() 
    {
        m_spriteCapacity = 0;
        reserveBufferSpace( CHESTNUT_SPRITE_RENDERER_INIT_SPRITE_CAPACITY );

        m_missingTexturePlaceholder = CSprite( *CTexture2DResource::loadFromPixels(missingTextureBytes, 8, 8, 3) );
        m_missingTexturePlaceholder.setFiltering( GL_NEAREST, GL_NEAREST );
    }

    void CSpriteRenderer::reserveBufferSpace( GLsizei targetSpriteCapacity ) 
    {
        m_shader.bind();
        
        if( targetSpriteCapacity <= m_spriteCapacity )
        {
            return;
        }
        
        m_vboInst->reserve(sizeof( SSpriteRender_Instance ) * targetSpriteCapacity);
        
        m_spriteCapacity = targetSpriteCapacity;
    }

    void CSpriteRenderer::clear() 
    {
        m_mapTexIDToInstanceGroup.clear();
        m_vecBatches.clear();
    }

    void CSpriteRenderer::submitSprite( const CSprite& sprite, const vec2f& translation, const vec2f& origin, const vec2f& scale, double rotation ) 
    {
        GLuint id;
        int w, h;
        SRectangle rect;

        if( sprite.isValid() )
        {
            id = sprite.getID();
            w = sprite.getWidth();
            h = sprite.getHeight();
            rect = sprite.getClippingRect();
        }
        else
        {
            id = m_missingTexturePlaceholder.getID();
            w = m_missingTexturePlaceholder.getWidth();
            h = m_missingTexturePlaceholder.getHeight();
            rect = m_missingTexturePlaceholder.getClippingRect();
        }
        

        SSpriteRender_Instance instance;
        instance.origin = origin;
        instance.transl = translation;
        instance.scale = scale;
        instance.rot = (float)rotation;
        instance.clipRect = vec4f( rect.x, 1.f - rect.y - rect.h, rect.w, rect.h ); // we have to shift Y around to adapt it to OpenGL's way of handling texture coords
        instance.tint = sprite.getTint();
        instance.tintFactor = sprite.getTintFactor();  

        auto& group = m_mapTexIDToInstanceGroup[id];
        group.texID = id;
        group.texSize = { (float)w, (float)h };
        group.vecInstances.push_back( instance );
    }

    void CSpriteRenderer::submitTexture( const CTexture2D& texture, const vec2f& translation, const vec2f& origin, const vec2f& scale, double rotation)
    {
        GLuint id;
        int w, h;

        if( texture.isValid() )
        {
            id = texture.getID();
            w = texture.getWidth();
            h = texture.getHeight();
        }
        else
        {
            id = m_missingTexturePlaceholder.getID();
            w = m_missingTexturePlaceholder.getWidth();
            h = m_missingTexturePlaceholder.getHeight();
        }
        

        SSpriteRender_Instance instance;
        instance.origin = origin;
        instance.transl = translation;
        instance.scale = scale;
        instance.rot = (float)rotation;
        instance.clipRect = { 0, 0, (float)w, (float)h };
        instance.tint = vec3f(1.f);
        instance.tintFactor = 0.f;

        auto& group = m_mapTexIDToInstanceGroup[id];
        group.texID = id;
        group.texSize = { (float)w, (float)h };
        group.vecInstances.push_back( instance );
    }

    void CSpriteRenderer::prepareBuffers() 
    {
        GLsizei spriteCount = 0;
        for( const auto& [ id, group ] : m_mapTexIDToInstanceGroup )
        {
            spriteCount += group.vecInstances.size();
        }

        if( spriteCount > m_spriteCapacity )
        {
            reserveBufferSpace( spriteCount );
        }

        size_t instanceAmount, instanceSizeBytes;
        size_t instanceOffset, instanceOffsetBytes;
        SSpriteRender_Batch batch;

        instanceOffset = 0;
        instanceOffsetBytes = 0;
        for( const auto& [ id, group ] : m_mapTexIDToInstanceGroup )
        {
            instanceAmount = group.vecInstances.size();
            instanceSizeBytes = instanceAmount * sizeof( SSpriteRender_Instance );

            m_vboInst->update((void *)group.vecInstances.data(), instanceSizeBytes, instanceOffsetBytes);

            batch.texID = group.texID;
            batch.texSize = group.texSize;
            batch.instanceOffset = instanceOffset;
            batch.instanceAmount = instanceAmount;
            m_vecBatches.push_back( batch );

            instanceOffset += instanceAmount;
            instanceOffsetBytes += instanceSizeBytes;
        }
    }

    void CSpriteRenderer::render() 
    {
        m_shader.bind();

        prepareBuffers();

        m_vao.bind();
        for( const SSpriteRender_Batch& batch : m_vecBatches )
        {
            glBindTexture( GL_TEXTURE_2D, batch.texID );
            m_unifTexSize.set(batch.texSize);
            glDrawElementsInstancedBaseInstance( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, batch.instanceAmount, batch.instanceOffset );
        }
        m_vao.unbind();
    }

    void CSpriteRenderer::render( const CFramebuffer& targetFramebuffer ) 
    {
        m_shader.bind();

        prepareBuffers();

        targetFramebuffer.bind();

        m_vao.bind();
        for( const SSpriteRender_Batch& batch : m_vecBatches )
        {
            glBindTexture( GL_TEXTURE_2D, batch.texID );
            m_unifTexSize.set(batch.texSize);
            glDrawElementsInstancedBaseInstance( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, batch.instanceAmount, batch.instanceOffset );
        }
        m_vao.unbind();

        targetFramebuffer.unbind();
    }

} // namespace chestnut::engine
