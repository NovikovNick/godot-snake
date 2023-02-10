extends Node

const Board = preload("res://bin/snake_board.gdns")

onready var board = Board.new()

var t0;
var running = false;
var win_collision_msg = "Win!";
var lose_collision_msg = "Lose...";
var win_score_msg = "Win!\nYou have reached\nthe score!";
var lose_score_msg = "Lose...\nBot has reached\nthe score.";

var STOPED = 0;
var FST_PLAYER_REACHED_SCORE = 1;
var SND_PLAYER_REACHED_SCORE = 2;
var FST_PLAYER_COLLIDED = 3;
var SND_PLAYER_COLLIDED = 4;
var PLAYING = 5;

func _ready():
	$SnakeTileMap.hide();
	$FstPlayerScore.text = ""
	$SndPlayerScore.text = ""
	$Menu.show();

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	if Input.is_action_pressed("escape"):
		board.stop();
		$Menu.show();
		$FstPlayerScore.text = ""
		$SndPlayerScore.text = ""
		$GameResultLabel.hide();
		$SnakeTileMap.hide();
	
	if(!running):
		return;
		
	var status = board.get_status();
	if (status != PLAYING):

		if(status == FST_PLAYER_REACHED_SCORE):
			$GameResultLabel.text = win_score_msg
		if(status == FST_PLAYER_COLLIDED):
			$GameResultLabel.text = lose_collision_msg
		if(status == SND_PLAYER_REACHED_SCORE):
			$GameResultLabel.text = lose_score_msg
		if(status == SND_PLAYER_COLLIDED):
			$GameResultLabel.text = win_collision_msg
		$GameResultLabel.show();
		running = false;
		return;

	if Input.is_action_pressed("move_up"):
		board.update_input(1)
	if Input.is_action_pressed("move_left"):
		board.update_input(2)
	if Input.is_action_pressed("move_right"):
		board.update_input(3)
	if Input.is_action_pressed("move_down"):
		board.update_input(4)
	

	t0 += delta
	if(t0 > 0.2):
		board.move(0)
		board.move(1)
		$FstPlayerScore.text = str(board.get_player_score(0))
		$SndPlayerScore.text =  str(board.get_player_score(1))
		t0 = 0;
	
	for row in range(10):
		for col in range(10):
			$SnakeTileMap.set_cell(col, row, board.get_cell(col, row));

func _on_Menu_single_game():
	board.start();
	t0 = 0;
	running = true;
	$Menu.hide();
	$SnakeTileMap.show();
	$FstPlayerScore.text = "0"
	$SndPlayerScore.text = "0"

func _on_Menu_exit():
	get_tree().quit();
