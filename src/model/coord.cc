#include "coord.h"

// snake::Coord operator+(const snake::Coord& lhs, const snake::Coord& rhs) {
//   return {lhs.col + rhs.col, lhs.row + rhs.row};
// }
//
// bool operator==(const snake::Coord& lhs, const snake::Coord& rhs) {
//   return lhs.col == rhs.col && lhs.row == rhs.row;
// }
namespace snake {

Coord Coord::plus(const Coord& lhs, const Coord& rhs) {
  return {lhs.col + rhs.col, lhs.row + rhs.row};
}

bool Coord::equal(const Coord& lhs, const Coord& rhs) {
  return lhs.col == rhs.col && lhs.row == rhs.row;
}

}  // namespace snake
