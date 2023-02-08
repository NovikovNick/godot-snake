#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <Godot.hpp>
#include <Sprite.hpp>

#include "model/snake_game_api.h"

namespace godot {

class Board : public godot::Reference {
  GODOT_CLASS(Board, godot::Reference)

  std::unique_ptr<snake::SnakeGameAPI> api;

 public:
  static void _register_methods();

  void _init();

  int get_cell(const int x, const int y);

  int start();

  int move(const int player_id);
};
}  // namespace godot

#endif