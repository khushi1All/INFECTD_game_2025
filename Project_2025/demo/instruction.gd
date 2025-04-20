extends Control

@onready var bg_music = $AudioStreamPlayer2D
@onready var button_sound = $Back/AudioStreamPlayer2D

func _ready():
	bg_music.play()  # Start background music when scene loads

func _on_back_pressed():
	button_sound.play()  # Play click sound
	await get_tree().create_timer(0.3).timeout  # Wait for sound to finish a bit
	get_tree().change_scene_to_file("res://MainMenu.tscn")
