#pragma once
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

class Antidote : public Area2D {
    GDCLASS(Antidote, Area2D);

public:
    Antidote();

protected:
    static void _bind_methods();

private:
    String element_name;
    AudioStreamPlayer2D *pickup_sound;

    void _ready() override;
    void _on_body_entered(Node *body);
};
