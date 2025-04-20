extends Node

var score: int = 0
var player = null
var collected_elements = []
var hud = null

func _ready():
	# ✅ Find the HUD if it exists in the scene
	if get_tree().get_current_scene().has_node("HUD"):
		hud = get_tree().get_current_scene().get_node("HUD")

func add_score(points: int):
	score += points
	print("💯 Score:", score)

func collect_element(_item_name: String):
	if not _item_name in collected_elements:
		collected_elements.append(_item_name)
		print("🧪 Collected element:", _item_name)

	# ✅ Dynamically get how many antidotes were in the level
	var remaining_antidotes = get_tree().get_nodes_in_group("Antidote").size()
	print("🧪 Remaining antidotes:", remaining_antidotes)

	# ✅ If none left, go to next level
	if remaining_antidotes <= 1:  # Because this one is about to be removed
		form_antidote()


func form_antidote():
	print("✅ All antidote elements collected!")

	# ✅ Try changing level if the current scene supports it
	var scene = get_tree().current_scene
	if scene and scene.has_method("_check_for_next_level"):
		scene._check_for_next_level()
	else:
		print("⚠️ Could not find _check_for_next_level in current scene!")

func _process(_delta):
	if hud:
		# ❌ No more calling update_position unless you make that method
		# ✅ ONLY update antidote count on HUD if method exists
		if "update_antidotes" in hud:
			hud.update_antidotes(get_tree().get_nodes_in_group("Antidote").size())
