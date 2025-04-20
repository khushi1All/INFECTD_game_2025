#pragma once
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <vector>

using namespace godot;

class ZombieSpawner : public Node2D {
    GDCLASS(ZombieSpawner, Node2D);

public:
    ZombieSpawner();

protected:
    static void _bind_methods();

private:
    Ref<PackedScene> zombie_scene;
    Timer *spawn_timer;

    std::vector<Vector2> zombies_to_spawn;
    int total_zombies_to_spawn = 15;
    int zombies_spawned = 0;
    bool spawning = false;

    void _ready() override;
    void spawn_next_zombie();
    void on_zombie_died();
};
