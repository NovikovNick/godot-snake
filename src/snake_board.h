#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <Godot.hpp>
#include <Sprite.hpp>

#include "model/snake_game_api.h"
#include "model/game_state.h"

namespace godot {

class Board : public godot::Reference {
  GODOT_CLASS(Board, godot::Reference)

  std::unique_ptr<snake::SnakeGameAPI> api;

 public:
  static void _register_methods();

  void _init();

  int getCell(const int x, const int y);

  void start();

  void move(const int player_id);

  void updateInput(const int dir);
};
}  // namespace godot

#endif