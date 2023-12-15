#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/godot.hpp>

#include "discordgodot.h"
using namespace godot;

static discord_sdk *discordsdk;

void initialize_discordsdk_module(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        ClassDB::register_class<discord_sdk>();
        discordsdk = memnew(discord_sdk);
        Engine::get_singleton()->register_singleton("discord_sdk", discord_sdk::get_singleton());
    }
}

void uninitialize_discordsdk_module(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        Engine::get_singleton()->unregister_singleton("discord_sdk");
    }
}

extern "C"
{
    GDExtensionBool GDE_EXPORT discordsdkgd_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
    {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_discordsdk_module);
        init_obj.register_terminator(uninitialize_discordsdk_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
