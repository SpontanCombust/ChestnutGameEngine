#ifndef __CHESTNUT_ENGINE_EXCEPTION_H__
#define __CHESTNUT_ENGINE_EXCEPTION_H__

#include <exception>
#include <string>

namespace chestnut::engine
{
    struct ChestnutException : std::exception
    {
        const std::string msg;

        ChestnutException( const std::string& _msg ) : msg( _msg )
        {

        }

        const char* what() const throw()
        {
            return msg.c_str();
        }
    };

    struct ChestnutResourceLoadException : std::exception
    {
        const std::string reason;
        std::string msg;

        ChestnutResourceLoadException( const std::string& _resourceName, const std::string& _path, const std::string& _reason ) 
        : reason( _reason )
        {
            msg = "Failed to load " + _resourceName + " resource from file: " + _path + ". Cause: " + _reason + ".";
        }

        const char* what() const throw()
        {
            return msg.c_str();
        }
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_EXCEPTION_H__