#pragma once

#include <iostream>

#ifdef DEBUG_MODE
    #define LOG(s) ( std::cout << __FILE__ << " (" << __LINE__ << ") : " << s << std::endl )
#else
    #define LOG(s)
#endif
