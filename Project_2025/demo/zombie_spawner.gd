extends Node2D

var zombie_scene = preload("res://Assets/Zombies/ZombieTemplate.tscn")

var zombies_to_spawn = []
var total_zombies_to_spawn := 15
var zombies_spawned := 0
var spawning := false
var current_zombie = null

@onready var spawn_timer := Timer.new()

func _ready():
	spawn_timer.wait_time = 3.0
	spawn_timer.one_shot = true
	spawn_timer.connect("timeout", Callable(self, "spawn_next_zombie"))
	add_child(spawn_timer)

	zombies_to_spawn = [
		Vector2(100, 100), Vector2(200, 100), Vector2(300, 100),
		Vector2(400, 100), Vector2(500, 100), Vector2(-100, 100),
		Vector2(-200, 100), Vector2(70, 100), Vector2(473, 100),
		Vector2(-250, 100), Vector2(120, 150), Vector2(260, 180),
		Vector2(340, 120), Vector2(-120, 140), Vector2(280, 160)
	]
	zombies_to_spawn.shuffle()

	spawn_next_zombie()

func spawn_next_zombie():
	if spawning or zombies_spawned >= total_zombies_to_spawn:
		if zombies_spawned >= total_zombies_to_spawn:
			print("✅ All zombies spawned and defeated in Level 1!")
		return

	spawning = true

	if zombies_to_spawn.size() > 0:
		var pos = zombies_to_spawn.pop_front()
		var zombie = zombie_scene.instantiate()
		zombie.position = pos

		# Assign a random animation type (1 to 3)
		var random_type = str(randi() % 3 + 1)
		if "anim_set" in zombie:
			zombie.anim_set = random_type

		add_child(zombie)
		current_zombie = zombie
		zombies_spawned += 1

		if not zombie.is_connected("zombie_died", Callable(self, "on_zombie_died")):
			zombie.connect("zombie_died", Callable(self, "on_zombie_died"))

	spawning = false

func on_zombie_died():
	spawn_timer.start()
