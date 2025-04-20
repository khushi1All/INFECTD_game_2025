#pragma once
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/vector2.hpp>

using namespace godot;

class GlobalState : public Node {
    GDCLASS(GlobalState, Node);

public:
    GlobalState();

    static inline int score = 0;
    static inline Node *player = nullptr;
    static inline Array collected_elements;
    static inline Node *hud = nullptr;

protected:
    static void _bind_methods();

private:
    void _ready() override;

public:
    static void add_score(int points);
    static void collect_element(const String &element);
    static void form_antidote();
};

