#include "chestnut/engine/debug/log.hpp"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

namespace chestnut::engine::debug
{   
    std::ostream *streamPtr = &std::cout;
    bool hasFileOpened = false;


    std::ostream* CLogger::getStreamPtr() 
    {
        return streamPtr;
    }

    void CLogger::setToCout() 
    {
        closeFileIfIsOpened();
        streamPtr = &std::cout;
    }

    void CLogger::setToCerr() 
    {
        closeFileIfIsOpened();
        streamPtr = &std::cerr;
    }

    void CLogger::setToClog() 
    {
        closeFileIfIsOpened();
        streamPtr = &std::clog;
    }

    void CLogger::setToCustom( std::ostream *stream ) 
    {
        closeFileIfIsOpened();
        streamPtr = stream;
    }

    void CLogger::setToFile( const char *filePath ) 
    {
        closeFileIfIsOpened();
        streamPtr = new std::ofstream( filePath, std::ios::out );
        hasFileOpened = true;
    }

    void CLogger::closeFileIfIsOpened() 
    {
        if( hasFileOpened )
        {
            // this also means this class owns the pointer this time
            static_cast< std::ofstream * >( streamPtr )->close();
            delete streamPtr;
            streamPtr = nullptr;

            hasFileOpened = false;
        }
    }

    void CLogger::flush() 
    {
        streamPtr->flush();
    }

    std::string CLogger::getCurrentDateString() 
    {
        std::tm tm;
        std::time_t t = std::time( nullptr );
        localtime_s(&tm, &t);

        std::ostringstream oss;
        oss << std::put_time( &tm, "%d-%m-%Y %H:%M:%S" );

        return oss.str();
    }

} // namespace chestnut::engine
