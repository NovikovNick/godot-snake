#ifndef SNAKE_COORD_H_
#define SNAKE_COORD_H_

namespace snake {

struct Coord {
  int col, row;

  static Coord plus(const Coord& lhs, const Coord& rhs);
  static bool equal(const Coord& lhs, const Coord& rhs);
};
}  // namespace snake
#endif  // SNAKE_COORD_H_
