#ifndef __CHESTNUT_DEBUG_H__
#define __CHESTNUT_DEBUG_H__

#include <iostream>

#ifdef CHESTNUT_DEBUG
    #define LOG(s) ( std::cout << __FILE__ << " (" << __LINE__ << ") : " << s << std::endl )
    #define LOG_CHANNEL( ch, s ) ( std::cout << "[" << ch << "] : " << s << std::endl )
#else
    #define LOG(s)
    #define LOG_CHANNEL( ch, s )
#endif

#endif // __CHESTNUT_DEBUG_H__
