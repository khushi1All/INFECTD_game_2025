#pragma once
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

using namespace godot;

class Player : public CharacterBody2D {
    GDCLASS(Player, CharacterBody2D);

public:
    enum State {
        IDLE,
        WALK,
        RUN,
        HURT,
        DEAD
    };

    Player();

protected:
    static void _bind_methods();

private:
    float speed = 110.0f;
    State state = IDLE;

    AnimatedSprite2D *sprite;
    AudioStreamPlayer2D *gun_sound;
    AudioStreamPlayer2D *footstep_sound;
    Node2D *spawn_point;

    int health = 100;
    int max_health = 100;
    int ammo = 0;
    bool has_key = false;

    void _ready() override;
    void _physics_process(double delta) override;
    void _process(double delta) override;

    void _move();
    void _update_animation();
    void shoot();
    void on_player_hit();
    void take_damage(int amount);
    void die();
};
