#ifndef __CHESTNUT_TINDEX_H__
#define __CHESTNUT_TINDEX_H__

#include <typeindex>

namespace chestnut
{
    #define TINDEX(T) ( std::type_index( typeid( T ) ) )

    #define TINDEX_NAME(T) ( std::type_index( typeid( T ) ).name() )

} // namespace chestnut

#endif // __CHESTNUT_TINDEX_H__