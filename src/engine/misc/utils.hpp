#ifndef __CHESTNUT_UTILS_H__
#define __CHESTNUT_UTILS_H__

#include <typeindex>

#define TINDEX(T) ( std::type_index( typeid( T ) ) )

#endif // __CHESTNUT_UTILS_H__