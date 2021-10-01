#ifndef __CHESTNUT_ENGINE_EXCEPTION_H__
#define __CHESTNUT_ENGINE_EXCEPTION_H__

#include <exception>
#include <string>

namespace chestnut::engine
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

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_EXCEPTION_H__