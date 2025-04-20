#pragma once
#include <godot_cpp/classes/camera2d.hpp>

using namespace godot;

class CameraZoom : public Camera2D {
    GDCLASS(CameraZoom, Camera2D);

public:
    CameraZoom();

protected:
    static void _bind_methods();

private:
    void _ready() override;
};
