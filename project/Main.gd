extends Node

const Board = preload("res://bin/snake_board.gdns")

onready var board = Board.new()

var t0;

# Called when the node enters the scene tree for the first time.
func _ready():
	board.start();
	t0 = 0;

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if Input.is_action_pressed("move_up"):
		board.update_input(1)
	if Input.is_action_pressed("move_left"):
		board.update_input(2)
	if Input.is_action_pressed("move_right"):
		board.update_input(3)
	if Input.is_action_pressed("move_down"):
		board.update_input(4)

	t0 += delta
	if(t0 > 0.1):
		board.move(0)
		#board.move(1)
		t0 = 0;
	
	for row in range(10):
		for col in range(10):
			$SnakeTileMap.set_cell(col, row, board.get_cell(col, row));
	
