#ifndef SNAKE_TILE_H_
#define SNAKE_TILE_H_
#include "board_cell_type.h"
#include "tile_index.h"

namespace snake {

struct Tile {
  BOARD_CELL_TYPE type;
  int player_id;
  TILE_INDEX index;

  Tile(const BOARD_CELL_TYPE type, const int player_id, const TILE_INDEX index)
      : type(type), player_id(player_id), index(index){};

  static Tile empty() {
    return Tile(BOARD_CELL_TYPE::EMPTY, -1, TILE_INDEX::EMPTY);
  }

  static Tile apple() {
    return Tile(BOARD_CELL_TYPE::APPLE, -1, TILE_INDEX::APPLE);
  }

  static Tile player(const int player_id, const TILE_INDEX index) {
    return Tile(BOARD_CELL_TYPE::PLAYER, player_id, index);
  }

  bool operator==(const Tile& rhs) const {
    return type == rhs.type && index == rhs.index && player_id == rhs.player_id;
  };
};

}  // namespace snake
#endif  // SNAKE_TILE_H_
