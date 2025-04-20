#include "../headers/GlobalState.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

GlobalState::GlobalState() {}

void GlobalState::_bind_methods() {
    // Bindings if needed
}

void GlobalState::_ready() {
    Node *current_scene = get_tree()->get_current_scene();
    if (current_scene->has_node("HUD")) {
        hud = current_scene->get_node("HUD");
    }
}

void GlobalState::add_score(int points) {
    score += points;
    UtilityFunctions::print("💯 Score: ", score);
}

void GlobalState::collect_element(const String &element) {
    if (!collected_elements.has(element)) {
        collected_elements.append(element);
        UtilityFunctions::print("🧪 Collected element: ", element);
    }

    int remaining = get_tree()->get_nodes_in_group("Antidote").size();
    UtilityFunctions::print("🧪 Remaining antidotes: ", remaining);

    if (remaining <= 1) {
        form_antidote();
    }
}

void GlobalState::form_antidote() {
    UtilityFunctions::print("✅ All antidote elements collected!");

    Node *scene = get_tree()->get_current_scene();
    if (scene && scene->has_method("_check_for_next_level")) {
        scene->call("_check_for_next_level");
    } else {
        UtilityFunctions::print("⚠️ Could not find _check_for_next_level in current scene!");
    }
}

