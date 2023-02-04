#ifndef SNAKE_TILE_INDEX_H_
#define SNAKE_TILE_INDEX_H_

namespace snake {

enum class TILE_INDEX {
  EMPTY = 0,
  APPLE = 1,

  BODY_HOR_P1 = 2,
  BODY_VER_P1 = 3,

  HEAD_TOP_P1 = 4,
  HEAD_BTM_P1 = 5,
  HEAD_LFT_P1 = 6,
  HEAD_RHT_P1 = 7,

  TAIL_TOP_P1 = 8,
  TAIL_BTM_P1 = 9,
  TAIL_LFT_P1 = 10,
  TAIL_RHT_P1 = 11,

  TURN_TL_P1 = 12,
  TURN_TR_P1 = 13,
  TURN_BL_P1 = 14,
  TURN_BR_P1 = 15,
  
  BODY_HOR_P2 = 16,
  BODY_VER_P2 = 17,

  HEAD_TOP_P2 = 18,
  HEAD_BTM_P2 = 19,
  HEAD_LFT_P2 = 20,
  HEAD_RHT_P2 = 21,

  TAIL_TOP_P2 = 22,
  TAIL_BTM_P2 = 23,
  TAIL_LFT_P2 = 24,
  TAIL_RHT_P2 = 25,

  TURN_TL_P2 = 26,
  TURN_TR_P2 = 27,
  TURN_BL_P2 = 28,
  TURN_BR_P2 = 29
};

}  // namespace snake
#endif  // SNAKE_TILE_INDEX_H_
