#include "../headers/InstructionScreen.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

InstructionScreen::InstructionScreen() {}

void InstructionScreen::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_back_pressed"), &InstructionScreen::_on_back_pressed);
}

void InstructionScreen::_ready() {
    bg_music = get_node<AudioStreamPlayer2D>("AudioStreamPlayer2D");
    button_sound = get_node<AudioStreamPlayer2D>("Back/AudioStreamPlayer2D");

    if (bg_music) bg_music->play();

    get_node<Button>("Back")->connect("pressed", Callable(this, "_on_back_pressed"));
}

void InstructionScreen::_on_back_pressed() {
    if (button_sound) button_sound->play();
    get_tree()->create_timer(0.3)->connect("timeout", Callable([=]() {
        get_tree()->change_scene_to_file("res://MainMenu.tscn");
    }));
}
