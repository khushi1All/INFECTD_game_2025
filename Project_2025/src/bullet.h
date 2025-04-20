#pragma once
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

using namespace godot;

class Bullet : public Area2D {
    GDCLASS(Bullet, Area2D);

public:
    Bullet();

protected:
    static void _bind_methods();

private:
    float speed = 500.0f;
    float max_distance = 60.0f;
    Vector2 direction = Vector2(1, 0);
    Vector2 start_position;

    AnimatedSprite2D *sprite;

    void _ready() override;
    void _process(double delta) override;
    void _on_body_entered(Node *body);
};
