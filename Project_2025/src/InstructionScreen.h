#pragma once
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>
#include <godot_cpp/classes/button.hpp>

using namespace godot;

class InstructionScreen : public Control {
    GDCLASS(InstructionScreen, Control);

public:
    InstructionScreen();

protected:
    static void _bind_methods();

private:
    AudioStreamPlayer2D *bg_music;
    AudioStreamPlayer2D *button_sound;

    void _ready() override;
    void _on_back_pressed();
};
