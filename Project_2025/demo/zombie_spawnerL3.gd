extends Node2D

var zombie_scene = preload("res://Assets/Zombies/ZombieTemplateLevel3.tscn")

# Handpicked safe spawn positions within maze rooms and corridors
var spawn_positions := [
	# Top-left room
	Vector2(120, 120), Vector2(140, 140), Vector2(160, 130),

	# Top-middle
	Vector2(300, 100), Vector2(320, 110), Vector2(280, 90),

	# Top-right room
	Vector2(360, 120), Vector2(380, 140), Vector2(340, 110),

	# Middle-center
	Vector2(300, 230), Vector2(320, 210), Vector2(280, 250),

	# Bottom-left room
	Vector2(120, 360), Vector2(140, 370), Vector2(160, 380),

	# Bottom-right room
	Vector2(360, 360), Vector2(380, 370), Vector2(340, 350),

	# Center tunnel area
	Vector2(300, 420), Vector2(320, 410), Vector2(280, 400)
]

var wave_number := 0
var zombies_killed_in_wave := 0
var current_wave_zombie_count := 0

func _ready():
	randomize()
	start_next_wave()

func start_next_wave():
	wave_number += 1
	current_wave_zombie_count = min(wave_number * 5, 35)
	zombies_killed_in_wave = 0

	print("🧟 Starting wave ", wave_number, " with ", current_wave_zombie_count, " zombies.")
	spawn_zombies_in_wave(current_wave_zombie_count)

func spawn_zombies_in_wave(count):
	for i in range(count):
		await get_tree().create_timer(0.6).timeout  # Delay for natural wave flow
		spawn_zombie()

func spawn_zombie():
	if spawn_positions.is_empty():
		print("⚠️ No spawn positions available!")
		return

	var spawn_pos = spawn_positions[randi() % spawn_positions.size()]
	spawn_pos += Vector2(randi_range(-4, 4), randi_range(-4, 4))  # Small offset to avoid stacking

	var zombie = zombie_scene.instantiate()

	# Random animation type for visual variety (e.g., walk1, walk2, walk3)
	var random_type = str(randi() % 3 + 1)
	if "anim_set" in zombie:
		zombie.anim_set = random_type

	zombie.position = spawn_pos
	add_child(zombie)

	if not zombie.is_connected("zombie_died", Callable(self, "_on_zombie_died")):
		zombie.connect("zombie_died", Callable(self, "_on_zombie_died"))

func _on_zombie_died():
	zombies_killed_in_wave += 1
	if zombies_killed_in_wave >= current_wave_zombie_count:
		await get_tree().create_timer(2.0).timeout  # Wait a bit before next wave
		start_next_wave()
