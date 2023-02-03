#include "chestnut/engine/ecs_impl/systems/debug_gui_rendering_system.hpp"

#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/debug/editor/gui_editor.hpp"

namespace chestnut::engine
{    
    void CDebugGuiRenderingSystem::render() 
    {
        try
        {
            debug::guiEntityListPanel(m_selectedEntity);
            debug::guiComponentInspector(m_selectedEntity);
            debug::guiMenuBar();
        }
        catch(const std::exception& e)
        {
            LOG_ERROR(e.what());
            m_selectedEntity = ecs::ENTITY_ID_INVALID;
        }
    }

} // namespace chestnut::engine
