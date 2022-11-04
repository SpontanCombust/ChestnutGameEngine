#pragma once


#include "chestnut/engine/macros.hpp"

#include <exception>
#include <string>

namespace chestnut::engine
{
    struct CHESTNUT_API ChestnutException : std::exception
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

} // namespace chestnut::engine

