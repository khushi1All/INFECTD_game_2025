extends Node2D

@onready var hud = get_node("Hud")

func _ready():
	Global.collected_elements.clear()
	hud.show_level_transition("LEVEL 2")

func _check_for_next_level():
	var scene_path = get_tree().current_scene.scene_file_path
	match scene_path:
		"res://main_scene.tscn":
			get_tree().change_scene_to_file("res://level2.tscn")
		"res://level2.tscn":
			get_tree().change_scene_to_file("res://Level3.tscn")
		"res://Level3.tscn":
			get_tree().change_scene_to_file("res://End.tscn")
