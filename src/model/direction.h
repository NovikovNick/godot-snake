#ifndef SNAKE_DIRECTION_H_
#define SNAKE_DIRECTION_H_
#include <iostream>


namespace snake {
enum class Direction : std::uint8_t {
  NONE = 0,
  UP = 1,
  LEFT = 2,
  RIGHT = 3,
  BOTTOM = 4
};
}  // namespace snake
#endif  // SNAKE_DIRECTION_H_
