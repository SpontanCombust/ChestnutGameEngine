#pragma once


#include <chestnut/ecs/types.hpp>

namespace chestnut::engine::debug
{
    // Returns whether entity changed
    bool guiEntityListPanel(chestnut::ecs::entityid_t& selectedEnt);
    void guiComponentInspector(chestnut::ecs::entityid_t entity);
    void guiMenuBar();
    void guiMenuBarFile();
    void guiMenuBarView();

} // namespace chestnut::engine::debug
