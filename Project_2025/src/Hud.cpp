#include "../headers/Hud.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "GlobalState.h" // Optional if you use global singletons

using namespace godot;

Hud::Hud() {}

void Hud::_bind_methods() {
    ClassDB::bind_method(D_METHOD("show_level_transition", "text"), &Hud::show_level_transition);
}

void Hud::_ready() {
    antidote_label = get_node<Label>("LabelContainer/AntidoteLabel");
    position_label = get_node<Label>("LabelContainer/PositionLabel");
    score_label = get_node<Label>("LabelContainer/ScoreLabel");
    popup_label = get_node<Label>("LevelPopupLabel");
}

void Hud::_process(double delta) {
    Node *player = get_tree()->get_first_node_in_group("Player");
    if (player) {
        Vector2 pos = player->get("global_position");
        position_label->set_text("📍 Position: (" + String::num(pos.x, 1) + ", " + String::num(pos.y, 1) + ")");
    }

    score_label->set_text("💯 Score: " + String::num_int64(GlobalState::score));

    Array antidotes = get_tree()->get_nodes_in_group("Antidote");
    antidote_label->set_text("🧪 Antidotes Left: " + String::num_int64(antidotes.size()));
}

void Hud::show_level_transition(const String &text) {
    popup_label->set_text(text);
    popup_label->set_visible(true);

    Ref<Timer> timer = Timer::_new();
    timer->set_wait_time(1.5);
    timer->set_one_shot(true);
    add_child(timer);

    timer->connect("timeout", Callable([=]() {
        popup_label->set_visible(false);
        timer->queue_free();
    }));

    timer->start();
}
