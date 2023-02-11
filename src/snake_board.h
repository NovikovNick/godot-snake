#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <Godot.hpp>
#include <Sprite.hpp>

#include "model/game_state.h"
#include "model/snake_game_api.h"

namespace godot {

class Board : public godot::Reference {
  GODOT_CLASS(Board, godot::Reference)

  std::unique_ptr<snake::SnakeGameAPI> api;

 public:
  static void _register_methods();

  void _init();

  int getCell(const int x, const int y);

  void start();

  void startWithSettings(const int width, const int heiht, const int max_score);

  void stop();

  int getStatus();

  void move(const int player_id);

  int getPlayerScore(const int player_id);

  void updateInput(const int player_id, const int dir);

  void calculateInput(const int player_id);
};
}  // namespace godot

#endif