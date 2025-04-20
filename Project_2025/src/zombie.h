#pragma once
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/navigation_agent2d.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/godot.hpp>
#include <godot_cpp/classes/particle2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

using namespace godot;

class Zombie : public CharacterBody2D {
    GDCLASS(Zombie, CharacterBody2D);

public:
    Zombie();

protected:
    static void _bind_methods();

private:
    float speed = 80.0f;
    String anim_set = "1";
    int health = 3;
    bool is_attacking = false;
    bool is_dead = false;
    bool sound_was_playing = false;

    const float NEAR_DISTANCE = 200.0f;
    const float ATTACK_DISTANCE = 10.0f;

    AnimatedSprite2D *sprite;
    NavigationAgent2D *nav_agent;
    AudioStreamPlayer2D *walk_sound;
    CollisionShape2D *collision_shape;
    Node *player;
    Particle2D *blood_particles;

    void _ready() override;
    void _physics_process(double delta) override;
    void _process(double delta) override;

    void _on_velocity_computed(Vector2 safe_velocity);
    Vector2 get_direction_to_player();
    void start_attack();
    void take_damage(int amount = 1);
    void die();
};
