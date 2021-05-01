#include "engine/libs.hpp"
#include "engine/types.hpp"
#include "engine/constants.hpp"
#include "engine/globals.hpp"

#include "engine/debug/debug.hpp"

#include "engine/maths/angles.hpp"
#include "engine/maths/rectangle.hpp"
#include "engine/maths/vector.hpp"
#include "engine/maths/vector2.hpp"
#include "engine/maths/vector3.hpp"
#include "engine/maths/vector4.hpp"
#include "engine/maths/matrix.hpp"
#include "engine/maths/matrix3.hpp"
#include "engine/maths/matrix4.hpp"
#include "engine/maths/vector_transform.hpp"

#include "engine/memory/multi_type_dynamic_memory_pool.hpp"

#include "engine/graphics/shader_program.hpp"
#include "engine/graphics/sprite_renderer.hpp"
#include "engine/graphics/texture2d.hpp"

#include "engine/misc/timers/auto_timer.hpp"
#include "engine/misc/timers/locked_auto_timer.hpp"
#include "engine/misc/timers/manual_timer.hpp"
#include "engine/misc/timers/locked_manual_timer.hpp"
#include "engine/misc/exception.hpp"
#include "engine/misc/tindex.hpp"
#include "engine/misc/resource_manager.hpp"

#include "engine/event_system/events/events.hpp"
#include "engine/event_system/event_helpers/event_constraint_functor_creators.hpp"
#include "engine/event_system/event_listener.hpp"
#include "engine/event_system/event_manager.hpp"
#include "engine/event_system/event_helpers/registers_keyboard_listeners.hpp"

#include "engine/ecs/component.hpp"
#include "engine/ecs/system.hpp"
#include "engine/ecs/management/component_set_signature.hpp"
#include "engine/ecs/management/component_batch.hpp"
#include "engine/ecs/management/entity_manager.hpp"
#include "engine/ecs/components/components.hpp"
#include "engine/ecs/systems/systems.hpp"

#include "engine/main/window.hpp"
#include "engine/main/application.hpp"
#include "engine/main/engine.hpp"