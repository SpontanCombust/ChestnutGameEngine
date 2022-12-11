#pragma once


#include <typeindex>

namespace chestnut::engine
{
    // Returns demangled name of the type
    const char * rttiTypeName(const std::type_index& typeIndex);
    const char * rttiTypeName(const std::type_info& typeInfo);

} // namespace chestnut::engine
