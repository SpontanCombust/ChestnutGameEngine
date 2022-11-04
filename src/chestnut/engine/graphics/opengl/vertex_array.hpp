#pragma once


#include "chestnut/engine/macros.hpp"
#include "buffer.hpp"
#include "vertex_attribute_array.hpp"

#include <GL/glew.h>
#include <tl/optional.hpp>

#include <memory>
#include <vector>


namespace chestnut::engine
{
    class CHESTNUT_API CVertexArray
    {
    private:
        struct SBufferBinding
        {
            std::shared_ptr<CBuffer> buffer;
            tl::optional<CVertexAttributeArray> attributeArray;
        };

        GLuint m_id;
        std::vector<SBufferBinding> m_vecBufferBindings;

    public:
        CVertexArray();
        ~CVertexArray();

        CVertexArray(const CVertexArray& other);
        CVertexArray& operator=(const CVertexArray& other);

        CVertexArray(CVertexArray&& other);
        CVertexArray& operator=(CVertexArray&& other);


        GLuint getID() const;


        void bind();
        void unbind();

        void addBuffer(std::shared_ptr<CBuffer> buffer);
        void addBuffer(std::shared_ptr<CBuffer> buffer, const CVertexAttributeArray& attributeArray);


        // Bind all stored buffers and associated with them attributes to the VAO
        void compose();
    };

} // namespace chestnut::engine

