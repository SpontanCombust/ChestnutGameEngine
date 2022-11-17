#pragma once

#include "chestnut/engine/macros.hpp"

#include <ostream>


namespace chestnut::engine::debug
{
    class CHESTNUT_API CLogger
    {
    public:
        static std::ostream *streamPtr;

        static void setToCout();
        static void setToCerr();
        static void setToClog();
        static void setToCustom( std::ostream *stream );
        static void setToFile( const char *filePath );

        static void flush();

        static std::string getCurrentDateString();

    private:
        static bool hasFileOpened;
        static void closeFileIfIsOpened();
    };

} // namespace chestnut::engine::debug

#ifdef CHESTNUT_DEBUG
    #define LOG(s, lvl) {\
        *chestnut::engine::debug::CLogger::streamPtr <<\
        chestnut::engine::debug::CLogger::getCurrentDateString() <<\
        " [" << lvl << "] " << "[ " << __FILE__ << " (" << __LINE__ << ") ] : " << s << std::endl;\
    }

    #define LOG_INFO(s)     LOG(s, "INFO")
    #define LOG_WARNING(s)  LOG(s, "WARNING")
    #define LOG_ERROR(s)    LOG(s, "ERROR")
#else
    #define LOG(s, lvl)
    #define LOG_INFO(s)
    #define LOG_WARNING(s)
    #define LOG_ERROR(s)
#endif
