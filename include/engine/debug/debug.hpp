#ifndef __CHESTNUT_DEBUG_H__
#define __CHESTNUT_DEBUG_H__

#include <iostream>

#define DEBUG_MODE

namespace chestnut
{
    #ifdef DEBUG_MODE
        #define LOG(s) ( std::cout << __FILE__ << " (" << __LINE__ << ") : " << s << std::endl )
    #else
        #define LOG(s)
    #endif
    
} // namespace chestnut

#endif // __CHESTNUT_DEBUG_H__
