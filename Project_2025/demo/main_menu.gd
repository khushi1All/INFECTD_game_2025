extends Control


func _on_start_pressed():
	$AudioStreamPlayer2D.play()
	await get_tree().create_timer(0.001).timeout 
	get_tree().change_scene_to_file("res://main_scene.tscn")

func _on_instructions_pressed():
	$AudioStreamPlayer2D.play()
	await get_tree().create_timer(0.1).timeout
	get_tree().change_scene_to_file("res://instruction.tscn")  

func _on_quit_pressed():
	$AudioStreamPlayer2D.play()
	await get_tree().create_timer(0.1).timeout
	get_tree().quit()
