#pragma once
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

class LevelScene : public Node2D {
    GDCLASS(LevelScene, Node2D);

public:
    LevelScene();

protected:
    static void _bind_methods();

private:
    Label *transition_label;

    void _ready() override;

public:
    void _check_for_next_level();
    void show_level_transition(const String &level_name);
};
