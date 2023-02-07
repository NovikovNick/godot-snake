#ifndef SNAKE_BOARD_CELL_TYPE_H_
#define SNAKE_BOARD_CELL_TYPE_H_

namespace snake {

enum class BOARD_CELL_TYPE : std::uint8_t { EMPTY = 0, APPLE = 1, PLAYER = 2 };

}  // namespace snake
#endif  // SNAKE_BOARD_CELL_TYPE_H_
