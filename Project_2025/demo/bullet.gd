extends Area2D

@export var speed := 500
@export var max_distance := 60  # Max travel distance in pixels
var direction := Vector2.RIGHT
var start_position := Vector2.ZERO

@onready var sprite: AnimatedSprite2D = $AnimatedSprite2D

func _ready():
	start_position = position
	sprite.play("fly")

func _process(delta):
	position += direction * speed * delta
	if position.distance_to(start_position) > max_distance:
		queue_free()

func _on_body_entered(body):
	if body.is_in_group("zombie"):
		body.take_damage()
		call_deferred("queue_free")
