#ifndef __CHESTNUT_ENGINE_VERTEX_ARRAY_H__
#define __CHESTNUT_ENGINE_VERTEX_ARRAY_H__

#include "buffer.hpp"

#include <GL/glew.h>

#include <memory>
#include <vector>


namespace chestnut::engine
{
    class CVertexArray
    {
    private:
        GLuint m_id;

        mutable bool m_shouldUpdate;
        std::vector<std::shared_ptr<IBuffer>> m_vecBuffers;

    public:
        CVertexArray();
        ~CVertexArray();

        CVertexArray(const CVertexArray& other);
        CVertexArray& operator=(const CVertexArray& other);

        CVertexArray(CVertexArray&& other);
        CVertexArray& operator=(CVertexArray&& other);


        void bind();
        void unbind();

        void addBuffer(std::shared_ptr<IBuffer> buffer);

        // Recomposes VAO by binding all stored buffers and associated with them attributes
        void update();
        bool shouldUpdate() const;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_VERTEX_ARRAY_H__