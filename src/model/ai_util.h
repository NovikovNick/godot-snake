#ifndef SNAKE_AI_UTIL_H_
#define SNAKE_AI_UTIL_H_

#include "coord.h"
#include "direction.h"
#include "game_state.h"

namespace snake {

class AIUtil {
 public:
  static Direction aStar(const Coord from, const GameState& gs);
};
}  // namespace snake
#endif  // SNAKE_AI_UTIL_H_
