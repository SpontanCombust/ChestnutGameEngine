#include "engine/core/vector.hpp"

#include <cmath>

namespace chestnut
{
    std::string vector2fToString( Vector2f v ) 
    {
        return "[ " + std::to_string(v.x) + ", " + std::to_string(v.y) + " ]";
    }

    std::string vector2iToString( Vector2i v ) 
    {
        return "[ " + std::to_string(v.x) + ", " + std::to_string(v.y) + " ]";
    }

} // namespace chestnut
