#ifndef SNAKE_GRID_CELL_H_
#define SNAKE_GRID_CELL_H_
#include <iostream>

#include "board_cell_type.h"

namespace snake {

enum class Direction : std::uint8_t {
  NONE = 0,
  UP = 1,
  LEFT = 2,
  RIGHT = 3,
  BOTTOM = 4
};

struct GridCell final {
  Direction next, prev;
  BOARD_CELL_TYPE type;
  uint8_t player_id;
  bool can_be_apple;

  GridCell();
  GridCell(const Direction next, const Direction prev,
           const BOARD_CELL_TYPE type, const uint8_t player_id,
           const bool can_be_apple);

  bool isApple() const;
  bool isPlayer(const uint8_t id) const;
  bool isTail() const;
  void removePlayer();
  void placeApple();
  void pickupApple();
  void setPlayer(const uint8_t id, Direction dir, Direction prev);
  void setTail();
};
}  // namespace snake
#endif  // SNAKE_GRID_CELL_H_
