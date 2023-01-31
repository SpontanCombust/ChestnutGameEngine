#include "chestnut/engine/ecs_impl/systems/default_exit_system.hpp"

#include "chestnut/engine/main/engine.hpp"

#include <SDL_events.h>

namespace chestnut::engine
{    
    void CDefaultExitSystem::onAttach() 
    {
        this->addEventListener("onExit", new CEventListener<SDL_QuitEvent>(
            [](const SDL_QuitEvent& e) {
                CEngine::getInstance().stop();
            }
        ));
    }

} // namespace chestnut::engine
