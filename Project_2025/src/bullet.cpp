#include "../headers/Bullet.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Bullet::Bullet() {}

void Bullet::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_body_entered", "body"), &Bullet::_on_body_entered);
}

void Bullet::_ready() {
    start_position = get_position();
    sprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
    sprite->play("fly");
    connect("body_entered", Callable(this, "_on_body_entered"));
}

void Bullet::_process(double delta) {
    set_position(get_position() + direction * speed * delta);
    if (get_position().distance_to(start_position) > max_distance) {
        queue_free();
    }
}

void Bullet::_on_body_entered(Node *body) {
    if (body->is_in_group("zombie")) {
        if (body->has_method("take_damage")) {
            body->call("take_damage");
        }
        queue_free();
    }
}
