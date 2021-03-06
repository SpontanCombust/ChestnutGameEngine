#ifndef __CHESTNUT_EXCEPTION_H__
#define __CHESTNUT_EXCEPTION_H__

#include <exception>
#include <string>

namespace chestnut
{
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


#endif // __CHESTNUT_EXCEPTION_H__