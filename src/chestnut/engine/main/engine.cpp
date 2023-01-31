#include "chestnut/engine/main/engine.hpp"

#include "chestnut/engine/misc/locked_auto_timer.hpp"
#include "chestnut/engine/misc/exception.hpp"
#include "chestnut/engine/misc/utility_functions.hpp"
#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/ecs_impl/systems/default_exit_system.hpp"

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include <algorithm>
#include <cassert>


namespace chestnut::engine
{    
    CEngine *CEngine::sm_instance = nullptr;


    CEngine::CEngine(CWindow& window, float updateInterval, bool defaultExitBehaviour)
    : m_defaultExitBehaviour(defaultExitBehaviour),
      m_window(window)
    {
        if( updateInterval <= 0 )
        {
            m_updateTimer = new CAutoTimer(0);
        }
        else
        {
            CLockedAutoTimer *lockedTimer = new CLockedAutoTimer( 0, updateInterval, true );
            lockedTimer->toggleThreadWaitingForTimerInterval( true );
            m_updateTimer = lockedTimer;
        }

        m_isRunning = false;
    }

    CEngine::~CEngine() 
    {
        delete m_updateTimer;
    }




    CEngine& CEngine::createInstance(CWindow& window, float updateInterval, bool defaultExitBehaviour)
    {
        if(sm_instance != nullptr)
        {
            delete sm_instance;
        }

        sm_instance = new CEngine(window, updateInterval, defaultExitBehaviour);
        return *sm_instance;
    }

    CEngine& CEngine::getInstance()
    {
        assert(sm_instance != nullptr && "Engine has not yet been instantiated");

        return *sm_instance;
    }

    void CEngine::deleteInstance()
    {
        if(sm_instance != nullptr)
        {
            delete sm_instance;
            sm_instance = nullptr;
        }
    }




    CWindow& CEngine::getWindow() 
    {
        return m_window;
    }

    ecs::CEntityWorld& CEngine::getEntityWorld() 
    {
        return m_entityWorld;
    }

    CEventManager& CEngine::getEventManager() 
    {
        return m_eventManager;
    }

    CAudioManager& CEngine::getAudioManager() 
    {
        return m_audioManager;
    }

    CResourceManager &CEngine::getResourceManager()
    {
        return m_resourceManager;
    }

    void CEngine::attachSystem(ILogicSystem *system)
    {
        // search for the spot where to insert the system
        auto it = m_listLogicSystems.begin();
        for( ;it != m_listLogicSystems.end(); ++it )
        {
            if( (*it)->getPriority() > system->getPriority() )
            {
                break;
            }
        }

        m_listLogicSystems.insert( it, system );

        try
        {
            system->onAttach();
        }
        catch(const std::exception& e)
        {
            LOG_ERROR("System attachment error: " << e.what());
            if(messageBoxYesNo("Error occured while attaching a system:\n" + std::string(e.what()) + "\nAbort the program?", "Error"))
            {
                exit(1);
            }
        }
    }

    void CEngine::attachSystem(IRenderingSystem *system)
    {
        // search for the spot where to insert the system
        auto it = m_listRenderingSystems.begin();
        for( ;it != m_listRenderingSystems.end(); ++it )
        {
            if( (*it)->getPriority() > system->getPriority() )
            {
                break;
            }
        }

        m_listRenderingSystems.insert( it, system );
        
        try
        {
            system->onAttach();
        }
        catch(const std::exception& e)
        {
            LOG_ERROR("System attachment error: " << e.what());
            if(messageBoxYesNo("Error occured while attaching a system:\n" + std::string(e.what()) + "\nAbort the program?", "Error"))
            {
                exit(1);
            }
        }
    }

    void CEngine::detachSystem(ILogicSystem *system)
    {
        for(auto it = m_listLogicSystems.begin(); it != m_listLogicSystems.end(); ++it)
        {
            if(*it == system)
            {
                try
                {
                    system->onDetach();
                }
                catch(const std::exception& e)
                {
                    LOG_ERROR("System detachment error: " << e.what());
                    if(messageBoxYesNo("Error occured while detaching a system:\n" + std::string(e.what()) + "\nAbort the program?", "Error"))
                    {
                        exit(1);
                    }
                }

                m_listLogicSystems.erase(it);
                return;
            }
        }       
    }

    void CEngine::detachSystem(IRenderingSystem *system)
    {
        for(auto it = m_listRenderingSystems.begin(); it != m_listRenderingSystems.end(); ++it)
        {
            if(*it == system)
            {
                try
                {
                    system->onDetach();
                }
                catch(const std::exception& e)
                {
                    LOG_ERROR("System detachment error: " << e.what());
                    if(messageBoxYesNo("Error occured while detaching a system:\n" + std::string(e.what()) + "\nAbort the program?", "Error"))
                    {
                        exit(1);
                    }
                }
                
                m_listRenderingSystems.erase(it);
                return;
            }
        }       
    }

    void CEngine::reorderSystems()
    {
        std::stable_sort(
            m_listLogicSystems.begin(),
            m_listLogicSystems.end(),

            [](const ILogicSystem *s1, const ILogicSystem *s2) {
                return s1->getPriority() < s2->getPriority();
            }
        );

        std::stable_sort(
            m_listRenderingSystems.begin(),
            m_listRenderingSystems.end(),

            [](const IRenderingSystem *s1, const IRenderingSystem *s2) {
                return s1->getPriority() < s2->getPriority();
            }
        );
    }




    void CEngine::start() 
    {
        if( m_listLogicSystems.empty() )
        {
            throw ChestnutException( "Engine needs at least one logic system to control it!");
        }

        if(m_defaultExitBehaviour)
        {
            attachSystem(new CDefaultExitSystem(SYSTEM_PRIORITY_HIGHEST));
        }

        m_isRunning = true;
        m_updateTimer->start();  
        gameLoop();
    }

    void CEngine::gameLoop() 
    {
        while( m_isRunning )
        {
            try
            {
                if( m_updateTimer->tick() )
                {
                    float dt = m_updateTimer->getDeltaTime();

                    for( ILogicSystem *sys : m_listLogicSystems )
                    {
                        sys->update( dt );
                    }


                    m_window.clear();

                #ifdef CHESTNUT_DEBUG
                    ImGui_ImplOpenGL3_NewFrame();
                    ImGui_ImplSDL2_NewFrame();
                    ImGui::NewFrame();
                #endif

                    for( IRenderingSystem  *sys : m_listRenderingSystems )
                    {
                        sys->render();
                    }

                #ifdef CHESTNUT_DEBUG
                    ImGui::Render();
                    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                #endif
                
                    m_window.flipBuffer();
                }
            }
            catch(const std::exception& e)
            {
                LOG_ERROR("Uncaught error in the engine: " << e.what());
                if(messageBoxYesNo("Unexpected error occured:\n" + std::string(e.what()) + "\nAbort the program?", "Error"))
                {
                    exit(1);
                }
            }
        }
    }

    void CEngine::stop()
    {
        m_isRunning = false;
    }

    float CEngine::getGameUpdatesPerSecond() 
    {
        return m_updateTimer->getUpdatesPerSec();
    }

    double CEngine::getGameTimeInSeconds() 
    {
        return m_updateTimer->getElapsedTimeInSeconds();
    }

} // namespace chestnut::engine
