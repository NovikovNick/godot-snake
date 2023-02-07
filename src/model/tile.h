#ifndef SNAKE_TILE_H_
#define SNAKE_TILE_H_
#include "board_cell_type.h"

namespace snake {

enum class TILE_INDEX : std::uint8_t {
  EMPTY = 0,
  APPLE = 1,

  BODY_HOR = 2,
  BODY_VER = 3,

  HEAD_TOP = 4,
  HEAD_BTM = 5,
  HEAD_LFT = 6,
  HEAD_RHT = 7,

  TAIL_TOP = 8,
  TAIL_BTM = 9,
  TAIL_LFT = 10,
  TAIL_RHT = 11,

  TURN_TL = 12,
  TURN_TR = 13,
  TURN_BL = 14,
  TURN_BR = 15,
};

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
