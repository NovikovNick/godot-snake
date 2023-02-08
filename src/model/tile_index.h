#ifndef SNAKE_TILE_INDEX_H_
#define SNAKE_TILE_INDEX_H_

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

}  // namespace snake
#endif  // SNAKE_TILE_INDEX_H_
