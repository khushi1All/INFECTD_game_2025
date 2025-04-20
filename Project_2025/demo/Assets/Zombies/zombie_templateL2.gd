extends CharacterBody2D

@export var speed := 100  # Slightly faster in Level 2
@export var anim_set := "1"  # Use "1", "2", or "3"
@export var health := 4  # Slightly tougher in Level 2
signal zombie_died

@onready var player = get_tree().get_first_node_in_group("Player")
@onready var nav_agent = $NavigationAgent2D
@onready var sprite = $AnimatedSprite2D
@onready var walk_sound = $ZombieSound
@onready var blood_particles = $BloodParticles
@onready var collision_shape = $CollisionShape2D

var sound_was_playing := false
var is_attacking = false
var is_dead := false

const NEAR_DISTANCE := 200
const ATTACK_DISTANCE := 10

func _ready():
	randomize()
	add_to_group("zombie")

	var walk_anim = "walk" + anim_set
	if walk_anim in sprite.sprite_frames.get_animation_names():
		sprite.play(walk_anim)

	if player:
		nav_agent.target_position = player.global_position
		nav_agent.velocity_computed.connect(_on_velocity_computed)

func _physics_process(_delta):
	if not player or is_attacking or is_dead:
		return

	nav_agent.target_position = player.global_position
	nav_agent.set_velocity(get_direction_to_player() * speed)

	if nav_agent.velocity.x != 0:
		sprite.flip_h = nav_agent.velocity.x < 0

func _on_velocity_computed(safe_velocity):
	velocity = safe_velocity
	move_and_slide()

func get_direction_to_player() -> Vector2:
	return (player.global_position - global_position).normalized()

func _process(delta):
	if not Global.player or is_dead:
		return

	var dist = global_position.distance_to(Global.player.global_position)
	var direction = (Global.player.global_position - global_position).normalized()

	if not is_attacking:
		position += direction * 50 * delta
		move_and_slide()

	# Walking sound
	if dist < NEAR_DISTANCE:
		if not walk_sound.playing:
			walk_sound.play()
			sound_was_playing = true
	else:
		if sound_was_playing:
			walk_sound.stop()
			sound_was_playing = false

	# Trigger attack
	if dist < ATTACK_DISTANCE and not is_attacking:
		start_attack()
	elif dist >= ATTACK_DISTANCE and is_attacking:
		sprite.stop()
		is_attacking = false
		var walk_anim = "walk" + anim_set
		if walk_anim in sprite.sprite_frames.get_animation_names():
			sprite.play(walk_anim)

func start_attack():
	var attack_anim = "attack" + anim_set
	if attack_anim in sprite.sprite_frames.get_animation_names():
		is_attacking = true
		sprite.play(attack_anim)
		await sprite.animation_finished

		if global_position.distance_to(Global.player.global_position) < ATTACK_DISTANCE:
			# Optional: Global.player.take_damage()
			pass

		is_attacking = false
		var walk_anim = "walk" + anim_set
		if walk_anim in sprite.sprite_frames.get_animation_names():
			sprite.play(walk_anim)

func take_damage(amount := 1):
	if is_dead:
		return

	health -= amount
	print("Zombie hurt! Health: ", health)

	if health > 0:
		var hurt_anim = "hurt" + anim_set
		if hurt_anim in sprite.sprite_frames.get_animation_names():
			sprite.play(hurt_anim)
			await sprite.animation_finished
	else:
		die()

func die():
	is_dead = true
	walk_sound.stop()

	# Disable collisions safely
	if collision_shape:
		collision_shape.call_deferred("set_disabled", true)

	if blood_particles:
		blood_particles.emitting = true

	# Play a random death animation
	var rand = randi() % 3 + 1
	var dead_anim = "dead" + str(rand)
	if dead_anim in sprite.sprite_frames.get_animation_names():
		sprite.play(dead_anim)
		await sprite.animation_finished
	else:
		print("No death animation found: ", dead_anim)

	Global.add_score(100)
	emit_signal("zombie_died")  # ✅ FIXED: No warning now
	await get_tree().create_timer(0.5).timeout
	queue_free()
