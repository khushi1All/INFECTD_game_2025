#include "../headers/Player.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_action.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Player::Player() {}

void Player::_bind_methods() {
    // You can expose methods here
}

void Player::_ready() {
    sprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
    gun_sound = get_node<AudioStreamPlayer2D>("GunSound");
    footstep_sound = get_node<AudioStreamPlayer2D>("FootstepSound");
    spawn_point = get_node<Node2D>("Gun/BulletSpawnPoint");
    add_to_group("Player");
}

void Player::_physics_process(double delta) {
    _move();
    _update_animation();
}

void Player::_process(double delta) {
    if (Input::get_singleton()->is_action_just_pressed("shoot")) {
        shoot();
    }
}

void Player::_move() {
    Vector2 velocity = Vector2();
    bool is_moving = false;

    if (Input::get_singleton()->is_action_pressed("move_left")) {
        velocity.x = -1;
        sprite->set_flip_h(true);
        is_moving = true;
    } else if (Input::get_singleton()->is_action_pressed("move_right")) {
        velocity.x = 1;
        sprite->set_flip_h(false);
        is_moving = true;
    }

    if (Input::get_singleton()->is_action_pressed("move_up")) {
        velocity.y = -1;
        is_moving = true;
    } else if (Input::get_singleton()->is_action_pressed("move_down")) {
        velocity.y = 1;
        is_moving = true;
    }

    if (velocity.length() > 0) {
        float current_speed = speed;
        if (Input::get_singleton()->is_action_pressed("run")) {
            current_speed *= 1.5f;
            state = RUN;
        } else {
            state = WALK;
        }

        velocity = velocity.normalized() * current_speed;
        set_velocity(velocity);
        move_and_slide();

        if (!footstep_sound->is_playing()) {
            footstep_sound->play();
        }
    } else {
        state = IDLE;
        footstep_sound->stop();
        set_velocity(Vector2());
        move_and_slide();
    }
}

void Player::_update_animation() {
    switch (state) {
        case IDLE:
            sprite->play("idle");
            break;
        case WALK:
            sprite->play("walk");
            break;
        case RUN:
            sprite->play("run");
            break;
        case HURT:
            sprite->play("hurt");
            break;
        case DEAD:
            sprite->play("dead");
            break;
    }
}

void Player::shoot() {
    Ref<PackedScene> bullet_scene = ResourceLoader::get_singleton()->load("res://bullet.tscn");
    Node2D *bullet = cast_to<Node2D>(bullet_scene->instantiate());
    Vector2 spawn_pos = spawn_point->get_global_position();

    if (sprite->is_flip_h()) {
        spawn_pos.x -= 10;
    }
    bullet->set_global_position(spawn_pos);

    Node2D *bullet_sprite = bullet->get_node<Node2D>("AnimatedSprite2D");
    bullet_sprite->set("flip_h", sprite->is_flip_h());
    bullet_sprite->call("play", "fly");

    get_tree()->get_current_scene()->add_child(bullet);
    gun_sound->play();
}

void Player::on_player_hit() {
    if (state == DEAD || state == HURT)
        return;

    state = HURT;
    sprite->play("hurt");
    // You would handle await in GDScript here using coroutines if needed
    state = IDLE;
}

void Player::take_damage(int amount) {
    health -= amount;
    if (health <= 0) {
        die();
    }
}

void Player::die() {
    state = DEAD;
    queue_free();
}
