#include "engine/main/engine.hpp"

namespace engine
{
    void CEngine::enterGameLoop()
    {
        // PLACEHOLDER; TO BE CHANGED LATER
        while( m_isRunning )
        {
            onUserUpdate();
            update();

            SDL_Delay(3000);
            m_isRunning = false;
        }
    }
       
} // namespace engine