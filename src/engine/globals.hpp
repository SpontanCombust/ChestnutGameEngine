#ifndef __CHESTNUT_GLOBALS_H__
#define __CHESTNUT_GLOBALS_H__

namespace chestnut
{   
    // globally available application instance declaration
    extern class CApplication *__g_application;

    #define theApp __g_application

} // namespace chestnut

#endif // __CHESTNUT_GLOBALS_H__