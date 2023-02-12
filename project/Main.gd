extends Node

const Board = preload("res://bin/snake_board.gdns")

onready var board = Board.new()

var t0;
var running = false;

var l10n_key_win = "game_result.win";
var l10n_key_lose = "game_result.lose";

var STOPED = 0;
var FST_PLAYER_REACHED_SCORE = 1;
var SND_PLAYER_REACHED_SCORE = 2;
var FST_PLAYER_COLLIDED = 3;
var SND_PLAYER_COLLIDED = 4;
var PLAYING = 5;

func _ready():
	$SnakeTileMap.hide();
	$HUD.hide();
	$GameResult.hide();
	$FstPlayerScore.text = ""
	$SndPlayerScore.text = ""
	$Menu.show();

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	if Input.is_action_pressed("escape"):
		$Music.stop();
		$WinSound.stop();
		$DeathSound.stop();
		
		board.stop();
		$Menu.show();
		$FstPlayerScore.text = ""
		$SndPlayerScore.text = ""
		$GameResult.hide();
		$HUD.hide();
		$SnakeTileMap.hide();

	if(!running):
		return;
		
	var status = board.get_status();
	if (status != PLAYING):

		if(status == FST_PLAYER_REACHED_SCORE):
			$WinSound.play();
			$Music.stop();
			$GameResult.get_node("Message").text = l10n_key_win
		if(status == SND_PLAYER_COLLIDED):
			$WinSound.play();
			$Music.stop();
			$GameResult.get_node("Message").text = l10n_key_win
		if(status == FST_PLAYER_COLLIDED):
			$DeathSound.play();
			$Music.stop();
			$GameResult.get_node("Message").text = l10n_key_lose
		if(status == SND_PLAYER_REACHED_SCORE):
			$DeathSound.play();
			$Music.stop();
			$GameResult.get_node("Message").text = l10n_key_lose
			
		$GameResult.show();
		running = false;
		return;

	if Input.is_action_pressed("move_up"):
		board.update_input(0, 1)
	if Input.is_action_pressed("move_left"):
		board.update_input(0, 2)
	if Input.is_action_pressed("move_right"):
		board.update_input(0, 3)
	if Input.is_action_pressed("move_down"):
		board.update_input(0, 4)
	

	t0 += delta
	if(t0 > 0.1):
		#board.calculate_input(0);
		board.move(0)
		board.calculate_input(1);
		board.move(1)
		$FstPlayerScore.text = str(board.get_player_score(0))
		$SndPlayerScore.text =  str(board.get_player_score(1))
		t0 = 0;
	
	for row in range(20):
		for col in range(20):
			$SnakeTileMap.set_cell(col, row, board.get_cell(col, row));

func _on_Menu_single_game():
	if(running):
		return;
	board.start_with_settings(20, 20, 100);
	t0 = 0;
	running = true;
	$Menu.hide();
		
	$Music.play();
	$WinSound.stop();
	$DeathSound.stop();
	
	$SnakeTileMap.show();
	$GameResult.hide();
	$HUD.show();
	$FstPlayerScore.text = "0"
	$SndPlayerScore.text = "0"

func _on_Menu_exit():
	get_tree().quit();
