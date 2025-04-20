#pragma once
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

class Hud : public CanvasLayer {
    GDCLASS(Hud, CanvasLayer);

public:
    Hud();

protected:
    static void _bind_methods();

private:
    Label *antidote_label;
    Label *position_label;
    Label *score_label;
    Label *popup_label;

    void _ready() override;
    void _process(double delta) override;

public:
    void show_level_transition(const String &text);
};
