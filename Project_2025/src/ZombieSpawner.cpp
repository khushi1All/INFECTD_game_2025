#include "../headers/ZombieSpawner.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/callable.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <algorithm>

using namespace godot;

ZombieSpawner::ZombieSpawner() {}

void ZombieSpawner::_bind_methods() {
    ClassDB::bind_method(D_METHOD("on_zombie_died"), &ZombieSpawner::on_zombie_died);
}

void ZombieSpawner::_ready() {
    zombie_scene = ResourceLoader::get_singleton()->load("res://Assets/Zombies/ZombieTemplate.tscn");
    spawn_timer = memnew(Timer);
    spawn_timer->set_wait_time(3.0);
    spawn_timer->set_one_shot(true);
    spawn_timer->connect("timeout", Callable(this, "spawn_next_zombie"));
    add_child(spawn_timer);

    zombies_to_spawn = {
        Vector2(100, 100), Vector2(200, 100), Vector2(300, 100),
        Vector2(400, 100), Vector2(500, 100), Vector2(-100, 100),
        Vector2(-200, 100), Vector2(70, 100), Vector2(473, 100),
        Vector2(-250, 100), Vector2(120, 150), Vector2(260, 180),
        Vector2(340, 120), Vector2(-120, 140), Vector2(280, 160)
    };

    std::random_shuffle(zombies_to_spawn.begin(), zombies_to_spawn.end());
    spawn_next_zombie();
}

void ZombieSpawner::spawn_next_zombie() {
    if (spawning || zombies_spawned >= total_zombies_to_spawn) {
        if (zombies_spawned >= total_zombies_to_spawn) {
            UtilityFunctions::print("✅ All zombies spawned and defeated in Level 1!");
        }
        return;
    }

    spawning = true;

    if (!zombies_to_spawn.empty()) {
        Vector2 pos = zombies_to_spawn.back();
        zombies_to_spawn.pop_back();

        Node2D *zombie = cast_to<Node2D>(zombie_scene->instantiate());
        zombie->set_position(pos);

        int random_type = UtilityFunctions::randi() % 3 + 1;
        if (zombie->has("anim_set")) {
            zombie->set("anim_set", String::num_int64(random_type));
        }

        add_child(zombie);

        if (!zombie->is_connected("zombie_died", Callable(this, "on_zombie_died"))) {
            zombie->connect("zombie_died", Callable(this, "on_zombie_died"));
        }

        zombies_spawned++;
    }

    spawning = false;
}

void ZombieSpawner::on_zombie_died() {
    spawn_timer->start();
}
