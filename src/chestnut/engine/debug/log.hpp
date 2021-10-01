#ifndef __CHESTNUT_ENGINE_LOG_H__
#define __CHESTNUT_ENGINE_LOG_H__

#include <ostream>

namespace chestnut
{
    class CLogger
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

} // namespace chestnut

#ifdef CHESTNUT_DEBUG
    #define LOG_INFO(s) { *CLogger::streamPtr << CLogger::getCurrentDateString() << " [INFO] " << "[ " << __FILE__ << " (" << __LINE__ << ") ] : " << s << std::endl; }
    #define LOG_WARNING(s) { *CLogger::streamPtr << CLogger::getCurrentDateString() << " [WARNING] " << "[ " << __FILE__ << " (" << __LINE__ << ") ] : " << s << std::endl; }
    #define LOG_ERROR(s) { *CLogger::streamPtr << CLogger::getCurrentDateString() << " [ERROR] " << "[ " << __FILE__ << " (" << __LINE__ << ") ] : " << s << std::endl; }
#else
    #define LOG_INFO(s)
    #define LOG_WARNING(s)
    #define LOG_ERROR(s)
#endif

#endif // __CHESTNUT_ENGINE_LOG_H__