extends CanvasLayer

@onready var antidote_label = $LabelContainer/AntidoteLabel
@onready var position_label = $LabelContainer/PositionLabel
@onready var score_label = $LabelContainer/ScoreLabel

func _process(_delta):
	if Global.player:
		var pos = Global.player.global_position
		position_label.text = "📍 Position: (%.1f, %.1f)" % [pos.x, pos.y]
		score_label.text = "💯 Score: %d" % Global.score
		antidote_label.text = "🧪 Antidotes Left: %d" % get_tree().get_nodes_in_group("Antidote").size()

@onready var popup_label = $LevelPopupLabel

func show_level_transition(text: String):
	popup_label.text = text
	popup_label.visible = true
	await get_tree().create_timer(1.5).timeout
	popup_label.visible = false


func _on_quit_pressed():
	$QuitSound.play()
	await get_tree().create_timer(0.1).timeout  # Let the sound play
	get_tree().change_scene_to_file("res://MainMenu.tscn")
