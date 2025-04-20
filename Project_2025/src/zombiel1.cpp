#include "../headers/Zombie.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

Zombie::Zombie() {}

void Zombie::_bind_methods() {
    // Add signals and bindings if needed
}

void Zombie::_ready() {
    sprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
    nav_agent = get_node<NavigationAgent2D>("NavigationAgent2D");
    walk_sound = get_node<AudioStreamPlayer2D>("ZombieSound");
    blood_particles = get_node<Particle2D>("BloodParticles");
    collision_shape = get_node<CollisionShape2D>("CollisionShape2D");
    player = get_tree()->get_first_node_in_group("Player");

    add_to_group("zombie");

    String walk_anim = "walk" + anim_set;
    if (sprite->get_sprite_frames()->has_animation(walk_anim)) {
        sprite->play(walk_anim);
    }

    if (player) {
        nav_agent->set_target_position(player->get_global_position());
        nav_agent->connect("velocity_computed", Callable(this, "_on_velocity_computed"));
    }
}

void Zombie::_physics_process(double delta) {
    if (!player || is_attacking || is_dead) return;

    nav_agent->set_target_position(player->get_global_position());
    nav_agent->set_velocity(get_direction_to_player() * speed);

    if (nav_agent->get_velocity().x != 0) {
        sprite->set_flip_h(nav_agent->get_velocity().x < 0);
    }
}

void Zombie::_on_velocity_computed(Vector2 safe_velocity) {
    set_velocity(safe_velocity);
    move_and_slide();
}

void Zombie::_process(double delta) {
    if (!player || is_dead) return;

    Vector2 dir = get_direction_to_player();
    float dist = get_global_position().distance_to(player->get_global_position());

    if (!is_attacking) {
        set_position(get_position() + dir * 50.0f * delta);
        move_and_slide();
    }

    if (dist < NEAR_DISTANCE && !walk_sound->is_playing()) {
        walk_sound->play();
        sound_was_playing = true;
    } else if (dist >= NEAR_DISTANCE && sound_was_playing) {
        walk_sound->stop();
        sound_was_playing = false;
    }

    if (dist < ATTACK_DISTANCE && !is_attacking) {
        start_attack();
    } else if (dist >= ATTACK_DISTANCE && is_attacking) {
        is_attacking = false;
        String walk_anim = "walk" + anim_set;
        if (sprite->get_sprite_frames()->has_animation(walk_anim)) {
            sprite->play(walk_anim);
        }
    }
}

Vector2 Zombie::get_direction_to_player() {
    return (player->get_global_position() - get_global_position()).normalized();
}

void Zombie::start_attack() {
    is_attacking = true;
    String attack_anim = "attack" + anim_set;
    if (sprite->get_sprite_frames()->has_animation(attack_anim)) {
        sprite->play(attack_anim);
        // You could simulate await using timers or coroutine plugin
    }
}

void Zombie::take_damage(int amount) {
    if (is_dead) return;
    health -= amount;
    if (health > 0) {
        String hurt_anim = "hurt" + anim_set;
        if (sprite->get_sprite_frames()->has_animation(hurt_anim)) {
            sprite->play(hurt_anim);
        }
    } else {
        die();
    }
}

void Zombie::die() {
    is_dead = true;
    walk_sound->stop();
    if (collision_shape) collision_shape->set_deferred("disabled", true);
    if (blood_particles) blood_particles->set_emitting(true);

    int rand = UtilityFunctions::randi() % 3 + 1;
    String dead_anim = "dead" + String::num_int64(rand);
    if (sprite->get_sprite_frames()->has_animation(dead_anim)) {
        sprite->play(dead_anim);
    }

    // Add points to score via global singleton if needed
    // Call deferred queue_free() if using signals
    queue_free();
}
