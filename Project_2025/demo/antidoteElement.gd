extends Area2D

@export var element_name: String

func _ready():
	connect("body_entered", Callable(self, "_on_body_entered"))
	add_to_group("Antidote")

func _on_body_entered(body):
	if body.is_in_group("Player"):
		$AudioStreamPlayer2D.play()

		# ✅ CACHE EVERYTHING before await
		var tree = get_tree()
		var scene = tree.current_scene

		Global.collect_element(element_name)

		if tree.get_nodes_in_group("Antidote").size() == 1:
			await tree.create_timer(0.5).timeout
			if scene and scene.has_method("_check_for_next_level"):
				scene._check_for_next_level()

		await tree.create_timer(0.2).timeout
		queue_free()
