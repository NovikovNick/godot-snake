#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <Godot.hpp>
#include <Sprite.hpp>

namespace godot {

class Board : public godot::Reference {
  GODOT_CLASS(Board, godot::Reference)

 public:
  static void _register_methods();

  void _init();

  int get_cell_tile_index(const int x, const int y);
};
}  // namespace godot

#endif