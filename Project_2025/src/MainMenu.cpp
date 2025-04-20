#include "../headers/MainMenu.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

MainMenu::MainMenu() {}

void MainMenu::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_start_pressed"), &MainMenu::_on_start_pressed);
    ClassDB::bind_method(D_METHOD("_on_instructions_pressed"), &MainMenu::_on_instructions_pressed);
    ClassDB::bind_method(D_METHOD("_on_quit_pressed"), &MainMenu::_on_quit_pressed);
}

void MainMenu::_ready() {
    click_sound = get_node<AudioStreamPlayer2D>("AudioStreamPlayer2D");

    get_node<Button>("Start")->connect("pressed", Callable(this, "_on_start_pressed"));
    get_node<Button>("Instructions")->connect("pressed", Callable(this, "_on_instructions_pressed"));
    get_node<Button>("Quit")->connect("pressed", Callable(this, "_on_quit_pressed"));
}

void MainMenu::_on_start_pressed() {
    if (click_sound) click_sound->play();
    get_tree()->create_timer(0.001)->connect("timeout", Callable([=]() {
        get_tree()->change_scene_to_file("res://main_scene.tscn");
    }));
}

void MainMenu::_on_instructions_pressed() {
    if (click_sound) click_sound->play();
    get_tree()->create_timer(0.1)->connect("timeout", Callable([=]() {
        get_tree()->change_scene_to_file("res://instruction.tscn");
    }));
}

void MainMenu::_on_quit_pressed() {
    if (click_sound) click_sound->play();
    get_tree()->create_timer(0.1)->connect("timeout", Callable([=]() {
        get_tree()->quit();
    }));
}
