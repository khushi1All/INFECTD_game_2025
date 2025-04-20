#include "../headers/Antidote.h"
#include "GlobalState.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Antidote::Antidote() {}

void Antidote::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_body_entered", "body"), &Antidote::_on_body_entered);
    ClassDB::bind_method(D_METHOD("set_element_name", "name"), &Antidote::set_element_name);
    ClassDB::bind_method(D_METHOD("get_element_name"), &Antidote::get_element_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "element_name"), "set_element_name", "get_element_name");
}

void Antidote::_ready() {
    pickup_sound = get_node<AudioStreamPlayer2D>("AudioStreamPlayer2D");
    connect("body_entered", Callable(this, "_on_body_entered"));
    add_to_group("Antidote");
}

void Antidote::_on_body_entered(Node *body) {
    if (body->is_in_group("Player")) {
        if (pickup_sound) {
            pickup_sound->play();
        }

        GlobalState::collect_element(element_name);

        Node *scene = get_tree()->get_current_scene();
        if (get_tree()->get_nodes_in_group("Antidote").size() <= 1 && scene && scene->has_method("_check_for_next_level")) {
            scene->call("_check_for_next_level");
        }

        call_deferred("queue_free");
    }
}

String Antidote::get_element_name() const {
    return element_name;
}

void Antidote::set_element_name(const String &name) {
    element_name = name;
}
