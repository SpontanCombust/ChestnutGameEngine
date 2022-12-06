#pragma once

#ifdef _WIN32
    // use after includes from the base library
    #undef CHESTNUT_API
    #ifdef ChestnutGameEngine_Graphics3D_EXPORTS
        #define CHESTNUT_API __declspec(dllexport)
    #else
        #define CHESTNUT_API __declspec(dllimport)
    #endif
#else
    #define CHESTNUT_API
#endif