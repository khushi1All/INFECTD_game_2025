#include "../headers/LevelScene.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

LevelScene::LevelScene() {}

void LevelScene::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_check_for_next_level"), &LevelScene::_check_for_next_level);
    ClassDB::bind_method(D_METHOD("show_level_transition", "level_name"), &LevelScene::show_level_transition);
}

void LevelScene::_ready() {
    Node *hud_node = get_node_or_null("Hud");
    if (hud_node) {
        transition_label = hud_node->get_node<Label>("LevelPopupLabel");
    }
    if (transition_label) {
        String current_scene = get_tree()->current_scene->get_scene_file_path();
        if (current_scene.contains("main_scene")) {
            show_level_transition("LEVEL 1");
        } else if (current_scene.contains("level2")) {
            show_level_transition("LEVEL 2");
        } else if (current_scene.contains("Level3")) {
            show_level_transition("LEVEL 3");
        }
    }
}

void LevelScene::show_level_transition(const String &level_name) {
    if (transition_label) {
        transition_label->set_text(level_name);
        transition_label->set_visible(true);

        Ref<Timer> timer = Timer::_new();
        timer->set_wait_time(1.5);
        timer->set_one_shot(true);
        add_child(timer);

        timer->connect("timeout", Callable([=]() {
            transition_label->set_visible(false);
            timer->queue_free();
        }));
        timer->start();
    }
}

void LevelScene::_check_for_next_level() {
    String path = get_tree()->current_scene->get_scene_file_path();

    if (path.contains("main_scene")) {
        get_tree()->change_scene_to_file("res://level2.tscn");
    } else if (path.contains("level2")) {
        get_tree()->change_scene_to_file("res://Level3.tscn");
    } else if (path.contains("Level3")) {
        get_tree()->change_scene_to_file("res://End.tscn");
    }
}

