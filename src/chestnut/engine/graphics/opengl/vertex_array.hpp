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

        std::vector<std::shared_ptr<CBuffer>> m_vecBuffers;

    public:
        CVertexArray();
        ~CVertexArray();

        void bind();
        void unbind();

        void addBuffer(std::shared_ptr<CBuffer> buffer);

        void update();
        bool shouldUpdate() const;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_VERTEX_ARRAY_H__