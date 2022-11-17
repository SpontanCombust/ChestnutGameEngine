#pragma once


#include <chestnut/ecs/types.hpp>

namespace chestnut::engine::debug
{
    // Returns whether entity changed
    bool guiEntityListPanel(chestnut::ecs::entityid_t& selectedEnt);
    void guiComponentListPanel(chestnut::ecs::entityid_t entity);

} // namespace chestnut::engine::debug
