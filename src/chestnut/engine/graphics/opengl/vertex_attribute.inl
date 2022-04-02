#include <type_traits>

namespace chestnut::engine
{
    template<typename T>
    tl::optional<CVertexAttribute::EType> CVertexAttribute::deduceTypeEnum()
    {
        if constexpr(std::is_same_v<T, GLbyte>)
        {
            return CVertexAttribute::EType::BYTE;
        }
        if constexpr(std::is_same_v<T, GLubyte>)
        {
            return CVertexAttribute::EType::UBYTE;
        }
        if constexpr(std::is_same_v<T, GLshort>)
        {
            return CVertexAttribute::EType::SHORT;
        }
        if constexpr(std::is_same_v<T, GLushort>)
        {
            return CVertexAttribute::EType::USHORT;
        }
        if constexpr(std::is_same_v<T, GLint>)
        {
            return CVertexAttribute::EType::INT;
        }
        if constexpr(std::is_same_v<T, GLuint>)
        {
            return CVertexAttribute::EType::UINT;
        }
        if constexpr(std::is_same_v<T, GLfloat>)
        {
            return CVertexAttribute::EType::FLOAT;
        }
        
        return tl::nullopt;
    }

} // namespace chestnut::engine
