#ifndef __CHESTNUT_UTILS_H__
#define __CHESTNUT_UTILS_H__

#include <exception>
#include <typeindex>

namespace chestnut
{
    #define TINDEX(T) ( std::type_index( typeid( T ) ) )

    struct ChestnutException : std::exception
    {
        const std::string msg;
        ChestnutException( const std::string _msg ) : msg( _msg )
        {

        }

        const char* what() const throw()
        {
            return msg.c_str();
        }
    };

} // namespace chestnut


#endif // __CHESTNUT_UTILS_H__