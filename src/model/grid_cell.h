#ifndef SNAKE_GRID_CELL_H_
#define SNAKE_GRID_CELL_H_
#include <iostream>

#include "board_cell_type.h"
#include "direction.h"
#include "tile.h"
#include "tile_index_util.h"

namespace snake {

struct GridCell final {
  Direction next, prev;
  BOARD_CELL_TYPE type;
  uint8_t player_id;
  bool can_be_apple;
  TILE_INDEX tile;

  GridCell();
  GridCell(const Direction next, const Direction prev,
           const BOARD_CELL_TYPE type, const TILE_INDEX tile,
           const uint8_t player_id, const bool can_be_apple);

  bool isApple() const;
  bool isPlayer(const uint8_t id) const;
  bool isTail() const;
  void removePlayer();
  void placeApple();
  bool canBeApple();
  void pickupApple();
  void setHead(const uint8_t id, Direction dir, Direction prev);
  void setPlayer(const uint8_t id, Direction dir, Direction prev);
  void setTail();
};
}  // namespace snake
#endif  // SNAKE_GRID_CELL_H_
