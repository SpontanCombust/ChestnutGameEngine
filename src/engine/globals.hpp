#ifndef __CHESTNUT_GLOBALS_H__
#define __CHESTNUT_GLOBALS_H__

#include "main/application.hpp"

namespace chestnut
{   
    // globally available application instance declaration
    extern CApplication *__g_application;

    #define theApp __g_application

    #define theEngine __g_application->engine

    #define theEntityManager __g_application->engine.entityManager

    #define theEventManager __g_application->engine.eventManager

} // namespace chestnut

#endif // __CHESTNUT_GLOBALS_H__