#ifndef __CHESTNUT_GLOBALS_H__
#define __CHESTNUT_GLOBALS_H__

#include "main/application.hpp"

namespace chestnut
{   
    #define theApp (*CApplication::getInstance())

    #define theWindow CApplication::getInstance()->window

    #define theEngine CApplication::getInstance()->engine

    #define theEntityWorld CApplication::getInstance()->engine.entityWorld

    #define theEventManager CApplication::getInstance()->engine.eventManager

    #define theResourceManager CApplication::getInstance()->engine.resourceManager

} // namespace chestnut

#endif // __CHESTNUT_GLOBALS_H__