extends Node

const Board = preload("res://bin/snake_board.gdns")

onready var board_instance = Board.new()

# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	print("Apple => " + str(board_instance.get_cell_tile_index(1,2)));


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
