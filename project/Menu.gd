extends Node2D

signal single_game
signal exit

func _on_SinglePlayerButton_pressed():
	emit_signal("single_game");

func _on_ExitButton_pressed():
	emit_signal("exit");
