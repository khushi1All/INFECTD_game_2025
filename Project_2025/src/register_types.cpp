#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>

// Include all your class headers
#include "player.h"
#include "bullet.h"
#include "zombie.h"
#include "zombie_spawner.h"
#include "hud.h"
#include "global_state.h"
#include "antidote.h"
#include "main_menu.h"
#include "camera_zoom.h"
#include "instruction_screen.h"
#include "level_scene.h"

using namespace godot;

void initialize_zombified_escape(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    // Register all your C++ classes
    ClassDB::register_class<Player>();
    ClassDB::register_class<Bullet>();
    ClassDB::register_class<Zombie>();
    ClassDB::register_class<ZombieSpawner>();
    ClassDB::register_class<Hud>();
    ClassDB::register_class<GlobalState>();
    ClassDB::register_class<Antidote>();
    ClassDB::register_class<MainMenu>();
    ClassDB::register_class<CameraZoom>();
    ClassDB::register_class<InstructionScreen>();
    ClassDB::register_class<LevelScene>();
}

void uninitialize_zombified_escape(ModuleInitializationLevel p_level) {
    // Optional: cleanup if needed
}

extern "C" {
GDExtensionBool GDE_EXPORT zombified_escape_init(
    GDExtensionInterfaceGetProcAddress p_get_proc_address,
    const GDExtensionClassLibraryPtr p_library,
    GDExtensionInitialization *r_initialization
) {
    static GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_zombified_escape);
    init_obj.register_terminator(uninitialize_zombified_escape);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}
}
