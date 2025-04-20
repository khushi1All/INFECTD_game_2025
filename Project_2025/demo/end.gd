extends Control



func _on_exit_pressed():
	$AudioStreamPlayer2D2.play()
	await get_tree().create_timer(0.3).timeout
	get_tree().quit()
