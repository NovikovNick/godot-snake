#include "snake_board.h"

#include "model/tile.h"

using namespace godot;

void Board::_register_methods() {
  godot::register_method("get_cell_tile_index",
                         &godot::Board::get_cell_tile_index);
}

void Board::_init() {}

int Board::get_cell_tile_index(const int x, const int y) {
  return static_cast<int>(snake::TILE_INDEX::APPLE);
}
