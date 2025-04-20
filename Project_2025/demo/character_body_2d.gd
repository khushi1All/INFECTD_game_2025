extends CharacterBody2D

enum State {
	IDLE,
	WALK,
	RUN,
	HURT,
	DEAD
}

@export var speed: float = 110.0
@export var bullet_scene := preload("res://bullet.tscn")

var state: State = State.IDLE

@onready var sprite: AnimatedSprite2D = $AnimatedSprite2D
@onready var gun_sound = $GunSound
@onready var footstep_sound = $FootstepSound
@onready var spawn_point = $Gun/BulletSpawnPoint  

func _ready():
	sprite.play("idle")
	add_to_group("Player")  # For zombie detection
	Global.player = self
	print("Player is in groups:", get_groups())  # Debug

func _physics_process(_delta):
	_move()
	_update_animation()

func _process(_delta):
	if Input.is_action_just_pressed("shoot"):
		shoot()

func _move():
	velocity = Vector2.ZERO
	var _is_moving = false

	if Input.is_action_pressed("ui_left") or Input.is_action_pressed("move_left"):
		velocity.x = -1
		sprite.flip_h = true
		_is_moving = true
	elif Input.is_action_pressed("ui_right") or Input.is_action_pressed("move_right"):
		velocity.x = 1
		sprite.flip_h = false
		_is_moving = true

	if Input.is_action_pressed("ui_up") or Input.is_action_pressed("move_up"):
		velocity.y = -1
		_is_moving = true
	elif Input.is_action_pressed("ui_down") or Input.is_action_pressed("move_down"):
		velocity.y = 1
		_is_moving = true

	if !velocity.is_zero_approx():
		var current_speed = speed
		
		if Input.is_action_pressed("run"):
			print("🚀 Shift pressed!")
			current_speed *= 1.5
			state = State.RUN
		else:
			state = State.WALK

		velocity = velocity.normalized() * current_speed
		self.velocity = velocity
		move_and_slide()

		if not footstep_sound.playing:
			footstep_sound.play()
	else:
		state = State.IDLE
		footstep_sound.stop()
		self.velocity = Vector2.ZERO
		move_and_slide()

func _update_animation():
	if not sprite:
		return

	match state:
		State.IDLE:
			sprite.play("idle")
		State.WALK:
			sprite.play("walk")
		State.RUN:
			sprite.play("run")
		State.HURT:
			sprite.play("hurt")
		State.DEAD:
			sprite.play("dead")

func shoot():
	var bullet = bullet_scene.instantiate()

	var spawn_pos = spawn_point.global_position

	# Adjust spawn position based on flip_h (left or right facing)
	if sprite.flip_h:
		# When facing left, adjust the spawn point by a certain offset to the right
		spawn_pos.x -= 10  # Adjust this value as needed to position the bullet correctly
	else:
		# No change needed when facing right
		pass

	bullet.global_position = spawn_pos

	var bullet_sprite = bullet.get_node("AnimatedSprite2D")

	if sprite.flip_h:
		bullet.direction = Vector2.LEFT
		bullet_sprite.flip_h = true
	else:
		bullet.direction = Vector2.RIGHT
		bullet_sprite.flip_h = false

	# Make sure the bullet plays the "fly" animation
	bullet_sprite.play("fly")

	get_tree().current_scene.add_child(bullet)
	gun_sound.play()



func on_player_hit():
	if state == State.DEAD or state == State.HURT:
		return  # Already hurt or dead

	state = State.HURT
	sprite.play("hurt")
	await sprite.animation_finished
	
	state = State.IDLE
	
var health := 100
var max_health := 100

func take_damage(amount: int):
	health -= amount
	print("Health:", health)
	if health <= 0:
		die()

func die():
	print("Player is dead.")
	# Optional: Play death animation, stop movement, trigger game over, etc.
	queue_free()  # Temporarily remove player (you can handle game over later)


var ammo := 0
var has_key := false
