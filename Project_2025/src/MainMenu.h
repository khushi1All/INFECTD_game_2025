#pragma once
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>
#include <godot_cpp/classes/button.hpp>

using namespace godot;

class MainMenu : public Control {
    GDCLASS(MainMenu, Control);

public:
    MainMenu();

protected:
    static void _bind_methods();

private:
    AudioStreamPlayer2D *click_sound;

    void _ready() override;
    void _on_start_pressed();
    void _on_instructions_pressed();
    void _on_quit_pressed();
};

