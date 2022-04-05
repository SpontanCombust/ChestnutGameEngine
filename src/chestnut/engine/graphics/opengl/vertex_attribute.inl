#include "../../maths/vector2.hpp"
#include "../../maths/vector3.hpp"
#include "../../maths/vector4.hpp"

#include <type_traits>

namespace chestnut::engine
{
    template<typename T>
    CVertexAttribute CVertexAttribute::create(const std::string& name, GLint location, bool isInstanced)
    {
        EType type;
        GLint length;

        if constexpr(std::is_same_v<T, int>)
        {
            type = EType::INT;
            length = 1;
        }
        else if constexpr(std::is_same_v<T, vec2i>)
        {
            type = EType::INT;
            length = 2;
        }
        else if constexpr(std::is_same_v<T, unsigned int>)
        {
            type = EType::UINT;
            length = 1;
        }
        else if constexpr(std::is_same_v<T, float>)
        {
            type = EType::FLOAT;
            length = 1;
        }
        else if constexpr(std::is_same_v<T, vec2f>)
        {
            type = EType::FLOAT;
            length = 2;
        }
        else if constexpr(std::is_same_v<T, vec3f>)
        {
            type = EType::FLOAT;
            length = 3;
        }
        else if constexpr(std::is_same_v<T, vec4f>)
        {
            type = EType::FLOAT;
            length = 4;
        }
        else
        {
            static_assert(sizeof(T) == 0, "Template type not supported as vertex attribute type!");
        }
        

        return CVertexAttribute(name, location, type, length, isInstanced);
    }

} // namespace chestnut::engine
