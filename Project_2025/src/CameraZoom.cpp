#include "../headers/CameraZoom.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

CameraZoom::CameraZoom() {}

void CameraZoom::_bind_methods() {
    // No methods to bind yet
}

void CameraZoom::_ready() {
    set_zoom(Vector2(4.9, 4.9));
}
